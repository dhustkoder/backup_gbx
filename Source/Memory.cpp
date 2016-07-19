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
