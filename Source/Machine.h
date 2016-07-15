#ifndef GBX_MACHINE_H_
#define GBX_MACHINE_H_
#include <Utix/Ints.h>

namespace gbx {




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
	uint8_t* ram;
	size_t rom_size;
};


Machine* CreateMachine();
void DestroyMachine(Machine* const mach);
bool LoadRom(const char* rom_file_name, Machine* const mach);
bool StepMachine(Machine* const mach);



inline uint16_t ConcatBytes(const uint8_t high_byte, const uint8_t low_byte) {
	return (high_byte << 8) | low_byte;
}


inline void Split16(const uint16_t value, uint8_t* const high_byte, uint8_t* const low_byte) {
	*high_byte = (value & 0xFF00) >> 8;
	*low_byte = (value & 0x00FF);
}


inline uint16_t Read16(const uint8_t* memory) {
	return ConcatBytes(memory[1], memory[0]);
}


inline void Read16(const uint8_t* memory, uint8_t* const high_byte, uint8_t* const low_byte) {
	*high_byte = *( memory + 1 );
	*low_byte = *memory;
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



inline bool GetFlag(Cpu::Flags flag, const Cpu& cpu) {
	return (cpu.F & static_cast<uint8_t>(flag) ) != 0;
}


inline void SetFlag(Cpu::Flags flag, Cpu* const cpu) {
	cpu->F |= static_cast<uint8_t>(flag);
}


inline void UnsetFlag(Cpu::Flags flag, Cpu* const cpu) {
	cpu->F ^= static_cast<uint8_t>(flag);
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
