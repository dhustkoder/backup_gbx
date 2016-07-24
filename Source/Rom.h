#ifndef GBX_ROM_H_
#define GBX_ROM_H_
#include <Utix/Alloc.h>
#include <Utix/Ints.h>

namespace gbx {


class Rom {
public:
	void Initialize();
	bool Load(const char* file_name);
	void Dispose();
	uint8_t* Data();
	const uint8_t* Data() const;
	size_t GetSize() const;

private:
	uint8_t* const m_data;
};






inline void Rom::Initialize() {
	const_cast<uint8_t*&>(m_data) = nullptr;
}

inline void Rom::Dispose() {
	utix::free_arr(m_data);
}


inline size_t Rom::GetSize() const {
	return utix::arr_size(m_data);
}


inline const uint8_t* Rom::Data() const {
	return m_data;
}


inline uint8_t* Rom::Data() {
	return m_data;
}






























}
#endif