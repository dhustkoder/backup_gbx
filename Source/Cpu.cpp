#include <stdio.h>
#include "Common.h"
#include "Cpu.h"


namespace gbx {





uint16_t Cpu::GetBC() const {
	return ConcatBytes(B, C);
}

uint16_t Cpu::GetDE() const {
	return ConcatBytes(D, E);	
}

uint16_t Cpu::GetHL() const {
	return ConcatBytes(H, L);
}


Cpu::Flags Cpu::GetFlags(const Cpu::Flags flags) const {
	return static_cast<Flags>(this->F & flags);
}


void Cpu::ShowFlags() const {
	const auto z = F & FLAG_Z;
	const auto n = F & FLAG_N;
	const auto h = F & FLAG_H;
	const auto c = F & FLAG_C;
	printf("CPU FLAGS: Z(%X), N(%X), H(%X), C(%X)\n", z, n, h, c);
}


void Cpu::SetFlags(const Cpu::Flags flags) {
	this->F |= flags;
	this->ShowFlags();
}


void Cpu::UnsetFlags(const Cpu::Flags flags) {
	this->F &= ~flags;
	this->ShowFlags();
}



void Cpu::SetBC(const uint16_t value) {
	Split16(value, &this->B, &this->C);
}

void Cpu::SetDE(const uint16_t value) {
	Split16(value, &this->D, &this->E);
}

void Cpu::SetHL(const uint16_t value) {
	Split16(value, &this->H, &this->L);
}


void Cpu::AddBC(const uint16_t value) {
	Add16(value, &this->B, &this->C);
}


void Cpu::AddDE(const uint16_t val) {
	Add16(val, &this->D, &this->E);
}

void Cpu::AddHL(const uint16_t val) {
	Add16(val, &this->H, &this->L);
}



void Cpu::SubBC(const uint16_t val) {
	Sub16(val, &this->B, &this->C);
}

void Cpu::SubDE(const uint16_t val) {
	Sub16(val, &this->D, &this->E);
}

void Cpu::SubHL(const uint16_t val) {
	Sub16(val, &this->H, &this->L);
}








uint8_t Cpu::AddWithZNHC(const uint8_t reg, const uint8_t value) {
	const uint16_t result = reg + value;
	this->F = 0;
	
	if(result == 0)
		this->F = FLAG_Z;
	else if(GetHighNibble(result) != GetHighNibble(reg))
		this->F |= FLAG_H;
	if(result & 0xff00)
		this->F |= FLAG_C;

	this->ShowFlags();
	return result;
}






uint8_t Cpu::SubWithZNHC(const uint8_t reg, const uint8_t value) {
	const uint16_t result = reg - value;
	this->F = FLAG_N;
	
	if(result == 0)
		this->F |= FLAG_Z;
	else if(GetHighNibble(result) != GetHighNibble(reg)) 
		this->F |= FLAG_H;
	
	if(result & 0xff00)
		this->F |= FLAG_C;

	this->ShowFlags();
	return result;
}



uint8_t Cpu::AddWithZNH(const uint8_t reg, const uint8_t value) {
	const uint8_t result = reg + value;
	this->F = this->F & FLAG_C;
	
	if(result == 0)
		this->F |= FLAG_Z;
	else if(GetHighNibble(result) != GetHighNibble(reg)) 
		this->F |= FLAG_H;
	
	this->ShowFlags();
	return result;
}


uint8_t Cpu::SubWithZNH(const uint8_t reg, const uint8_t value) {
	const uint8_t result = reg - value;
	this->F = this->F & FLAG_C;
	
	if(result == 0)
		this->F |= FLAG_Z;
	if(GetHighNibble(result) != GetHighNibble(reg)) 
		this->F |= FLAG_H;

	this->ShowFlags();
	return result;
}














}
