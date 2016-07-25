#ifndef GBX_MACHINE_H_
#define GBX_MACHINE_H_
#include <Utix/Ints.h>
#include "Cpu.h"
#include "Memory.h"
#include "Cartridge.h"

namespace gbx {


class Machine {
public:
	Machine()=delete;
	~Machine()=delete;
	Machine(Machine&)=delete;
	Machine(Machine&&)=delete;
	Machine&operator=(Machine&)=delete;
	Machine&operator=(Machine&&)=delete;

	bool LoadRom(const char* filename);
	bool Reset();
	bool Step();

	void PushStack8(const uint8_t value);
	void PushStack16(const uint16_t value);
	uint8_t PopStack8();
	uint16_t PopStack16();
	

	Cpu cpu;
	Memory memory;
	Cartridge cartridge;
};




Machine* CreateMachine();
void DestroyMachine(Machine* const mach);





































}
#endif
