#include <stdio.h>
#include <stdlib.h>
#include <Utix/ScopeExit.h>

#include "Instructions.h"
#include "Machine.h"
#include "Memory.h"







int main(int argc, char** argv) {
	if(argc < 2) {
		fprintf(stderr, "usage: %s <rom>\n", argv[0]);
		return EXIT_FAILURE;
	}
	sizeof(gbx::Machine);
	gbx::Machine* const machine = gbx::CreateMachine();
	
	if(!machine)
		return EXIT_FAILURE;

	const auto machine_cleanup = utix::MakeScopeExit([=] {
		gbx::DestroyMachine(machine);
	});

	if(!machine->LoadRom(argv[1]))
		return EXIT_FAILURE;

	while (1) {
		// boot code seems to expected the value in this area
		// to keep changing
		machine->memory.AddU8(0xff44, 1);

		// fetch Opcode and execute instruction
		// uint8_t variable can't overflow main_instruction array
		const uint16_t pc = machine->cpu.GetPC();
		printf("PC: %4x | ", pc);

		if (pc <= gbx::HOME_MAX_OFFSET) {
			const auto op = machine->memory.ReadU8(pc);
			machine->cpu.SetOP(op);
			printf("OPCODE: %2x | ", op);
			gbx::main_instructions[op](machine);
		}
		else {
			fprintf(stderr, "PC overflows program memory\n");
			break;
		}

	}

	return EXIT_SUCCESS;
}


