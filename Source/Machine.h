#ifndef GBX_MACHINE_H_
#define GBX_MACHINE_H_
#include <Utix/Ints.h>

namespace gbx {

// based on http://marc.rawer.de/Gameboy/
/* MEMORY MAP:

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
//constexpr const size_t WORK_RAM_SIZE = 8 * 1024;
//constexpr const size_t EXPANDED_WORK_RAM_SIZE = 8 * 1024;
//constexpr const size_t BKG_DISP_DATA2_SIZE = 1024;
//constexpr const size_t BKG_DISP_DATA1_SIZE = 1024;
//constexpr const size_t CHAR_DATA_SIZE = 6 * 1024;
//constexpr const size_t HOME_SIZE = 16 * 1024;
//constexpr const size_t FIXED_HOME_SIZE = 16 * 1024;

//MEMORY AREAS OFFSETS:
//constexpr const size_t OAM_RAM_OFFSET = 0xFE00;
//constexpr const size_t WORK_RAM_OFFSET = 0xC000;
//constexpr const size_t EXPANDED_WORK_RAM_OFFSET = 0xA000;
//constexpr const size_t BKG_DISP_DATA2_OFFSET = 0x9C00;
//constexpr const size_t BKG_DISP_DATA1_OFFSET = 0x9800;
constexpr const size_t CHAR_DATA_OFFSET = 0x8000;
//constexpr const size_t HOME_OFFSET = 0x4000;
//onstexpr const size_t FIXED_HOME_OFFSET = 0;
constexpr const size_t CARTRIDGE_ENTRY_POINT = 0x100;


constexpr const size_t TOTAL_RAM_SIZE = 0xFFFF;
constexpr const size_t MAX_CARTRIDGE_SIZE = 32 * 1024;


struct Cpu {
	uint16_t pc;
	uint16_t sp;
	uint8_t op;
	uint8_t A, F; 
	uint8_t B, C; 
	uint8_t D, E;
	uint8_t H, L;

	enum class Flags : uint8_t {
		Z = 0x80, N = 0x40, H = 0x20, C = 0x10
	};
};


struct Machine {
	Cpu cpu;
	uint8_t* const ram;
	const size_t rom_size;
};





Machine* CreateMachine();
void DestroyMachine(Machine* const mach);
bool LoadRom(const char* rom_file_name, Machine* const mach);
bool StepMachine(Machine* const mach);









constexpr Cpu::Flags operator|(Cpu::Flags f1, Cpu::Flags f2) {
	return static_cast<Cpu::Flags>(static_cast<uint8_t>(f1) | static_cast<uint8_t>(f2));
}

constexpr Cpu::Flags operator&(Cpu::Flags f1, Cpu::Flags f2) {
	return static_cast<Cpu::Flags>(static_cast<uint8_t>(f1) & static_cast<uint8_t>(f2));
}




inline uint16_t ConcatBytes(const uint8_t high_byte, const uint8_t low_byte) {
	return (high_byte << 8) | low_byte;
}


inline void Split16(const uint16_t value, uint8_t* const high_byte, uint8_t* const low_byte) {
	*high_byte = (value & 0xFF00) >> 8;
	*low_byte = (value & 0x00FF);
}


inline uint8_t Read8(const uint8_t* memory) {
	return *memory;
}

inline void Read8(const uint8_t* memory, uint8_t* byte) {
	*byte = *memory;
}


inline uint16_t Read16(const uint8_t* memory) {
	return ConcatBytes(memory[1], memory[0]);
}


inline void Read16(const uint8_t* memory, uint8_t* const high_byte, uint8_t* const low_byte) {
	*high_byte = *( memory + 1 );
	*low_byte = *memory;
}


inline void Write8(const uint8_t value, uint8_t* const memory) {
	*memory = value;
}


inline void Write16(const uint16_t value, uint8_t* const memory) {
	Split16(value, &memory[1], &memory[0]);
}


inline void Write16(const uint8_t high_byte, const uint8_t low_byte, uint8_t* const memory) {
	memory[0] = low_byte;
	memory[1] = high_byte;
}



inline void Add16(const uint16_t val, uint8_t* const high_byte, uint8_t* const low_byte) {
	const uint16_t result = ConcatBytes(*high_byte, *low_byte) + val;
	Split16(result, high_byte, low_byte);
}

inline void Sub16(const uint16_t val, uint8_t* const high_byte, uint8_t* const low_byte) {
	const uint16_t result = ConcatBytes(*high_byte, *low_byte) - val;
	Split16(result, high_byte, low_byte);
}





inline uint16_t GetBC(const Cpu& cpu) {
	return ConcatBytes(cpu.B, cpu.C);
}

inline uint16_t GetDE(const Cpu& cpu) {
	return ConcatBytes(cpu.D, cpu.E);	
}

inline uint16_t GetHL(const Cpu& cpu) {
	return ConcatBytes(cpu.H, cpu.L);
}




inline bool GetFlags(Cpu::Flags flags, const Cpu& cpu) {
	return ( cpu.F & static_cast<uint8_t>(flags) ) != 0;
}


inline void SetFlags(Cpu::Flags flags, Cpu* const cpu) {
	cpu->F |= static_cast<uint8_t>(flags);
}


inline void UnsetFlags(Cpu::Flags flags, Cpu* const cpu) {
	cpu->F ^= static_cast<uint8_t>(flags);
}


inline void SetBC(const uint8_t* memory, Cpu* const cpu) {
	Read16(memory, &cpu->B, &cpu->C);
}

inline void SetDE(const uint8_t* memory, Cpu* const cpu) {
	Read16(memory, &cpu->D, &cpu->E);
}

inline void SetHL(const uint8_t* memory, Cpu* const cpu) {
	Read16(memory, &cpu->H, &cpu->L);
}



inline void SetBC(const uint16_t value, Cpu* const cpu) {
	Split16(value, &cpu->B, &cpu->C);
}

inline void SetDE(const uint16_t value, Cpu* const cpu) {
	Split16(value, &cpu->D, &cpu->E);
}

inline void SetHL(const uint16_t value, Cpu* const cpu) {
	Split16(value, &cpu->H, &cpu->L);
}




inline void AddBC(const uint16_t val, Cpu* const cpu) {
	Add16(val, &cpu->B, &cpu->C);
}

inline void AddDE(const uint16_t val, Cpu* const cpu) {
	Add16(val, &cpu->D, &cpu->E);
}

inline void AddHL(const uint16_t val, Cpu* const cpu) {
	Add16(val, &cpu->H, &cpu->L);
}



inline void SubBC(const uint16_t val, Cpu* const cpu) {
	Sub16(val, &cpu->B, &cpu->C);
}

inline void SubDE(const uint16_t val, Cpu* const cpu) {
	Sub16(val, &cpu->D, &cpu->E);
}

inline void SubHL(const uint16_t val, Cpu* const cpu) {
	Sub16(val, &cpu->H, &cpu->L);
}



























}
#endif
