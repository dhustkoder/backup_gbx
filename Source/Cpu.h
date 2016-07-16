#ifndef GBX_CPU_H_
#define GBX_CPU_H_
#include "Common.h"

namespace gbx {

struct Cpu {
	
	enum class Flags : uint8_t {
		Z = 0x80, N = 0x40, H = 0x20, C = 0x10
	};

	Cpu()=delete;
	Cpu(Cpu&)=delete;
	Cpu(Cpu&&)=delete;
	Cpu&operator=(Cpu&)=delete;
	Cpu&operator=(Cpu&&)=delete;


	uint16_t GetBC() const;
	uint16_t GetDE() const;
	uint16_t GetHL() const;
	bool GetFlags(Cpu::Flags flags) const;

	void SetBC(uint16_t val);
	void SetDE(uint16_t val);
	void SetHL(uint16_t val);
	void AddBC(uint16_t val);
	void AddDE(uint16_t val);
	void AddHL(uint16_t val);
	void SubBC(uint16_t val);
	void SubDE(uint16_t val);
	void SubHL(uint16_t val);

	void SetFlags(Cpu::Flags flags);
	void UnsetFlags(Cpu::Flags flags);

	uint16_t pc;
	uint16_t sp;
	uint8_t op;
	uint8_t A, F; 
	uint8_t B, C; 
	uint8_t D, E;
	uint8_t H, L;
};


constexpr Cpu::Flags operator|(Cpu::Flags f1, Cpu::Flags f2) {
	return static_cast<Cpu::Flags>(static_cast<uint8_t>(f1) | static_cast<uint8_t>(f2));
}

constexpr Cpu::Flags operator&(Cpu::Flags f1, Cpu::Flags f2) {
	return static_cast<Cpu::Flags>(static_cast<uint8_t>(f1) & static_cast<uint8_t>(f2));
}


inline uint16_t Cpu::GetBC() const {
	return ConcatBytes(B, C);
}

inline uint16_t Cpu::GetDE() const {
	return ConcatBytes(D, E);	
}

inline uint16_t Cpu::GetHL() const {
	return ConcatBytes(H, L);
}


inline bool Cpu::GetFlags(Cpu::Flags flags) const {
	return (this->F & static_cast<uint8_t>(flags)) != 0;
}


inline void Cpu::SetFlags(Cpu::Flags flags) {
	this->F |= static_cast<uint8_t>(flags);
}


inline void Cpu::UnsetFlags(Cpu::Flags flags) {
	this->F ^= static_cast<uint8_t>(flags);
}



inline void Cpu::SetBC(const uint16_t value) {
	Split16(value, &this->B, &this->C);
}

inline void Cpu::SetDE(const uint16_t value) {
	Split16(value, &this->D, &this->E);
}

inline void Cpu::SetHL(const uint16_t value) {
	Split16(value, &this->H, &this->L);
}


inline void Cpu::AddBC(const uint16_t val) {
	Add16(val, &this->B, &this->C);
}

inline void Cpu::AddDE(const uint16_t val) {
	Add16(val, &this->D, &this->E);
}

inline void Cpu::AddHL(const uint16_t val) {
	Add16(val, &this->H, &this->L);
}



inline void Cpu::SubBC(const uint16_t val) {
	Sub16(val, &this->B, &this->C);
}

inline void Cpu::SubDE(const uint16_t val) {
	Sub16(val, &this->D, &this->E);
}

inline void Cpu::SubHL(const uint16_t val) {
	Sub16(val, &this->H, &this->L);
}

















}
#endif
