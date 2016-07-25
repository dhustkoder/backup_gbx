#ifndef GBX_CARTRIDGE_H_
#define GBX_CARTRIDGE_H_
#include <Utix/Ints.h>

namespace gbx {



enum class CartridgeType {
	ROM_ONLY = 0x0,
	ROM_MBC1 = 0x1,
	ROM_MBC1_RAM = 0x2,
	ROM_MBC1_RAM_BATT = 0x3,
	ROM_MBC = 0x5,
	ROM_MBC2_BATT = 0x6,
	ROM_RAM = 0x8,
	ROM_RAM_BATT = 0x9,
	ROM_MMM01 = 0xB,
	ROM_MMM01_SRAM = 0xC,
	ROM_MMM01_SRAM_BATT = 0xD,
	ROM_MBC3_TIMER_BATT = 0xF,
	ROM_MBC3_TIMER_RAM_BATT = 0x10,
	ROM_MBC3 = 0x11,
	ROM_MBC3_RAM = 0x12,
	ROM_MBC3_RAM_BATT = 0x13,
	ROM_MBC5 = 0x19,
	ROM_MBC5_RAM = 0x1A,
	ROM_MBC5_RAM_BATT = 0x1B,
	ROM_MBC5_RUMBLE = 0x1C,
	ROM_MBC5_RUMBLE_SRAM = 0x1D,
	ROM_MBC5_RUMBLE_SRAM_BATT = 0x1E,
	POCKET_CAMERA = 0x1F,
	BANDAI_TAMA5 = 0xFD,
	HUDSON_HUC_3 = 0xFE,
	Hudson_HUC_3 = 0xFF
};

enum class GameBoyType {
	GAMEBOY, GAMEBOY_COLOR, SUPER_GAMEBOY
};






class Cartridge {
public:
	Cartridge()=delete;
	~Cartridge()=delete;
	Cartridge(const Cartridge&)=delete;
	Cartridge(Cartridge&&)=delete;
	Cartridge&operator=(Cartridge&)=delete;


	void Initialize();
	bool Load(const char* file_name);
	void Dispose();
	const uint8_t* Data() const;
	const char* GetName() const;
	GameBoyType GetGameBoyType() const;
	CartridgeType GetType() const;
	size_t GetSize() const;
	uint8_t* Data();

private:
	uint8_t* const m_data;
};






inline void Cartridge::Initialize() {
	const_cast<uint8_t*&>(m_data) = nullptr;
}



inline CartridgeType Cartridge::GetType() const {
	return static_cast<CartridgeType>(m_data[0x147]);
}





inline const uint8_t* Cartridge::Data() const {
	return m_data;
}



inline uint8_t* Cartridge::Data() {
	return m_data;
}






















}
#endif
