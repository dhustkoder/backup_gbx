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








void Memory::AddU8(const uint16_t pointer, const uint8_t value) {
	const uint8_t result = ReadU8(pointer) + value;
	WriteU8(pointer, result);
}






void Memory::SubU8(const uint16_t pointer, const uint8_t value) {
	const uint8_t result = ReadU8(pointer) - value;
	WriteU8(pointer, result);
}















	

}
