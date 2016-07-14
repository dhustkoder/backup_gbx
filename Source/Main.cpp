#include <stdio.h>
#include <stdlib.h>
#include <Utix/ScopeExit.h>
#include "Machine.h"



int main(int argc, char** argv) 
{
	if(argc < 2) {
		fprintf(stderr, "usage: %s <rom>", argv[0]);
		return EXIT_FAILURE;
	}

	auto* const machine = gbx::CreateMachine();
	
	if(!machine)
		return EXIT_FAILURE;

	const auto machine_cleanup = utix::MakeScopeExit([=]() noexcept {
		gbx::DestroyMachine(machine);
	});

	if(!gbx::LoadRom(argv[1], machine))
		return EXIT_FAILURE;

	while(gbx::StepMachine(machine)) {
		
	}

	return EXIT_SUCCESS;
}


