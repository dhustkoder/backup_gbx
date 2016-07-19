#include <stdio.h>
#include "Common.h"
#include "Cpu.h"


namespace gbx {





Cpu::Flags Cpu::GetFlags(const Cpu::Flags flags) const {
	return static_cast<Flags>(this->f & flags);
}


void Cpu::ShowFlags() const {
	const auto z = this->f & FLAG_Z;
	const auto n = this->f & FLAG_N;
	const auto h = this->f & FLAG_H;
	const auto c = this->f & FLAG_C;
	printf("CPU FLAGS: Z(%X), N(%X), H(%X), C(%X)\n", z, n, h, c);
}


void Cpu::SetFlags(const Cpu::Flags flags) {
	this->f |= flags;
	this->ShowFlags();
}


void Cpu::UnsetFlags(const Cpu::Flags flags) {
	this->f &= ~flags;
	this->ShowFlags();
}











uint8_t Cpu::AddWithZNHC(const uint8_t reg, const uint8_t value) {
	const uint16_t result = reg + value;
	this->f = 0;
	
	if(result == 0)
		this->f = FLAG_Z;
	else if(GetHighNibble(result) != GetHighNibble(reg))
		this->f |= FLAG_H;
	if(result & 0xff00)
		this->f |= FLAG_C;

	this->ShowFlags();
	return result;
}






uint8_t Cpu::SubWithZNHC(const uint8_t reg, const uint8_t value) {
	const uint16_t result = reg - value;
	this->f = FLAG_N;
	
	if(result == 0)
		this->f |= FLAG_Z;
	else if(GetHighNibble(result) != GetHighNibble(reg)) 
		this->f |= FLAG_H;
	
	if(result & 0xff00)
		this->f |= FLAG_C;

	this->ShowFlags();
	return result;
}



uint8_t Cpu::AddWithZNH(const uint8_t reg, const uint8_t value) {
	const uint8_t result = reg + value;
	this->f = this->f & FLAG_C;
	
	if(result == 0)
		this->f |= FLAG_Z;
	else if(GetHighNibble(result) != GetHighNibble(reg)) 
		this->f |= FLAG_H;
	
	this->ShowFlags();
	return result;
}


uint8_t Cpu::SubWithZNH(const uint8_t reg, const uint8_t value) {
	const uint8_t result = reg - value;
	this->f = this->f & FLAG_C;
	
	if(result == 0)
		this->f |= FLAG_Z;
	if(GetHighNibble(result) != GetHighNibble(reg)) 
		this->f |= FLAG_H;

	this->ShowFlags();
	return result;
}














}
