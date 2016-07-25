#include <stdio.h>
#include <Utix/Assert.h>
#include "Common.h"
#include "Cpu.h"


namespace gbx {







void Cpu::ShowFlags() const {
	const auto f = GetF();
	const auto z = f & FLAG_Z ? 1 : 0;
	const auto n = f & FLAG_N ? 1 : 0;
	const auto h = f & FLAG_H ? 1 : 0;
	const auto c = f & FLAG_C ? 1 : 0;
	printf("CPU FLAGS: Z(%x), N(%x), H(%x), C(%x)\n", z, n, h, c);
}





void Cpu::ADDHL(const uint16_t second) {
	// flags effect: - 0 H C
	const auto first = GetHL();
	const uint32_t result = first + second;
	const uint8_t flags_result = GetFlags(FLAG_Z) | CheckH_11th_bit(first, second) | CheckC_15th_bit(result);
	SetHL(static_cast<uint16_t>(result));
	SetF(flags_result);
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
	
	const uint8_t f = CheckZ(result) | CheckH_3th_bit(first, second) | CheckC_11th_bit(result);
	
	SetF(f);
	return static_cast<uint8_t>(result);
}









uint8_t Cpu::SUB(const uint8_t first, const uint8_t second) {
	// flags effect: Z 1 H C
	const uint16_t result = first - second;
	
	const uint8_t f = CheckZ(result) | CheckH_borrow(first, second) | CheckC_borrow(first, second);

	SetF(f | FLAG_N);
	return static_cast<uint8_t>(result);
}








uint8_t Cpu::INC(uint8_t first) {
	// flags effect: Z 0 H -
	const uint8_t result = first + 1;
	const uint8_t f = CheckZ(result) | CheckH_3th_bit(first, 1) | GetFlags(FLAG_C);
	SetF(f);
	return first;
}








uint8_t Cpu::DEC(uint8_t first) {
	// flags effect: Z 1 H -
	const uint8_t result = first - 1;
	const uint8_t f = CheckZ(result) | FLAG_N | CheckH_borrow(first, 1) | GetFlags(FLAG_C);
	SetF(f);
	return result;
}







uint8_t Cpu::OR(const uint8_t first, const uint8_t second) {
	// flags effect: Z 0 0 0
	const uint8_t result = first | second;
	SetF(CheckZ(result));
	return result;
}








uint8_t Cpu::AND(const uint8_t first, const uint8_t second) {
	// flags effect: Z 0 1 0
	const uint8_t result = first & second;
	SetF(CheckZ(result) | FLAG_H);
	return result;
}








uint8_t Cpu::XOR(const uint8_t first, const uint8_t second) {
	// flags effect: Z 0 0 0
	const uint8_t result = first ^ second;
	SetF(CheckZ(result));
	return result;
}









uint8_t Cpu::SWAP(const uint8_t value) {
	// flags effect: Z 0 0 0
	const uint8_t result = ((value & 0x0f) << 4) | ((value & 0xf0) >> 4);
	SetF(CheckZ(result));
	return result;
}
















}
