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
constexpr const size_t MAX_CARTRIDGE_SIZE = 32 * 1024;
constexpr const size_t TOTAL_RAM_SIZE = MAIN_RAM_SIZE + VIDEO_RAM_SIZE + MAX_CARTRIDGE_SIZE;


Machine* CreateMachine(uint8_t* rom, size_t rom_size) {
	
	using utix::LogError;

	if(rom_size >= MAX_CARTRIDGE_SIZE) {
		LogError("rom_size is too big!");
		return nullptr;
	}

	auto machine = static_cast<Machine*>( malloc(sizeof(Machine)) );

	if(!machine) {
		LogError("can't allocate memory for machine");
		return nullptr;
	}

	// null all ptrs in machine
	// to not have problems with DestroyMachine, if called
	machine->ram = nullptr;

	auto machine_cleanup = utix::MakeScopeExitIf([=]() noexcept {
			gbx::DestroyMachine(machine);
	});

	machine->ram = static_cast<uint8_t*>( malloc(sizeof(uint8_t) * ( TOTAL_RAM_SIZE + rom_size )) );
	
	if(!machine->ram) {
		LogError("can't allocate memory for gb ram");
		return nullptr;
	}

	memcpy(machine->ram, rom, rom_size);
	machine->rom_size = rom_size;
	machine->cpu.opcode = 0;
	machine->cpu.pc = 0;
	machine_cleanup.Cancel();
	return machine;
}


void DestroyMachine(Machine* mach) {
	free(mach->ram);
	free(mach);
}






bool StepMachine(Machine* mach) {

	if(mach->cpu.pc >= mach->rom_size)
		return false;

	mach->cpu.opcode = mach->ram[mach->cpu.pc];

	if(mach->cpu.opcode	>= utix::arr_size(main_instructions)) {
		utix::LogError("unknown opcode %u\n", mach->cpu.opcode);
		return false;
	}

	main_instructions[mach->cpu.opcode](mach);
	return true;
}













}
