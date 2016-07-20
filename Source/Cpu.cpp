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
	printf("| CPU FLAGS: Z(%x), N(%x), H(%x), C(%x) | ", z, n, h, c);
}


void Cpu::SetFlags(const Cpu::Flags flags) {
	SetF(GetF() | flags);
	this->ShowFlags();
}


void Cpu::UnsetFlags(const Cpu::Flags flags) {
	SetF(GetF() & ~flags);
	this->ShowFlags();
}




uint16_t Cpu::ADC16(uint16_t, const uint16_t) {
	ASSERT_MSG(false, "Not Implemented!");
	return 0;
}

uint16_t Cpu::SBC16(uint16_t, const uint16_t) {
	ASSERT_MSG(false, "Not Implemented!");
	return 0;
}



uint8_t Cpu::ADC8(uint8_t first, const uint8_t second) {
	if(GetFlags(FLAG_C))
		++first;
	
	const uint16_t result = first + second;
	uint8_t f = 0;
	
	if(result == 0)
		f = FLAG_Z;
	else if(GetHighNibble(result) != GetHighNibble(first))
		f |= FLAG_H;
	if(result & 0xff00)
		f |= FLAG_C;

	SetF(f);
	ShowFlags();
	return result;
}




uint8_t Cpu::SBC8(uint8_t first, const uint8_t second) {
	if(GetFlags(FLAG_C))
		--first;
		
	const uint16_t result = first - second;
	uint8_t f = FLAG_N;
	
	if(result == 0)
		f |= FLAG_Z;
	else if(GetHighNibble(result) != GetHighNibble(first)) 
		f |= FLAG_H;
	if(result & 0xff00)
		f |= FLAG_C;

	SetF(f);
	ShowFlags();
	return result;
}




uint8_t Cpu::ADDWithZNH(const uint8_t first, const uint8_t second) {
	const uint8_t result = first + second;
	uint8_t f = GetF() & FLAG_C;
	
	if(result == 0)
		f |= FLAG_Z;
	else if(GetHighNibble(result) != GetHighNibble(first)) 
		f |= FLAG_H;
	
	SetF(f);
	ShowFlags();
	return result;
}






uint8_t Cpu::SUBWithZNH(const uint8_t first, const uint8_t second) {
	const uint8_t result = first - second;
	uint8_t f = GetF() & FLAG_C;
	
	if(result == 0)
		f |= FLAG_Z;
	if(GetHighNibble(result) != GetHighNibble(first)) 
		f |= FLAG_H;

	SetF(f);
	ShowFlags();
	return result;
}




uint8_t Cpu::ORWithZNHC(const uint8_t first, const uint8_t second) {
	// flags effect: Z 0 0 0
	const auto result = first | second;
	SetF( result == 0 ? FLAG_Z : 0 );
	ShowFlags();
	return result;
}



uint8_t Cpu::ANDWithZNHC(const uint8_t first, const uint8_t second) {
	// flags effect: Z 0 1 0
	const auto result = first & second;
	SetF( result == 0 ? (FLAG_Z | FLAG_H) : FLAG_H);
	return result;
}







}
