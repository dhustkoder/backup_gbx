#ifndef GBX_CARTRIDGE_H_
#define GBX_CARTRIDGE_H_
#include <Utix/Alloc.h>
#include <Utix/Ints.h>

namespace gbx {
	/*
	0147       Cartridge type:
           0 - ROM ONLY                12 - ROM+MBC3+RAM
           1 - ROM+MBC1                13 - ROM+MBC3+RAM+BATT
           2 - ROM+MBC1+RAM            19 - ROM+MBC5
           3 - ROM+MBC1+RAM+BATT       1A - ROM+MBC5+RAM
           5 - ROM+MBC                 1B - ROM+MBC5+RAM+BATT
           6 - ROM+MBC2+BATTERY        1C - ROM+MBC5+RUMBLE
           8 - ROM+RAM                 1D - ROM+MBC5+RUMBLE+SRAM
           9 - ROM+RAM+BATTERY         1E - ROM+MBC5+RUMBLE+SRAM+BATT
           B - ROM+MMM01               1F - Pocket Camera
           C - ROM+MMM01+SRAM          FD - Bandai TAMA5
           D - ROM+MMM01+SRAM+BATT     FE - Hudson HuC-3
           F - ROM+MBC3+TIMER+BATT     FF - Hudson HuC-1
          10 - ROM+MBC3+TIMER+RAM+BATT
          11 - ROM+MBC3
	
	
	*/


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


inline void Cartridge::Dispose() {
	utix::free_arr(m_data);
	const_cast<uint8_t*&>(m_data) = nullptr;
}


inline size_t Cartridge::GetSize() const {
	return utix::arr_size(m_data);
}


inline const uint8_t* Cartridge::Data() const {
	return m_data;
}



inline CartridgeType Cartridge::GetType() const {
	return static_cast<CartridgeType>(m_data[0x147]);
}



inline uint8_t* Cartridge::Data() {
	return m_data;
}






















}
#endif