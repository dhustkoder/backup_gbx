#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <Utix/Alloc.h>
#include <Utix/Ints.h>
#include <Utix/ScopeExit.h>

namespace gbx {
	
struct Machine;

Machine* CreateMachine(uint8_t* rom, size_t rom_size);
void DestroyMachine(Machine* mach);
bool StepMachine(Machine* mach);

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





namespace gbx {

using std::cout;

constexpr const size_t MAIN_RAM_SIZE = 8 * 1024;
constexpr const size_t VIDEO_RAM_SIZE = 8 * 1024;
constexpr const size_t MAX_CARTRIDGE_SIZE = 32 * 1024;
constexpr const size_t TOTAL_RAM_SIZE = MAIN_RAM_SIZE + VIDEO_RAM_SIZE + MAX_CARTRIDGE_SIZE;

struct Cpu {
	uint32_t opcode;
	uint16_t pc;
	uint8_t flags;
};

struct Machine {
	Cpu cpu;
	uint8_t* ram;
	size_t rom_size;
};

Machine* CreateMachine(uint8_t* rom, size_t rom_size) {

	if(rom_size >= MAX_CARTRIDGE_SIZE) {
		fprintf(stderr, "rom_size is too big!\n");
		return nullptr;
	}

	auto machine = static_cast<Machine*>( malloc(sizeof(Machine)) );

	if(!machine) {
		perror("can't allocate memory for machine");
		return nullptr;
	}
	// null all ptrs in machine
	// to not have problems with DestroyMachine, if called
	machine->ram = nullptr;

	auto machine_cleanup = utix::MakeScopeExit([=]() noexcept {
			gbx::DestroyMachine(machine);
	});

	machine->ram = static_cast<uint8_t*>( malloc(sizeof(uint8_t) * ( TOTAL_RAM_SIZE + rom_size )) );
	
	if(!machine->ram) {
		perror("can't allocate memory for gb ram");
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



// 0x00
void nop_00(Machine*);
void ld_01(Machine*);
void ld_02(Machine*);
void inc_03(Machine*);
void inc_04(Machine*);
void dec_05(Machine*);
void ld_06(Machine*);
void rlca_07(Machine*);
void ld_08(Machine*);
void add_09(Machine*);
void ld_0A(Machine*);
void dec_0B(Machine*);
void inc_0C(Machine*);
void dec_0D(Machine*);
void ld_0E(Machine*);
void rrca_0F(Machine*);
// 0x10
void stop_10(Machine*);
void ld_11(Machine*);
void ld_12(Machine*);
void inc_13(Machine*);
void inc_14(Machine*);
void dec_15(Machine*);
void ld_16(Machine*);
void rla_17(Machine*);
void jr_18(Machine*);
void add_19(Machine*);
void ld_1A(Machine*);
void dec_1B(Machine*);
void inc_1C(Machine*);
void dec_1D(Machine*);
void ld_1E(Machine*);
void rra_1F(Machine*);
// 0x20
void jr_20(Machine*);
void ld_21(Machine*);
void ld_22(Machine*);
void inc_23(Machine*);
void inc_24(Machine*);
void dec_25(Machine*);
void ld_26(Machine*);
void daa_27(Machine*);
void jr_28(Machine*);
void add_29(Machine*);
void ld_2A(Machine*);
void dec_2B(Machine*);
void inc_2C(Machine*);
void dec_2D(Machine*);
void ld_2E(Machine*);
void cpl_2F(Machine*);
// 0x30




using InstructionFunction = void(*)(Machine*);
extern InstructionFunction main_instructions[0x30];


bool StepMachine(Machine* mach) {

	if(mach->cpu.pc >= mach->rom_size)
		return false;

	mach->cpu.opcode = mach->ram[mach->cpu.pc];

	if(mach->cpu.opcode	>= utix::arr_size(main_instructions)) {
		std::cout << "unknown opcode: " << mach->cpu.opcode << '\n';
		return false;
	}

	main_instructions[mach->cpu.opcode](mach);
	return true;
}







InstructionFunction main_instructions[0x30] = 
{
/*         0      1      2       3       4       5      6        7      8       9      A       B       C       D      E        F  */
/* 0 */ nop_00, ld_01, ld_02, inc_03, inc_04, dec_05, ld_06, rlca_07, ld_08, add_09, ld_0A, dec_0B, inc_0C, dec_0D, ld_0E, rrca_0F,
/* 1 */ stop_10, ld_11, ld_12, inc_13, inc_14, dec_15, ld_16, rla_17, jr_18, add_19, ld_1A, dec_1B, inc_1C, dec_1D, ld_1E, rra_1F,
/* 2 */  jr_20, ld_21, ld_22, inc_23, inc_24, dec_25, ld_26, daa_27, jr_28, add_29, ld_2A, dec_2B, inc_2C, dec_2D, ld_2E, cpl_2F,
};







// 0x00
void nop_00(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_01(Machine* mach)  { std::cout << __func__ << '\n'; mach->cpu.pc += 3; }
void ld_02(Machine* mach)  { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void inc_03(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void inc_04(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void dec_05(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_06(Machine* mach)  { std::cout << __func__ << '\n'; mach->cpu.pc += 2; }
void rlca_07(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_08(Machine* mach)  { std::cout << __func__ << '\n'; mach->cpu.pc += 3; }
void add_09(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_0A(Machine* mach)  { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void dec_0B(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void inc_0C(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void dec_0D(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_0E(Machine* mach)  { std::cout << __func__ << '\n'; mach->cpu.pc += 2; }
void rrca_0F(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
// 0x10
void stop_10(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 2; }
void ld_11(Machine* mach)  { std::cout << __func__ << '\n'; mach->cpu.pc += 3; }
void ld_12(Machine* mach)  { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void inc_13(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void inc_14(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void dec_15(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_16(Machine* mach)  { std::cout << __func__ << '\n'; mach->cpu.pc += 2; }
void rla_17(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void jr_18(Machine* mach)  { std::cout << __func__ << '\n'; mach->cpu.pc += 2; }
void add_19(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_1A(Machine* mach)  { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void dec_1B(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void inc_1C(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void dec_1D(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_1E(Machine* mach)  { std::cout << __func__ << '\n'; mach->cpu.pc += 2; }
void rra_1F(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
// 0x20
void jr_20(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 2; }
void ld_21(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 3; }
void ld_22(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void inc_23(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void inc_24(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void dec_25(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_26(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 2; }
void daa_27(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void jr_28(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 2; }
void add_29(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_2A(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void dec_2B(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void inc_2C(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void dec_2D(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_2E(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 2; }
void cpl_2F(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
// 0x30













}
