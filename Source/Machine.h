#ifndef GBX_MACHINE_H_
#define GBX_MACHINE_H_
#include <Utix/Ints.h>

namespace gbx {

struct Cpu {
	uint16_t opcode;
	uint16_t pc;
	uint16_t sp;
};


struct Machine {
	Cpu cpu;
	uint8_t* ram;
};


Machine* CreateMachine();
void DestroyMachine(Machine* const mach);
bool LoadRom(const char* rom_file_name, Machine* const mach);
bool StepMachine(Machine* const mach);



}






#endif
