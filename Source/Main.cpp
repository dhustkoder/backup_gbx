#include <stdio.h>
#include <stdlib.h>
#include <Utix/ScopeExit.h>
#include "Machine.h"



int main(int argc, char** argv) 
{
	if(argc < 2) {
		fprintf(stderr, "usage: %s <rom>\n", argv[0]);
		return EXIT_FAILURE;
	}

	auto* const machine = gbx::CreateMachine();
	
	if(!machine)
		return EXIT_FAILURE;

	const auto machine_cleanup = utix::MakeScopeExit([=]() noexcept {
		gbx::DestroyMachine(machine);
	});

	if(!machine->LoadRom(argv[1]))
		return EXIT_FAILURE;

	while(machine->StepMachine()) {

	}

	return EXIT_SUCCESS;
}


