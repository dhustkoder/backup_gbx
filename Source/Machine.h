#ifndef GBX_MACHINE_H_
#define GBX_MACHINE_H_
#include <Utix/Ints.h>
#include "Cpu.h"
#include "Memory.h"
#include "Cartridge.h"

namespace gbx {



enum InterruptMasks : uint8_t {
	INTERRUPT_VBLANK = 0x01,
	INTERRUPT_LCDC = 0x02,
	INTERRUPT_TIMER = 0x40,
	INTERRUPT_SERIAL = 0x80,
	INTERRUPT_THLP = 0x10,
	// extra mask for emulator information
	INTERRUPT_IME = 0x80, // used as IME flag on INTERRUPT_ENABLED_OFFSET (in memory)
	INTERRUPT_IMA = 0x40  // used as aux flag on INTERRUPT_ENABLED_OFFSET (in memory)
};


enum InterruptAddrs : uint16_t {
	INTERRUPT_VBLANK_ADDR = 0x40
};












class Machine {
public:
	Machine()=delete;
	~Machine()=delete;
	Machine(Machine&)=delete;
	Machine(Machine&&)=delete;
	Machine&operator=(Machine&)=delete;
	Machine&operator=(Machine&&)=delete;

	bool GetIME() const;
	void SetIME(bool val);

	bool LoadRom(const char* filename);
	bool Reset();
	bool Step();
	void StepInterrupts();


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





inline bool Machine::GetIME() const {
	return (memory.GetIE() & INTERRUPT_IME) != 0;
}



inline void Machine::SetIME(bool val) {
	uint8_t ie = memory.GetIE();
	if (val) ie |= INTERRUPT_IME;
	else ie &= ~INTERRUPT_IME;
	memory.SetIE(ie);
}









inline void Machine::PushStack8(const uint8_t value) {
	const uint16_t sp = cpu.GetSP() - 1;
	memory.WriteU8(sp, value);
	cpu.SetSP(sp);

}







inline void Machine::PushStack16(const uint16_t value) {
	const uint16_t sp = cpu.GetSP() - 2;
	memory.WriteU16(sp, value);
	cpu.SetSP(sp);
}







inline uint8_t Machine::PopStack8() {
	const auto sp = cpu.GetSP();
	const auto val = memory.ReadU8(sp);
	cpu.SetSP(sp + 1);
	return val;
}








inline uint16_t Machine::PopStack16() {
	const auto sp = cpu.GetSP();
	const auto val = memory.ReadU16(sp);
	cpu.SetSP(sp + 2);
	return val;
}





























}
#endif
