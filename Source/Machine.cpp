#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Utix/BaseTraits.h>
#include <Utix/ScopeExit.h>
#include "Instructions.h"
#include "Machine.h"

namespace gbx {





Machine* CreateMachine() {	

	auto* const mach = static_cast<Machine*>( malloc(sizeof(Machine)) );

	if(!mach) {
		perror("can't allocate memory for Machine");
		return nullptr;
	}

	auto mach_cleanup = utix::MakeScopeExitIf([=]() noexcept {
			free(mach);
	});


	const_cast<uint8_t*&>(mach->memory.ram) = static_cast<uint8_t*>(malloc(sizeof(uint8_t) * TOTAL_RAM_SIZE));

	if(!mach->memory.ram) {
		perror("failed to allocate Machine's memory");
		return nullptr;
	}

	mach_cleanup.Cancel();
	return mach;
}




void DestroyMachine(Machine* const mach) {
	free(mach->memory.ram);
	free(mach);
}






bool Machine::LoadRom(const char* const rom_file_name) {

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

	fread(this->memory.ram, sizeof(uint8_t), rom_size, rom_file);

	if(ferror(rom_file)) {
		perror("error while reading from rom");
		return false;
	}

	const_cast<size_t&>(this->rom_size) = rom_size;
	this->cpu.pc = CARTRIDGE_ENTRY_POINT;

	printf("ROM TYPE: %X\n", this->memory.Read8(0x147));
	printf("ROM SIZE: %X\n", this->memory.Read8(0x148));

	return true;
}




bool Machine::StepMachine() {
	// fetch Opcode and execute instruction
	// uint8_t variable can't overflow main_instruction array
	const uint16_t pc = this->cpu.pc;
	if(pc < CHAR_DATA_OFFSET) {
		cpu.op = memory.Read8(pc);
		main_instructions[cpu.op](this);
	} 
	else {
		fprintf(stderr, "PC overflows program memory\n");
		return false;
	}

	return true;
}
























}
