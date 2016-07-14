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











}
#endif
