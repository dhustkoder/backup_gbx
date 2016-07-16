#ifndef GBX_COMMON_H_
#define GBX_COMMON_H_

namespace gbx {


inline uint16_t ConcatBytes(const uint8_t high_byte, const uint8_t low_byte) {
	return (high_byte << 8) | low_byte;
}


inline void Split16(const uint16_t value, uint8_t* const high_byte, uint8_t* const low_byte) {
	*high_byte = (value & 0xFF00) >> 8;
	*low_byte = (value & 0x00FF);
}

inline void Add16(const uint16_t val, uint8_t* const high_byte, uint8_t* const low_byte) {
	const auto result = ConcatBytes(*high_byte, *low_byte) + val;
	Split16(result, high_byte, low_byte);
}

inline void Sub16(const uint16_t val, uint8_t* const high_byte, uint8_t* const low_byte) {
	const auto result = ConcatBytes(*high_byte, *low_byte) - val;
	Split16(result, high_byte, low_byte);
}

















}
#endif
