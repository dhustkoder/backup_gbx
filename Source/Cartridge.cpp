#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Utix/Assert.h>
#include <Utix/Alloc.h>
#include <Utix/ScopeExit.h>

#include "Memory.h"
#include "Cartridge.h"


namespace gbx {






bool Cartridge::Load(const char* file_name) {
	FILE* const rom_file = fopen(file_name, "r");

	if (!rom_file) {
		perror("Could not open rom file");
		return false;
	}

	const auto file_cleanup = utix::MakeScopeExit([=] {
		fclose(rom_file);
	});

	fseek(rom_file, 0, SEEK_END);
	const auto rom_size = static_cast<size_t>(ftell(rom_file));
	fseek(rom_file, 0, SEEK_SET);

	if (rom_size > MAX_CARTRIDGE_SIZE) {
		fprintf(stderr, "\'%s\' size is too big\n", file_name);
		return false;
	}

	if (m_data)
		this->Dispose();

	const_cast<uint8_t*&>(m_data) = utix::alloc_arr<uint8_t>(rom_size);

	if (m_data == nullptr) {
		perror("Couldn't allocate memory for ROM");
		return false;
	}

	auto cartridge_data_guard = utix::MakeScopeExitIf([=] {
		this->Dispose();
	});

	fread(m_data, sizeof(uint8_t), rom_size, rom_file);

	if (ferror(rom_file)) {
		perror("error while reading from rom");
		return false;
	}

	// null the last name character just in case!
	if (m_data[0x142] != 0)
		m_data[0x142] = 0;

	cartridge_data_guard.Cancel();
	return true;
}







GameBoyType Cartridge::GetGameBoyType() const {
	const uint8_t sgb = m_data[0x146];
	const uint8_t col = m_data[0x143];
	
	if (sgb == 0x3)
		return GameBoyType::SUPER_GAMEBOY;
	else if (col == 0x80)
		return GameBoyType::GAMEBOY_COLOR;
	
	return GameBoyType::GAMEBOY;
}





const char* Cartridge::GetName() const {
	return reinterpret_cast<const char*>(m_data + 0x134);
}










}

















