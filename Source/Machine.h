#ifndef GBX_MACHINE_H_
#define GBX_MACHINE_H_
#include <Utix/Ints.h>

namespace gbx {

struct Cpu {
	uint32_t opcode;
	uint16_t pc;
};


struct Machine {
	Cpu cpu;
	uint8_t* ram;
	size_t rom_size;
};

Machine* CreateMachine(uint8_t* rom, size_t rom_size);
void DestroyMachine(Machine* mach);
bool StepMachine(Machine* mach);



}






#endif
