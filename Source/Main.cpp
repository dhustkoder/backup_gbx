#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <Utix/Ints.h>
#include <Utix/ScopeExit.h>
#include "Machine.h"



int main(int argc, char** argv) 
{
	using std::cerr;
	using std::cout;

	try {
		
		if(argc < 2) {
			cerr << "usage: " << argv[0] << " <rom>\n";
			return EXIT_FAILURE;
		}

		const auto machine = [argv] {
			std::ifstream rom(argv[1], std::ios::binary | std::ios::ate);
			const auto rom_size = rom.tellg();
			rom.seekg(0, rom.beg);
			std::vector<uint8_t> rom_bytes(rom_size);
			rom.read(reinterpret_cast<char*>(rom_bytes.data()), rom_size);
			auto mach = gbx::CreateMachine(rom_bytes.data(), rom_size);
			if(mach == nullptr) throw std::runtime_error("cannot create machine!");
			return mach;
		}();

		const auto destroy_manchine = utix::MakeScopeExit([=]() noexcept {
			gbx::DestroyMachine(machine);	
		});

		while( StepMachine(machine) ) 
		{
			
		}

	
	}
	catch(std::exception& e) {
		cerr << "Fatal Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}


