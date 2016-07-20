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




	uint16_t ADC16(uint16_t first, const uint16_t second);
	uint16_t SBC16(uint16_t first, const uint16_t second);
	
	uint8_t ADC8(uint8_t first, const uint8_t second);
	uint8_t SBC8(uint8_t first, const uint8_t second);

	uint8_t ADDWithZNH(const uint8_t first, const uint8_t second);
	uint8_t SUBWithZNH(const uint8_t first, const uint8_t second);
	
	uint8_t ORWithZNHC(const uint8_t first, const uint8_t second);
	uint8_t ANDWithZNHC(const uint8_t first, const uint8_t second);


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

inline void Cpu::AddPC(const uint16_t val) { pc += val; }















}
#endif
