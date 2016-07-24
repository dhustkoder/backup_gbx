#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Utix/Assert.h>
#include <Utix/Alloc.h>
#include <Utix/ScopeExit.h>

#include "Memory.h"
#include "Rom.h"


namespace gbx {






bool Rom::Load(const char* file_name) {
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

	const_cast<uint8_t*&>(m_data) = static_cast<uint8_t*>(utix::alloc_arr(sizeof(uint8_t) * rom_size));

	if (m_data == nullptr) {
		perror("Couldn't allocate memory for ROM");
		return false;
	}

	auto cartridge_data_guard = utix::MakeScopeExitIf([this] {
		free(m_data);
		const_cast<uint8_t*&>(m_data) = nullptr;
	});


	fread(m_data, sizeof(uint8_t), rom_size, rom_file);

	if (ferror(rom_file)) {
		perror("error while reading from rom");
		return false;
	}

	cartridge_data_guard.Cancel();
	return true;
}





















}

















