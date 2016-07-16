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
	Machine&operator=(Machine&)=delete;
	Machine&operator=(Machine&&)=delete;

	bool LoadRom(const char* rom_file_name);
	bool StepMachine();
	void Load16BC(const uint16_t pointer);
	void Load16DE(const uint16_t pointer);
	void Load16HL(const uint16_t pointer);
	void Store8BC(const uint8_t value);
	void Store8DE(const uint8_t value);
	void Store8HL(const uint8_t value);



	Cpu cpu;
	Memory memory;
	const size_t rom_size;
};


Machine* CreateMachine();
void DestroyMachine(Machine* const gb);



inline void Machine::Load16BC(const uint16_t pointer) {
	memory.Read16(pointer, &cpu.B, &cpu.C);
}

inline void Machine::Load16DE(const uint16_t pointer) {
	memory.Read16(pointer, &cpu.D, &cpu.E);
}

inline void Machine::Load16HL(const uint16_t pointer) {
	memory.Read16(pointer, &cpu.H, &cpu.L);
}



inline void Machine::Store8BC(const uint8_t value) {
	memory.Write8(cpu.GetBC(), value);
}

inline void Machine::Store8DE(const uint8_t value) {
	memory.Write8(cpu.GetDE(), value);
}

inline void Machine::Store8HL(const uint8_t value) {
	memory.Write8(cpu.GetHL(), value);
}


























}
#endif
