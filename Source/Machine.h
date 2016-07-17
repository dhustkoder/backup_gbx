#ifndef GBX_MACHINE_H_
#define GBX_MACHINE_H_
#include <Utix/Ints.h>
#include "Cpu.h"
#include "Memory.h"

namespace gbx {


struct Machine {
	Machine()=delete;
	Machine(Machine&)=delete;
	Machine(Machine&&)=delete;
	~Machine()=delete;
	Machine&operator=(Machine&)=delete;
	Machine&operator=(Machine&&)=delete;

	bool LoadRom(const char* rom_file_name);
	bool StepMachine();

	void PushStack8(const uint8_t value);
	void PushStack16(const uint16_t value);
	uint8_t PopStack8();
	uint16_t PopStack16();

	Cpu cpu;
	Memory memory;
	const size_t rom_size;
};


Machine* CreateMachine();
void DestroyMachine(Machine* const mach);




inline void Machine::PushStack8(const uint8_t value) {
	memory.Write8(--cpu.sp, value);
}

inline void Machine::PushStack16(const uint16_t value) {
	cpu.sp -= 2;
	memory.Write16(cpu.sp, value);
}

inline uint8_t Machine::PopStack8() {
	return memory.Read8(cpu.sp++);
}


inline uint16_t Machine::PopStack16() {
	const auto val = memory.Read16(cpu.sp);
	cpu.sp += 2;
	return val;
}






















}
#endif
