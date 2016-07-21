#include <stdio.h>
#include <Utix/Assert.h>
#include "Common.h"
#include "Cpu.h"


namespace gbx {


inline Cpu::Flags CheckZH(uint16_t result, uint8_t first, int16_t second) {
	uint8_t f = 0;
	
	if(((first&0xf)+(second&0xf) > 0xf))
		f = Cpu::FLAG_H;
	if(!result)
		f |= Cpu::FLAG_Z;
	
	return static_cast<Cpu::Flags>(f);
}



inline Cpu::Flags CheckZHC(uint16_t result, uint8_t first, int16_t second) {
	uint8_t f = 0;
	
	if(((first&0xf)+(second&0xf) > 0xf))
		f = Cpu::FLAG_H;
	if(!result)
		f |= Cpu::FLAG_Z;
	else if(result & 0xff00)
		f |= Cpu::FLAG_C;
	
	return static_cast<Cpu::Flags>(f);
}







Cpu::Flags Cpu::GetFlags(const Cpu::Flags flags) const {
	return static_cast<Flags>(GetF() & flags);
}







void Cpu::ShowFlags() const {
	const auto f = GetF();
	const auto z = f & FLAG_Z ? 1 : 0;
	const auto n = f & FLAG_N ? 1 : 0;
	const auto h = f & FLAG_H ? 1 : 0;
	const auto c = f & FLAG_C ? 1 : 0;
	printf("CPU FLAGS: Z(%x), N(%x), H(%x), C(%x)\n", z, n, h, c);
}







void Cpu::SetFlags(const Cpu::Flags flags) {
	SetF(GetF() | flags);
}






void Cpu::UnsetFlags(const Cpu::Flags flags) {
	SetF(GetF() & ~flags);
}







uint8_t Cpu::INC(uint8_t value) {
	// flags effect: Z 0 H -
	SetF(GetF() & FLAG_C);
	if(((value&0xf)+1) > 0xf)
		SetFlags(FLAG_H);
	if(!++value)
		SetFlags(FLAG_Z);
	
	return value;
}








uint8_t Cpu::DEC(uint8_t value) {
	// flags effect: Z 1 H -
	SetF((GetF() & FLAG_C) | FLAG_N);
	if(((value&0xf)-1) > 0xf)
		SetFlags(FLAG_H);
	if(!--value)
		SetFlags(FLAG_Z);
	
	return value;
}











uint8_t Cpu::ADC(uint8_t first, const uint8_t second) {
	// flags effect: Z 0 H C
	if(GetFlags(FLAG_C))
		++first;
	
	return ADD(first, second);
}









uint8_t Cpu::SBC(uint8_t first, const uint8_t second) {
	// flags effect: Z 1 H C
	if(GetFlags(FLAG_C))
		--first;
		
	return SUB(first, second);
}








uint8_t Cpu::ADD(const uint8_t first, const uint8_t second) {
	// flags effect Z 0 H C
	const uint16_t result = first + second;
	
	const auto f = CheckZHC(result, first, second);
	
	SetF(f);
	return static_cast<uint8_t>(result);
}









uint8_t Cpu::SUB(const uint8_t first, const uint8_t second) {
	// flags effect: Z 1 H C
	const uint16_t result = first - second;
	
	const auto f = CheckZHC(result, first, -second);

	SetF(f | FLAG_N);
	return static_cast<uint8_t>(result);
}









uint8_t Cpu::OR(const uint8_t first, const uint8_t second) {
	// flags effect: Z 0 0 0
	const uint8_t result = first | second;
	SetF( result == 0 ? FLAG_Z : 0 );
	return result;
}







uint8_t Cpu::AND(const uint8_t first, const uint8_t second) {
	// flags effect: Z 0 1 0
	const uint8_t result = first & second;
	SetF( result == 0 ? (FLAG_Z | FLAG_H) : FLAG_H);
	return result;
}







uint8_t Cpu::XOR(const uint8_t first, const uint8_t second) {
	// flags effect: Z 0 0 0
	const uint8_t result = first ^ second;
	SetF(result == 0 ?  FLAG_Z : 0 );
	return result;
}










}
