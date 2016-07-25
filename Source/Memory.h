#ifndef GBX_MEMORY_H_
#define GBX_MEMORY_H_
#include <Utix/Ints.h>
#include "Common.h"



namespace gbx {
/*  
based on http://marc.rawer.de/Gameboy/
MEMORY MAP:

		|...............| 0xFFFF
		|_______________| 0xFFFE
		|  WORK & STACK |
		|      AREA     |
		|_______________| 0xFF80
		| SOUND CONTROL |
		|    REGISTER   |
		|_______________|
		|  LCDC CONTROL |
		|   REGISTER    |
		|_______________|
		|    PORT/MODE  |
		|    REGISTER   |
		|_______________| 0xFF00
		|     OAM RAM   |
		|_______________| 0xFE00
		|       -       |
		|_______________| 0xF000
		|       -       |
		|_______________| 0xE000
		|               |
		|    WORK RAM   |
		|_______________| 0xC000
		|    EXPANDED   |
		|    WORK RAM   |
		|_______________| 0xA000
		|BKG DISP DATA 2|
		|_______________| 0x9C00
		|BKG DISP DATA 1|
		|_______________| 0x9800
		|   CHARACTER   |
		|      DATA     |
		|_______________| 0x8000
		|               |
		|      HOME     |
		|               |
		|_______________| 0x4000
		|               |
		|   FIXED HOME  |
		|               |
		|_______________| 0x0000 


fixed home and home goes the cartridge's user program data
catridge's entry point is at 0x100
*/

//MEMORY AREAS SIZES:
//constexpr const size_t OAM_RAM_SIZE = 256;
//constexpr const size_t WORK_RAM_SIZE = 8_Kib;
//constexpr const size_t EXPANDED_WORK_RAM_SIZE = 8_Kib;
//constexpr const size_t BKG_DISP_DATA2_SIZE = 1_Kib;
//constexpr const size_t BKG_DISP_DATA1_SIZE = 1_Kib;
//constexpr const size_t CHAR_DATA_SIZE = 6_Kib;
constexpr const size_t HOME_SIZE = 16_Kib;
constexpr const size_t FIXED_HOME_SIZE = 16_Kib;
constexpr const size_t TOTAL_RAM_SIZE = 64_Kib;
constexpr const size_t MAX_CARTRIDGE_SIZE = 32_Kib;
constexpr const size_t MIN_CARTRIDGE_SIZE = 32_Kib;


//MEMORY AREAS OFFSETS:
//constexpr const size_t OAM_RAM_MAX_OFFSET = 0xFEFF;
//constexpr const size_t OAM_RAM_OFFSET = 0xFE00;
//constexpr const size_t WORK_RAM_MAX_OFFSET = 0xDFFF;
//constexpr const size_t WORK_RAM_OFFSET = 0xC000;
//constexpr const size_t EXPANDED_WORK_RAM_MAX_OFFSET = 0xBFFF;
//constexpr const size_t EXPANDED_WORK_RAM_OFFSET = 0xA000;
//constexpr const size_t BKG_DISP_DATA2_MAX_OFFSET = 0x9FFF;
//constexpr const size_t BKG_DISP_DATA2_OFFSET = 0x9C00;
//constexpr const size_t BKG_DISP_DATA1_MAX_OFFSET = 0x9BFF;
//constexpr const size_t BKG_DISP_DATA1_OFFSET = 0x9800;
//constexpr const size_t CHAR_DATA_MAX_OFFSET = 0x97FF;
//constexpr const size_t CHAR_DATA_OFFSET = 0x8000;
constexpr const size_t HOME_MAX_OFFSET = 0x7FFF;
constexpr const size_t HOME_OFFSET = 0x4000;
//constexpr const size_t FIXED_HOME_MAX_OFFSET = 0x3FFF;
constexpr const size_t FIXED_HOME_OFFSET = 0;
constexpr const size_t CARTRIDGE_ENTRY_POINT = 0x100;


class Memory {
public:
	Memory()=delete;
	~Memory()=delete;
	Memory(Memory&)=delete;
	Memory(Memory&&)=delete;
	Memory&operator=(Memory&)=delete;
	Memory&operator=(Memory&&)=delete;

	bool Initialize();
	void Dispose();

	uint8_t* Data();
	const uint8_t* Data() const;

	int8_t ReadS8(const uint16_t pointer) const;
	uint8_t ReadU8(const uint16_t pointer) const;
	uint16_t ReadU16(const uint16_t pointer) const;
	void ReadU16(const uint16_t pointer, uint8_t* const high_byte, uint8_t* const low_byte) const;
	void WriteU8(const uint16_t pointer, const uint8_t value);
	void WriteU16(const uint16_t pointer, const uint16_t value);
	void WriteU16(const uint16_t pointer, const uint8_t high_byte, const uint8_t low_byte);
	
	void AddU8(const uint16_t pointer, const uint8_t value);
	void SubU8(const uint16_t pointer, const uint8_t value);

private:
	uint8_t* const m_data;
};


































}
#endif
