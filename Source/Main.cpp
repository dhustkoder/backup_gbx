#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <Utix/Log.h>
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

		const auto machine = gbx::CreateMachine();

		if(!machine)
			throw std::runtime_error(utix::GetLastLogError());

		const auto destroy_manchine = utix::MakeScopeExit([=]() noexcept {
			gbx::DestroyMachine(machine);	
		});
		
		if(!gbx::LoadRom(argv[1], machine))
			throw std::runtime_error(utix::GetLastLogError());

		while(gbx::StepMachine(machine))
		{
			
		}
	
	}
	catch(std::exception& e) {
		cerr << "Fatal Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}


