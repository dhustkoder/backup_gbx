#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Utix/BaseTraits.h>
#include <Utix/ScopeExit.h>
#include "Instructions.h"
#include "Machine.h"

namespace gbx {


// based on http://marc.rawer.de/Gameboy/
/* MEMORY MAP:

		|...............| 0xFFFF
		|_______________| 0xFFFE
		|  WORK & STACK |
		|      AREA     |
		|_______________| 0xFF80
		| SOUND CONTROL |
		|    REGISTER   |
		|_______________|
		|  LCDC CONTROL |
		|   REGISTER    |
		|_______________|
		|    PORT/MODE  |
		|    REGISTER   |
		|_______________| 0xFF00
		|     OAM RAM   |
		|_______________| 0xFE00
		|       -       |
		|_______________| 0xF000
		|       -       |
		|_______________| 0xE000
		|               |
		|    WORK RAM   |
		|_______________| 0xC000
		|    EXPANDED   |
		|    WORK RAM   |
		|_______________| 0xA000
		|BKG DISP DATA 2|
		|_______________| 0x9C00
		|BKG DISP DATA 1|
		|_______________| 0x9800
		|   CHARACTER   |
		|      DATA     |
		|_______________| 0x8000
		|               |
		|      HOME     |
		|               |
		|_______________| 0x4000
		|               |
		|   FIXED HOME  |
		|               |
		|_______________| 0x0000 


fixed home and home goes the cartridge's user program data



MEMORY AREAS SIZES:
constexpr const size_t OAM_RAM_SIZE = 256;
constexpr const size_t WORK_RAM_SIZE = 8 * 1024;
constexpr const size_t EXPANDED_WORK_RAM_SIZE = 8 * 1024;
constexpr const size_t BKG_DISP_DATA2_SIZE = 1024;
constexpr const size_t BKG_DISP_DATA1_SIZE = 1024;
constexpr const size_t CHAR_DATA_SIZE = 6 * 1024;
constexpr const size_t HOME_SIZE = 16 * 1024;
constexpr const size_t FIXED_HOME_SIZE = 16 * 1024;

MEMORY AREAS OFFSETS:
constexpr const size_t OAM_RAM_OFFSET = 0xFE00;
constexpr const size_t WORK_RAM_OFFSET = 0xC000;
constexpr const size_t EXPANDED_WORK_RAM_OFFSET = 0xA000;
constexpr const size_t BKG_DISP_DATA2_OFFSET = 0x9C00;
constexpr const size_t BKG_DISP_DATA1_OFFSET = 0x9800;
constexpr const size_t CHAR_DATA_OFFSET = 0x8000;
constexpr const size_t HOME_OFFSET = 0x4000;
constexpr const size_t FIXED_HOME_OFFSET = 0;

*/

constexpr const size_t TOTAL_RAM_SIZE = 0xFFFF;
constexpr const size_t MAX_CARTRIDGE_SIZE = 32 * 1024;







Machine* CreateMachine() {	

	auto* const machine = static_cast<Machine*>( malloc(sizeof(Machine)) );

	if(!machine) {
		perror("can't allocate memory for machine");
		return nullptr;
	}

	auto machine_cleanup = utix::MakeScopeExitIf([=]() noexcept {
			free(machine);
	});

	machine->ram = static_cast<uint8_t*>( malloc(sizeof(uint8_t) * TOTAL_RAM_SIZE ) );
	
	if(!machine->ram) {
		perror("can't allocate memory for Machine's ram");
		return nullptr;
	}

	machine_cleanup.Cancel();
	return machine;
}




void DestroyMachine(Machine* const mach) {
	free(mach->ram);
	free(mach);
}






bool LoadRom(const char* const rom_file_name, Machine* const mach) {

	FILE* const rom_file = fopen(rom_file_name, "r");

	if(!rom_file) {
		perror("Could not open rom file");
		return false;
	}

	const auto file_cleanup = utix::MakeScopeExit([=]() noexcept {
		fclose(rom_file);
	});	

	fseek(rom_file, 0, SEEK_END);
	const auto rom_size = static_cast<size_t>(ftell(rom_file));
	fseek(rom_file, 0, SEEK_SET);
	
	if(rom_size > MAX_CARTRIDGE_SIZE) {
		fprintf(stderr, "\'%s\' size is too big", rom_file_name);
		return false;
	}

	fread(mach->ram, sizeof(uint8_t), rom_size, rom_file);

	if(ferror(rom_file)) {
		perror("error while reading from rom");
		return false;
	}

	mach->rom_size = rom_size;
	mach->cpu.pc = 0x100;
	return true;
}




bool StepMachine(Machine* const mach) {
	// fetch Opcode and execute instruction
	// uint8_t variable can't overflow main_instruction array
	const auto pc = mach->cpu.pc;
	if(pc < mach->rom_size) {
		const auto op = mach->cpu.op = mach->ram[pc];
		main_instructions[op](mach);
		return true;
	}

	return false;
}
























}
