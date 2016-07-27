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

	bool GetIME() const;
	uint8_t GetIE() const;
	uint8_t GetIF() const;


	bool LoadRom(const char* filename);
	bool Reset();
	bool Step();
	void UpdateInterrupts();


	void PushStack8(const uint8_t value);
	void PushStack16(const uint16_t value);
	uint8_t PopStack8();
	uint16_t PopStack16();
	
	void SetIME(bool val);



	Cpu cpu;
	Memory memory;
	Cartridge cartridge;
};




Machine* CreateMachine();
void DestroyMachine(Machine* const mach);



inline bool Machine::GetIME() const {
	return (memory.ReadU8(INTERRUPT_ENABLED_OFFSET) & 0x80) != 0;
}


inline uint8_t Machine::GetIE() const {
	return memory.ReadU8(INTERRUPT_ENABLED_OFFSET) & 0x0f;
}


inline uint8_t Machine::GetIF() const {
	return memory.ReadU8(INTERRUPT_FLAGS_OFFSET);
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









inline void Machine::SetIME(bool val) {
	uint8_t ie = memory.ReadU8(INTERRUPT_ENABLED_OFFSET);
	memory.WriteU8(INTERRUPT_ENABLED_OFFSET, val ? ie | 0x80 : ie & 0x0f);
}




















}
#endif
