#ifndef GBX_MACHINE_H_
#define GBX_MACHINE_H_
#include <Utix/Ints.h>
#include "Cpu.h"
#include "Memory.h"

namespace gbx {


class Machine {
public:
	Machine()=delete;
	~Machine()=delete;
	Machine(Machine&)=delete;
	Machine(Machine&&)=delete;
	Machine&operator=(Machine&)=delete;
	Machine&operator=(Machine&&)=delete;

	size_t GetRomSize() const;
	bool LoadRom(const char* rom_file_name);
	bool StepMachine();

	void PushStack8(const uint8_t value);
	void PushStack16(const uint16_t value);
	uint8_t PopStack8();
	uint16_t PopStack16();
	

	Cpu cpu;
	Memory memory;

private:
	size_t m_rom_size;
};

Machine* CreateMachine();
void DestroyMachine(Machine* const mach);



inline size_t Machine::GetRomSize() const {
	return m_rom_size;
}


inline void Machine::PushStack8(const uint8_t value) {
	const auto sp = cpu.GetSP() - 1;
	memory.WriteU8(sp, value);
	cpu.SetSP(sp);

}

inline void Machine::PushStack16(const uint16_t value) {
	const auto sp = cpu.GetSP() - 2;
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
