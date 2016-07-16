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

	Cpu cpu;
	Memory memory;
	const size_t rom_size;
};


Machine* CreateMachine();
void DestroyMachine(Machine* const gb);

























}
#endif
