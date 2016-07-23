#ifndef GBX_CPU_H_
#define GBX_CPU_H_
#include "Common.h"

namespace gbx {

class Cpu {
public:
	Cpu()=delete;
	~Cpu()=delete;
	Cpu(Cpu&)=delete;
	Cpu(Cpu&&)=delete;
	Cpu&operator=(Cpu&)=delete;
	Cpu&operator=(Cpu&&)=delete;
	
	enum Flags : uint8_t {
		FLAG_Z = 0x80, FLAG_N = 0x40, FLAG_H = 0x20, FLAG_C = 0x10
	};

	uint8_t GetA() const;
	uint8_t GetF() const;
	uint8_t GetB() const;
	uint8_t GetC() const;
	uint8_t GetD() const;
	uint8_t GetE() const;
	uint8_t GetH() const;
	uint8_t GetL() const;

	uint8_t GetOP() const;
	uint16_t GetPC() const;
	uint16_t GetSP() const;
	uint16_t GetAF() const;
	uint16_t GetBC() const;
	uint16_t GetDE() const;
	uint16_t GetHL() const;

	Flags GetFlags(const Cpu::Flags flags) const;
	void ShowFlags() const;


	void SetA(const uint8_t val);
	void SetF(const uint8_t val);
	void SetB(const uint8_t val);
	void SetC(const uint8_t val);
	void SetD(const uint8_t val);
	void SetE(const uint8_t val);
	void SetH(const uint8_t val);
	void SetL(const uint8_t val);

	void SetOP(const uint8_t val);
	void SetPC(const uint16_t val);
	void SetSP(const uint16_t val);
	void SetAF(const uint16_t val);
	void SetBC(const uint16_t val);
	void SetDE(const uint16_t val);
	void SetHL(const uint16_t val);


	void AddPC(const uint16_t val);



	void SetFlags(const Cpu::Flags flags);
	void UnsetFlags(const Cpu::Flags flags);


	void ADDHL(const uint16_t reg_pair);

	uint8_t INC(uint8_t first);
	uint8_t DEC(uint8_t first);
	
	uint8_t ADC(uint8_t first, const uint8_t second);
	uint8_t SBC(uint8_t first, const uint8_t second);

	uint8_t ADD(const uint8_t first, const uint8_t second);
	uint8_t SUB(const uint8_t first, const uint8_t second);
	
	
	uint8_t OR(const uint8_t first, const uint8_t second);
	uint8_t AND(const uint8_t first, const uint8_t second);
	uint8_t XOR(const uint8_t first, const uint8_t second);
	
	uint8_t SWAP(const uint8_t value);
	

private:
	uint16_t pc;
	uint16_t sp;
	uint8_t op;

	// TODO: check endianess, this is only compatible with little endian
	union {
		struct {
			uint8_t f, a; 
		}bytes;
		uint16_t pair;
	}af;

	union {
		struct {
			uint8_t c, b; 
		}bytes;
		uint16_t pair;
	}bc;

	union {
		struct {
			uint8_t e, d; 
		}bytes;
		uint16_t pair;
	}de;

	union {
		struct {
			uint8_t l, h; 
		}bytes;
		uint16_t pair;
	}hl;
	
};











inline uint8_t CheckZ(uint32_t result) {
	return result ? 0 : Cpu::FLAG_Z;
}




inline uint8_t CheckH_3th_bit(uint8_t first, uint8_t second) {
	return (((first&0x0f) + (second&0x0f)) & 0x10) ? Cpu::FLAG_H : 0;
}




inline uint8_t CheckH_11th_bit(uint16_t first, uint16_t second) {
	return (((first&0xf00) + (second&0xf00)) & 0x1000) ? Cpu::FLAG_H : 0;
}




inline uint8_t CheckC_11th_bit(uint16_t result) {
	return (result & 0xff00) ? Cpu::FLAG_C : 0;
}




inline uint8_t CheckC_15th_bit(uint32_t result) {
	return (result & 0xffff0000) ? Cpu::FLAG_C : 0;
}





inline uint8_t CheckC_borrow(uint8_t first, uint8_t second) {
	return first < second ? Cpu::FLAG_C : 0;
}




inline uint8_t CheckH_borrow(uint8_t first, uint8_t second) {
	return (((first&0xf) - (second&0xf)) & 0x10) ? Cpu::FLAG_H : 0;
}














inline uint8_t Cpu::GetA() const { return af.bytes.a; }
inline uint8_t Cpu::GetF() const { return af.bytes.f; }
inline uint8_t Cpu::GetB() const { return bc.bytes.b; }
inline uint8_t Cpu::GetC() const { return bc.bytes.c; }
inline uint8_t Cpu::GetD() const { return de.bytes.d; }
inline uint8_t Cpu::GetE() const { return de.bytes.e; }
inline uint8_t Cpu::GetH() const { return hl.bytes.h; }
inline uint8_t Cpu::GetL() const { return hl.bytes.l; }

inline uint8_t Cpu::GetOP() const  { return op; }
inline uint16_t Cpu::GetPC() const { return pc; }
inline uint16_t Cpu::GetSP() const { return sp; }
inline uint16_t Cpu::GetAF() const { return af.pair; } 
inline uint16_t Cpu::GetBC() const { return bc.pair; }
inline uint16_t Cpu::GetDE() const { return de.pair; }
inline uint16_t Cpu::GetHL() const { return hl.pair; }

inline Cpu::Flags Cpu::GetFlags(const Cpu::Flags flags) const {
	return static_cast<Flags>(GetF() & flags);
}





inline void Cpu::SetA(const uint8_t val) { af.bytes.a = val; }
inline void Cpu::SetF(const uint8_t val) { af.bytes.f = val; }
inline void Cpu::SetB(const uint8_t val) { bc.bytes.b = val; }
inline void Cpu::SetC(const uint8_t val) { bc.bytes.c = val; }
inline void Cpu::SetD(const uint8_t val) { de.bytes.d = val; }
inline void Cpu::SetE(const uint8_t val) { de.bytes.e = val; }
inline void Cpu::SetH(const uint8_t val) { hl.bytes.h = val; }
inline void Cpu::SetL(const uint8_t val) { hl.bytes.l = val; }

inline void Cpu::SetOP(const uint8_t val)  { op = val; }
inline void Cpu::SetPC(const uint16_t val) { pc = val; }
inline void Cpu::SetSP(const uint16_t val) { sp = val; }
inline void Cpu::SetAF(const uint16_t val) { af.pair = val; } 
inline void Cpu::SetBC(const uint16_t val) { bc.pair = val; }
inline void Cpu::SetDE(const uint16_t val) { de.pair = val; }
inline void Cpu::SetHL(const uint16_t val) { hl.pair = val; }

inline void Cpu::SetFlags(const Cpu::Flags flags) {
	SetF(GetF() | flags);
}

inline void Cpu::UnsetFlags(const Cpu::Flags flags) {
	SetF(GetF() & ~flags);
}



inline void Cpu::AddPC(const uint16_t val) { pc += val; }






inline void Cpu::ADDHL(const uint16_t second) {
	// flags effect: - 0 H C
	const auto hl = GetHL();
	const uint32_t result = hl + second;
	const uint8_t flags_result = GetFlags(FLAG_Z) | CheckH_11th_bit(hl, second) | CheckC_15th_bit(result);
	SetHL(static_cast<uint16_t>(result));
	SetF(flags_result);
}








inline uint8_t Cpu::INC(uint8_t first) {
	// flags effect: Z 0 H -
	const uint8_t result = first + 1;
	const uint8_t f = CheckZ(result) | CheckH_3th_bit(first, 1) | GetFlags(FLAG_C);
	SetF(f);
	return first;
}




inline uint8_t Cpu::DEC(uint8_t first) {
	// flags effect: Z 1 H -
	const uint8_t result = first - 1;
	const uint8_t f = CheckZ(result) | FLAG_N | CheckH_borrow(first, 1) | GetFlags(FLAG_C);
	SetF(f);
	return result;
}










inline uint8_t Cpu::OR(const uint8_t first, const uint8_t second) {
	// flags effect: Z 0 0 0
	const uint8_t result = first | second;
	SetF( CheckZ(result) );
	return result;
}






inline uint8_t Cpu::AND(const uint8_t first, const uint8_t second) {
	// flags effect: Z 0 1 0
	const uint8_t result = first & second;
	SetF(CheckZ(result) | FLAG_H);
	return result;
}






inline uint8_t Cpu::XOR(const uint8_t first, const uint8_t second) {
	// flags effect: Z 0 0 0
	const uint8_t result = first ^ second;
	SetF(CheckZ(result));
	return result;
}







inline uint8_t Cpu::SWAP(const uint8_t value) {
	// flags effect: Z 0 0 0
	const uint8_t result = ((value & 0x0f) << 4) | ((value & 0xf0) >> 4);
	SetF(CheckZ(result));
	return result;
}











}
#endif
