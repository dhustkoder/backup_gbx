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





















}
