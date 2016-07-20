#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "Memory.h"

namespace gbx {



bool Memory::Initialize(const size_t ram_size) {
	
	const_cast<uint8_t*&>(m_data) = static_cast<uint8_t*>( malloc(ram_size) );
	
	if(!m_data) {
		perror("Memory::Initialize: Couldn't allocate memory");
		return false;
	}
	
	// Common GB init memory registers
	Write8(0xFF05, 0x00); // TIMA
	Write8(0xFF06, 0x00); // TMA
	Write8(0xFF07, 0x00); // TAC
	Write8(0xFF10, 0x80); // NR10
	Write8(0xFF11, 0xBF); // NR11
	Write8(0xFF12, 0xF3); // NR12
	Write8(0xFF14, 0xBF); // NR14
	Write8(0xFF16, 0x3F); // NR21
	Write8(0xFF17, 0x00); // NR22
	Write8(0xFF19, 0xBF); // NR24
	Write8(0xFF1A, 0x7F); // NR30
	Write8(0xFF1B, 0xFF); // NR31
	Write8(0xFF1C, 0x9F); // NR32
	Write8(0xFF1E, 0xBF); // NR33
	Write8(0xFF20, 0xFF); // NR41
	Write8(0xFF21, 0x00); // NR42
	Write8(0xFF22, 0x00); // NR43
	Write8(0xFF23, 0xBF); // NR30
	Write8(0xFF24, 0x77); // NR50
	Write8(0xFF25, 0xF3); // NR51
	Write8(0xFF26, 0xF1); // NR52
	Write8(0xFF40, 0x91); // LCDC
	Write8(0xFF42, 0x00); // SCY
	Write8(0xFF43, 0x00); // SCX
	Write8(0xFF45, 0x00); // LYC
	Write8(0xFF47, 0xFC); // BGP
	Write8(0xFF48, 0xFF); // OBP0
	Write8(0xFF49, 0xFF); // OBP1
	Write8(0xFF4A, 0x00); // WY
	Write8(0xFF4B, 0x00); // WX
	Write8(0xFFFF, 0x00); // IE
	
	return true;
}

void Memory::Dispose() {
	free(m_data);
}


uint8_t Memory::Read8(const uint16_t pointer) const {
	return m_data[pointer];
}

uint16_t Memory::Read16(const uint16_t pointer) const {
	return ConcatBytes(m_data[pointer+1], m_data[pointer]);
}


void Memory::Read16(const uint16_t pointer, uint8_t* const high_byte, uint8_t* const low_byte) const {
	*high_byte = m_data[pointer+1];
	*low_byte = m_data[pointer];
}


void Memory::Write8(const uint16_t pointer, const uint8_t value) {
	m_data[pointer] = value;
}


void Memory::Write16(const uint16_t pointer, const uint16_t value) {
	Split16(value, &m_data[pointer+1], &m_data[pointer]);
}


void Memory::Write16(const uint16_t pointer, const uint8_t high_byte, const uint8_t low_byte) {
	Write8(pointer+1, high_byte);
	Write8(pointer, low_byte);
}



void Memory::Add8(const uint16_t pointer, const uint8_t val) {
	const auto result = Read8(pointer) + val;
	Write8(pointer, result);
}

void Memory::Add16(const uint16_t pointer, const uint16_t val) {
	const auto result = Read16(pointer) + val;
	Write16(pointer, result);
}


void Memory::Sub8(const uint16_t pointer, const uint8_t val) {
	const auto result = Read8(pointer) - val;
	Write8(pointer, result);
}



void Memory::Sub16(const uint16_t pointer, const uint16_t val) {
	const auto result = Read16(pointer) - val;
	Write16(pointer, result);
}






















	
}
