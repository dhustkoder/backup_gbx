#include <stdlib.h>
#include <string.h>
#include <Utix/Log.h>
#include <Utix/BaseTraits.h>
#include <Utix/ScopeExit.h>
#include "Instructions.h"
#include "Machine.h"



namespace gbx {

constexpr const size_t MAIN_RAM_SIZE = 8 * 1024;
constexpr const size_t VIDEO_RAM_SIZE = 8 * 1024;
constexpr const size_t MAX_CARTRIDGE_SIZE = (32 * 1024) + 0x100;
constexpr const size_t TOTAL_RAM_SIZE = MAIN_RAM_SIZE + VIDEO_RAM_SIZE + MAX_CARTRIDGE_SIZE;


Machine* CreateMachine() {	
	using utix::LogError;

	auto* const machine = static_cast<Machine*>( malloc(sizeof(Machine)) );

	if(!machine) {
		LogError("can't allocate memory for machine");
		return nullptr;
	}

	// null all ptrs in the machine structure
	// to not have problems with DestroyMachine, if called
	machine->ram = nullptr;

	auto machine_cleanup = utix::MakeScopeExitIf([=]() noexcept {
			gbx::DestroyMachine(machine);
	});

	machine->ram = static_cast<uint8_t*>( malloc(sizeof(uint8_t) * TOTAL_RAM_SIZE ) );
	
	if(!machine->ram) {
		LogError("can't allocate memory for gb ram");
		return nullptr;
	}

	machine_cleanup.Cancel();
	return machine;
}


void DestroyMachine(Machine* const mach) {
	free(mach->ram);
	free(mach);
}




bool LoadRom(const char* rom_file_name, Machine* const mach) {
	using utix::LogError;

	FILE* const rom_file = fopen(rom_file_name, "r");

	if(!rom_file) {
		LogError("Could not open \'%s\'", rom_file_name);
		return false;
	}
	const auto file_cleanup = utix::MakeScopeExit([=]() noexcept {
		fclose(rom_file);
	});	

	fseek(rom_file, 0, SEEK_END);
	const auto rom_size = static_cast<size_t>(ftell(rom_file));
	fseek(rom_file, 0, SEEK_SET);
	
	if(rom_size >= MAX_CARTRIDGE_SIZE) {
		LogError("\'%s\' size is too big", rom_file_name);
		return false;
	}

	fread(mach->ram, sizeof(uint8_t), rom_size, rom_file);

	if(ferror(rom_file)) {
		LogError("error while reading from \'%s\'", rom_file_name);
		return false;
	}

	mach->cpu.pc = 0x100;
	mach->rom_size = rom_size;
	return true;
}




bool StepMachine(Machine* const mach) {

	if(mach->cpu.pc >= mach->rom_size)
		return false;

	mach->cpu.opcode = mach->ram[mach->cpu.pc];

	if(mach->cpu.opcode >= utix::arr_size(main_instructions)) {
		utix::LogError("unknown opcode %X\n", mach->cpu.opcode);
		return false;
	}

	main_instructions[mach->cpu.opcode](mach);
	return true;
}













}
