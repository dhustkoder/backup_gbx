#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Utix/BaseTraits.h>
#include <Utix/ScopeExit.h>
#include "Instructions.h"
#include "Machine.h"

namespace gbx {





Machine* CreateMachine() {	

	auto* const machine = static_cast<Machine*>( malloc(sizeof(Machine)) );

	if(!machine) {
		perror("can't allocate memory for machine");
		return nullptr;
	}

	auto machine_cleanup = utix::MakeScopeExitIf([=]() noexcept {
			free(machine);
	});

	const_cast<uint8_t*&>(machine->ram) = static_cast<uint8_t*>( malloc(sizeof(uint8_t) * TOTAL_RAM_SIZE ) );
	
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

	const_cast<size_t&>(mach->rom_size) = rom_size;
	mach->cpu.pc = CARTRIDGE_ENTRY_POINT;

	printf("ROM TYPE: %X\n", mach->ram[0x147]);
	printf("ROM SIZE: %X\n", mach->ram[0x148]);

	return true;
}




bool StepMachine(Machine* const mach) {
	// fetch Opcode and execute instruction
	// uint8_t variable can't overflow main_instruction array
	const uint16_t pc = mach->cpu.pc;
	if(pc < CHAR_DATA_OFFSET) {
		mach->cpu.op = mach->ram[pc];
		main_instructions[mach->cpu.op](mach);
	} 
	else {
		fprintf(stderr, "PC overflows program memory\n");
		return false;
	}

	return true;
}
























}
