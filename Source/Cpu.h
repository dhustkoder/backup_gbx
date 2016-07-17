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
	
	enum class Flags : uint8_t {
		Z = 0x80, N = 0x40, H = 0x20, C = 0x10
	};


	uint16_t GetBC() const;
	uint16_t GetDE() const;
	uint16_t GetHL() const;
	bool GetFlags(const Cpu::Flags flags) const;
	void ShowFlags() const;

	void SetBC(const uint16_t val);
	void SetDE(const uint16_t val);
	void SetHL(const uint16_t val);
	void AddBC(const uint16_t val);
	void AddDE(const uint16_t val);
	void AddHL(const uint16_t val);
	void SubBC(const uint16_t val);
	void SubDE(const uint16_t val);
	void SubHL(const uint16_t val);

	void SetFlags(const Cpu::Flags flags);
	void UnsetFlags(const Cpu::Flags flags);

	uint16_t pc;
	uint16_t sp;
	uint8_t op;
	uint8_t A, F; 
	uint8_t B, C; 
	uint8_t D, E;
	uint8_t H, L;
};


constexpr Cpu::Flags operator|(const Cpu::Flags f1, const Cpu::Flags f2) {
	return static_cast<Cpu::Flags>(static_cast<uint8_t>(f1) | static_cast<uint8_t>(f2));
}

constexpr Cpu::Flags operator&(const Cpu::Flags f1, const Cpu::Flags f2) {
	return static_cast<Cpu::Flags>(static_cast<uint8_t>(f1) & static_cast<uint8_t>(f2));
}


constexpr uint8_t operator|(uint8_t value, Cpu::Flags f) {
	return value | static_cast<uint8_t>(f);
}

constexpr uint8_t operator&(uint8_t value, Cpu::Flags f) {
	return value & static_cast<uint8_t>(f);
}













}
#endif
