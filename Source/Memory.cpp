#include <stdio.h>
#include <Utix/Assert.h>
#include <Utix/Alloc_t.h>
#include "Common.h"
#include "Memory.h"

namespace gbx {



bool Memory::Initialize() {
	
	const_cast<uint8_t*&>(m_data) = utix::malloc_t<uint8_t>(TOTAL_RAM_SIZE);
	
	if(!m_data) {
		perror("Memory::Initialize: Couldn't allocate memory");
		return false;
	}

	return true;
}



void Memory::Dispose() {
	ASSERT_MSG(m_data!=nullptr, "attempt to free nullptr");
	free(m_data);
}









int8_t Memory::ReadS8(const uint16_t pointer) const {
	// TODO: this might not be totally portable 
	return static_cast<int8_t>(ReadU8(pointer));
}



uint8_t Memory::ReadU8(const uint16_t pointer) const {
	return m_data[pointer];
}



uint16_t Memory::ReadU16(const uint16_t pointer) const {
	return ConcatBytes(m_data[pointer+1], m_data[pointer]);
}




void Memory::ReadU16(const uint16_t pointer, uint8_t* const high_byte, uint8_t* const low_byte) const {
	*high_byte = m_data[pointer+1];
	*low_byte = m_data[pointer];
}




void Memory::WriteU8(const uint16_t pointer, const uint8_t value) {
	m_data[pointer] = value;
}




void Memory::WriteU16(const uint16_t pointer, const uint16_t value) {
	Split16(value, &m_data[pointer+1], &m_data[pointer]);
}




void Memory::WriteU16(const uint16_t pointer, const uint8_t high_byte, const uint8_t low_byte) {
	WriteU8(pointer+1, high_byte);
	WriteU8(pointer, low_byte);
}






void Memory::AddU8(const uint16_t pointer, const uint8_t value) {
	const uint8_t result = ReadU8(pointer) + value;
	WriteU8(pointer, result);
}






void Memory::SubU8(const uint16_t pointer, const uint8_t value) {
	const uint8_t result = ReadU8(pointer) - value;
	WriteU8(pointer, result);
}





const uint8_t* Memory::Data() const {
	return m_data;
}





uint8_t* Memory::Data() {
	return m_data;
}









	

}
