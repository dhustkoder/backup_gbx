#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <Utix/Ints.h>
#include <Utix/ScopeExit.h>

namespace gbx {

using Opcode = uint32_t;
using Byte = uint8_t;

struct Machine;
Machine* CreateMachine(Byte* rom, size_t rom_size);
void DestroyMachine(Machine* mach);
void DecodeAndExecuteInstruction(Machine* mach);

}




int main(int argc, char** argv) 
{
	using std::cerr;
	using std::cout;

	try {
		
		if(argc < 2) {
			cerr << "usage: " << argv[0] << " <rom>\n";
			return EXIT_FAILURE;
		}

		cout << sizeof(gbx::Opcode) << '\n';

		const auto machine = [argv] {
			std::ifstream rom(argv[1], std::ios::binary | std::ios::ate);
			const auto rom_size = rom.tellg();
			rom.seekg(0, rom.beg);
			std::vector<uint8_t> rom_bytes(rom_size);
			rom.read(reinterpret_cast<char*>(rom_bytes.data()), rom_size);
			return gbx::CreateMachine(rom_bytes.data(), rom_size);
		}();

		const auto machine_clean = MakeScopeExit([=] noexcept {
			gbx::DestroyMachine(machine_clean);	
		});
	
	}
	catch(std::exception& e) {
		cerr << "Fatal Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}





namespace gbx {

using std::cout;
constexpr const size_t MAIN_RAM_SIZE = 8 * 1024;
constexpr const size_t VIDEO_RAM_SIZE = 8 * 1024;
constexpr const size_t TOTAL_RAM_SIZE = MAIN_RAM_SIZE + VIDEO_RAM_SIZE;
struct Cpu {
	Opcode opcode;
	
};

struct Machine {
	Cpu cpu;
	Byte* ram;
};

Machine* CreateMachine(Byte* rom, size_t rom_size) {
	auto machine = static_cast<Machine*>( malloc(sizeof(Machine)) );
	machine->ram = static_cast<Byte*>( malloc(sizeof(Byte) * ( TOTAL_RAM_SIZE + rom_size )) );
	memcpy(mechine->ram, rom, rom_size);
	return machine;
}


void DestroyMachine(Machine* mach) {
	free(machine->ram);
	free(machine);
}



void nop(Machine*) {
	cout << "nop";
}
void ld(Machine*) {
	cout << "ld";
}
void inc(Machine*) {
	cout << "inc";
}

void dec(Machine*) {
	cout << "dec";
}

void rlca(Machine*) {
	cout << "rlca";
}

void ex(Machine*) {
	cout << "ex";
}


void add(Machine*) {
	cout << "add";
}

void rrca(Machine*) {
	cout << "rrca";
}



void DecodeAndExecuteInstruction(Machine* mach) {
	using IntructionFunction = void(*)(Machine*);
	static InstructionFunction instruction_table[] = 
	{
	/*       0    1   2   3    4    5    6   7    8    9   10  11   12   13   14  15 */
	/* 0 */ nop, ld, ld, inc, inc, dec, ld, rlca, ex, add, ld, dec, inc, dec, ld

	};

	if(mach->cpu.opcode	>= GetArrSz(instruction_table)) {
		cout << "unknown opcode: " << mach->cpu.opcode << '\n';
	}
	else {
		instruction_table[mach->cpu.opcode](mach);
		cout << '\n';
	}
}






}
