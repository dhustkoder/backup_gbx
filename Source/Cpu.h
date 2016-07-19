#ifndef GBX_CPU_H_
#define GBX_CPU_H_
#include "Common.h"

namespace gbx {

struct Cpu {
	Cpu()=delete;
	Cpu(Cpu&)=delete;
	Cpu(Cpu&&)=delete;
	~Cpu()=delete;
	Cpu&operator=(Cpu&)=delete;
	Cpu&operator=(Cpu&&)=delete;
	
	enum Flags : uint8_t {
		FLAG_Z = 0x80, FLAG_N = 0x40, FLAG_H = 0x20, FLAG_C = 0x10
	};


	Flags GetFlags(const Cpu::Flags flags) const;
	void ShowFlags() const;

	uint16_t ADC16(const uint16_t val1, const uint16_t val2);
	uint16_t SBC16(const uint16_t val1, const uint16_t val2);

	uint8_t ADC8(const uint8_t val1, const uint8_t val2);
	uint8_t SBC8(const uint8_t val1, const uint8_t val2);

	uint8_t AddWithZNH(const uint8_t reg, const uint8_t value);
	uint8_t SubWithZNH(const uint8_t reg, const uint8_t value);

	void SetFlags(const Cpu::Flags flags);
	void UnsetFlags(const Cpu::Flags flags);

	uint16_t pc;
	uint16_t sp;
	uint8_t op;
	
	union {
		struct {
			uint8_t f, a; 
		};
		uint16_t af;
	};

	union {
		struct {
			uint8_t c, b; 
		};
		uint16_t bc;
	};

	union {
		struct {
			uint8_t e, d; 
		};
		uint16_t de;
	};

	union {
		struct {
			uint8_t l, h; 
		};
		uint16_t hl;
	};
};








}
#endif
