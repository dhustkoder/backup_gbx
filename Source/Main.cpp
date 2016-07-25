#include <stdio.h>
#include <Utix/ScopeExit.h>
#include "Machine.h"




int main(int argc, char** argv) {
	if(argc < 2) {
		fprintf(stderr, "usage: %s <rom>\n", argv[0]);
		return EXIT_FAILURE;
	}

	gbx::Machine* const machine = gbx::CreateMachine();
	
	if(!machine)
		return EXIT_FAILURE;

	const auto machine_cleanup = utix::MakeScopeExit([=] {
		gbx::DestroyMachine(machine);
	});

	if(!machine->LoadRom(argv[1]))
		return EXIT_FAILURE;

	while (machine->Step()) {

	}

	return EXIT_SUCCESS;
}


