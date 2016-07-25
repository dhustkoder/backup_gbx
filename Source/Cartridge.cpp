#include <stdio.h>
#include <string.h>
#include <Utix/Alloc_t.h>
#include <Utix/Assert.h>
#include <Utix/ScopeExit.h>

#include "Memory.h"
#include "Cartridge.h"


namespace gbx {



inline uint8_t* AllocateCartridgeData(size_t bytes);
inline void DeallocateCartridgeData(uint8_t* ptr);
inline size_t GetCartridgeDataSize(uint8_t* ptr);





void Cartridge::Initialize() {
	const_cast<uint8_t*&>(m_data) = nullptr;
}



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

	if (rom_size > MAX_CARTRIDGE_SIZE || rom_size < MIN_CARTRIDGE_SIZE) {
		fprintf(stderr, "\'%s\' size not compatible\n", file_name);
		return false;
	}


	if(GetSize() < rom_size) {
		this->Dispose();
		const_cast<uint8_t*&>(m_data) = AllocateCartridgeData(sizeof(uint8_t) * rom_size);
		
		if (m_data == nullptr) {
			perror("Couldn't allocate memory for ROM");
			return false;
		}
	}
	
	fread(m_data, sizeof(uint8_t), rom_size, rom_file);

	if (ferror(rom_file)) {
		perror("error while reading from rom");
		return false;
	}

	// null the last byte of Cartridge's internal name -
	// just in case.
	if (m_data[0x142] != 0)
		m_data[0x142] = 0;
	
	return true;
}




void Cartridge::Dispose() {
	if(m_data) {
		DeallocateCartridgeData(m_data);
		const_cast<uint8_t*&>(m_data) = nullptr;
	}
}






CartridgeType Cartridge::GetType() const {
	return static_cast<CartridgeType>(m_data[0x147]);
}





const uint8_t* Cartridge::Data() const {
	return m_data;
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





size_t Cartridge::GetSize() const {
	return GetCartridgeDataSize(m_data);
}





uint8_t* Cartridge::Data() {
	return m_data;
}





















// putting rein..casts into one place


inline uint8_t* AllocateCartridgeData(size_t bytes) {
	// alloc enough bytes for rom_file and for a size_t variable
	const size_t size = (sizeof(uint8_t) * bytes);
	size_t* const ptr = static_cast<size_t*>(malloc(size + sizeof(size_t)));
	
	if(ptr) {
		// store Cartridge's size into first bytes of the array, then
		// increment pointer to not erase it
		*ptr = size;
		return reinterpret_cast<uint8_t*>(ptr + 1);
	}
	
	return reinterpret_cast<uint8_t*>(ptr);
}


inline void DeallocateCartridgeData(uint8_t* ptr) {
	// free the original pointer address
	free(reinterpret_cast<size_t*>(ptr) - 1);
}




inline size_t GetCartridgeDataSize(uint8_t* ptr) {
	// retrieve size from array first bytes as size_t
	return ptr ? *(reinterpret_cast<size_t*>(ptr) - 1) : 0;
}















}

















