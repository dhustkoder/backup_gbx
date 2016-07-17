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


bool Cpu::GetFlags(const Cpu::Flags flags) const {
	return (this->F & static_cast<uint8_t>(flags)) != 0;
}


void Cpu::ShowFlags() const {
	const auto z = F & Cpu::Flags::Z;
	const auto n = F & Cpu::Flags::N;
	const auto h = F & Cpu::Flags::H;
	const auto c = F & Cpu::Flags::C;
	printf("CPU FLAGS: Z(%X), N(%X), H(%X), C(%X)\n", z, n, h, c);
}


void Cpu::SetFlags(const Cpu::Flags flags) {
	this->F |= static_cast<uint8_t>(flags);
	this->ShowFlags();
}


void Cpu::UnsetFlags(const Cpu::Flags flags) {
	this->F &= ~static_cast<uint8_t>(flags);
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




















}
