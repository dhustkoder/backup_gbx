#include <stdio.h>
#include <string.h>
#include <Utix/ScopeExit.h>
#include "Machine.h"

namespace gbx {




Machine* CreateMachine() {	

	auto* const mach = static_cast<Machine*>(malloc(sizeof(Machine)));

	if(!mach) {
		perror("can't allocate memory for Machine");
		return nullptr;
	}

	auto mach_cleanup = utix::MakeScopeExitIf([=] {
			free(mach);
	});

	if(!mach->memory.Initialize())
		return nullptr;
	
	mach->rom.Initialize();
	mach->cpu.SetPC(CARTRIDGE_ENTRY_POINT);
	mach->cpu.SetSP(0xFFFE);
	mach->cpu.SetAF(0x01B0);
	mach->cpu.SetBC(0x0013);
	mach->cpu.SetDE(0x00D8);
	mach->cpu.SetHL(0x014D);
	
	mach_cleanup.Cancel();
	return mach;
}




void DestroyMachine(Machine* const mach) {
	mach->rom.Dispose();
	mach->memory.Dispose();
	free(mach);
}







bool Machine::LoadRom(const char* file_name) {
	if (!this->rom.Load(file_name))
		return false;

	// place the first banks into main memory
	memcpy(memory.Data(), rom.Data(), sizeof(uint8_t) * (FIXED_HOME_SIZE + HOME_SIZE));

	// show rom's internal name
	uint8_t buffer[17];
	memcpy(buffer, rom.Data() + 0x134, sizeof(uint8_t) * 16);
	buffer[16] = 0;
	printf("Internal ROM name: %s\n", buffer);

	return true;
}












}
