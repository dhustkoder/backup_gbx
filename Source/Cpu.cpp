#include <stdio.h>
#include <Utix/Assert.h>
#include "Common.h"
#include "Cpu.h"


namespace gbx {


Cpu::Flags Cpu::GetFlags(const Cpu::Flags flags) const {
	return static_cast<Flags>(GetF() & flags);
}


void Cpu::ShowFlags() const {
	const auto f = GetF();
	const auto z = f & FLAG_Z;
	const auto n = f & FLAG_N;
	const auto h = f & FLAG_H;
	const auto c = f & FLAG_C;
	printf("CPU FLAGS: Z(%X), N(%X), H(%X), C(%X)\n", z, n, h, c);
}


void Cpu::SetFlags(const Cpu::Flags flags) {
	SetF(GetF() | flags);
	this->ShowFlags();
}


void Cpu::UnsetFlags(const Cpu::Flags flags) {
	SetF(GetF() & ~flags);
	this->ShowFlags();
}




uint16_t Cpu::ADC16(const uint16_t, const uint16_t) {
	ASSERT_MSG(false, "Not Implemented!");
	return 0;
}

uint16_t Cpu::SBC16(const uint16_t, const uint16_t) {
	ASSERT_MSG(false, "Not Implemented!");
	return 0;
}



uint8_t Cpu::ADC8(const uint8_t val1, const uint8_t val2) {
	const uint16_t result = val1 + val2;
	uint8_t f = 0;
	
	if(result == 0)
		f = FLAG_Z;
	else if(GetHighNibble(result) != GetHighNibble(val1))
		f |= FLAG_H;
	if(result & 0xff00)
		f |= FLAG_C;

	SetF(f);
	ShowFlags();
	return result;
}


uint8_t Cpu::SBC8(const uint8_t val1, const uint8_t val2) {
	const uint16_t result = val1 - val2;
	uint8_t f = FLAG_N;
	
	if(result == 0)
		f |= FLAG_Z;
	else if(GetHighNibble(result) != GetHighNibble(val1)) 
		f |= FLAG_H;
	if(result & 0xff00)
		f |= FLAG_C;

	SetF(f);
	ShowFlags();
	return result;
}




uint8_t Cpu::AddWithZNH(const uint8_t reg, const uint8_t value) {
	const uint8_t result = reg + value;
	uint8_t f = GetF() & FLAG_C;
	
	if(result == 0)
		f |= FLAG_Z;
	else if(GetHighNibble(result) != GetHighNibble(reg)) 
		f |= FLAG_H;
	
	SetF(f);
	ShowFlags();
	return result;
}






uint8_t Cpu::SubWithZNH(const uint8_t reg, const uint8_t value) {
	const uint8_t result = reg - value;
	uint8_t f = GetF() & FLAG_C;
	
	if(result == 0)
		f |= FLAG_Z;
	if(GetHighNibble(result) != GetHighNibble(reg)) 
		f |= FLAG_H;

	SetF(f);
	ShowFlags();
	return result;
}














}
