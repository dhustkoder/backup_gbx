#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Utix/Assert.h>
#include <Utix/Alloc_t.h>
#include <Utix/ScopeExit.h>
#include "MainInstructions.h"
#include "Machine.h"


namespace gbx {





Machine* CreateMachine() {	
	auto* const mach = utix::malloc_t<Machine>();

	if(!mach) {
		perror("can't allocate memory for Machine");
		return nullptr;
	}

	auto mach_cleanup = utix::MakeScopeExitIf([=] {
			free(mach);
	});

	if(!mach->memory.Initialize())
		return nullptr;
	
	mach->cartridge.Initialize();	
	mach_cleanup.Cancel();
	return mach;
}




void DestroyMachine(Machine* const mach) {
	ASSERT_MSG(mach!=nullptr, "attempt to free nullptr");
	mach->cartridge.Dispose();
	mach->memory.Dispose();
	free(mach);
}








bool Machine::Reset() {
	const auto cartridge_gb_type = cartridge.GetGameBoyType();
	const auto cartridge_type = cartridge.GetType();
	printf("Internal ROM name: %s\n", cartridge.GetName());
	printf("Gameboy type:   %x\n", static_cast<unsigned int>(cartridge_gb_type));
	printf("Cartridge type: %x\n", static_cast<unsigned int>(cartridge_type));
	printf("Cartridge size: %zu Kib\n", cartridge.GetSize());

	if (cartridge_type != CartridgeType::ROM_ONLY) {
		fprintf(stderr, "Cartridge type not supported!\n");
		return false;
	}


	memcpy(memory.Data(), cartridge.Data(), (FIXED_HOME_SIZE + HOME_SIZE));
	cpu.SetPC(CARTRIDGE_ENTRY_POINT);

	// Common GB init memory registers
	cpu.SetSP(0xFFFE);
	cpu.SetAF(0x01B0);
	cpu.SetBC(0x0013);
	cpu.SetDE(0x00D8);
	cpu.SetHL(0x014D);

	
	memory.WriteU8(0xFF05, 0x00); // TIMA
	memory.WriteU8(0xFF06, 0x00); // TMA
	memory.WriteU8(0xFF07, 0x00); // TAC
	memory.WriteU8(0xFF10, 0x80); // NR10
	memory.WriteU8(0xFF11, 0xBF); // NR11
	memory.WriteU8(0xFF12, 0xF3); // NR12
	memory.WriteU8(0xFF14, 0xBF); // NR14
	memory.WriteU8(0xFF16, 0x3F); // NR21
	memory.WriteU8(0xFF17, 0x00); // NR22
	memory.WriteU8(0xFF19, 0xBF); // NR24
	memory.WriteU8(0xFF1A, 0x7F); // NR30
	memory.WriteU8(0xFF1B, 0xFF); // NR31
	memory.WriteU8(0xFF1C, 0x9F); // NR32
	memory.WriteU8(0xFF1E, 0xBF); // NR33
	memory.WriteU8(0xFF20, 0xFF); // NR41
	memory.WriteU8(0xFF21, 0x00); // NR42
	memory.WriteU8(0xFF22, 0x00); // NR43
	memory.WriteU8(0xFF23, 0xBF); // NR30
	memory.WriteU8(0xFF24, 0x77); // NR50
	memory.WriteU8(0xFF25, 0xF3); // NR51
	memory.WriteU8(0xFF26, 0xF1); // NR52
	memory.WriteU8(0xFF40, 0x91); // LCDC
	memory.WriteU8(0xFF42, 0x00); // SCY
	memory.WriteU8(0xFF43, 0x00); // SCX
	memory.WriteU8(0xFF45, 0x00); // LYC
	memory.WriteU8(0xFF47, 0xFC); // BGP
	memory.WriteU8(0xFF48, 0xFF); // OBP0
	memory.WriteU8(0xFF49, 0xFF); // OBP1
	memory.WriteU8(0xFF4A, 0x00); // WY
	memory.WriteU8(0xFF4B, 0x00); // WX
	memory.WriteU8(INTERRUPT_ENABLED_OFFSET, 0x00);

	return true;
}





bool Machine::LoadRom(const char* file_name) {
	if (!this->cartridge.Load(file_name))
		return false;

	return this->Reset();
}






bool Machine::Step() {
	// boot code seems to expect values from this addr
	memory.AddU8(0xff44, 1);

	// fetch Opcode and execute instruction
	// uint8_t variable can't overflow main_instruction array
	const uint16_t pc = cpu.GetPC();
	const uint8_t opcode = memory.ReadU8(pc);
	cpu.AddPC(1);
	
	// info
	printf("PC: %4x | ", pc);
	printf("OPCODE: %2x | ", opcode);
	
	main_instructions[opcode](this);
	return true;
}










void Machine::StepInterrupts() {
	// TODO: test vblank
	static clock_t interrupt_time = 0;

	if (GetIME()) {
		const auto interrupt_enabled = memory.GetIE();
		// give a break for next instruction execute before
		// the interrupt triggers, if its after a EI instruction
		if (!(interrupt_enabled & INTERRUPT_IMA)) {
			memory.SetIE(interrupt_enabled | INTERRUPT_IMA);
			return;
		}

		const uint8_t interrupt_flags = memory.GetIF();
		const uint8_t requests = interrupt_flags & interrupt_enabled;

		if (requests & INTERRUPT_VBLANK) {
			const auto ms_elapsed = ((double)(clock() - interrupt_time) / CLOCKS_PER_SEC) * 1000;
			if (ms_elapsed >= 14.6) {
				// unset vblank bit
				memory.SetIF(interrupt_flags & ~INTERRUPT_VBLANK);

				// unset IME and call interrupt
				SetIME(false);
				PushStack16(cpu.GetPC());
				cpu.SetPC(INTERRUPT_VBLANK_ADDR);
				interrupt_time = clock();
			}
		}
	}
}




























}
