#include "Machine.h"
#include "Instructions.h"

namespace gbx {



const MainInstrFunc main_instructions[0x100] = {
/*        0        1        2        3        4        5        6        7        8        9        A        B        C        D        E        F      */
/*0*/  nop_00,   ld_01,   ld_02,  inc_03,  inc_04,  dec_05,   ld_06, rlca_07,   ld_08,  add_09,   ld_0A,  dec_0B,  inc_0C,  dec_0D,   ld_0E, rrca_0F,
/*1*/ stop_10,   ld_11,   ld_12,  inc_13,  inc_14,  dec_15,   ld_16,  rla_17,   jr_18,  add_19,   ld_1A,  dec_1B,  inc_1C,  dec_1D,   ld_1E,  rra_1F,
/*2*/   jr_20,   ld_21,   ld_22,  inc_23,  inc_24,  dec_25,   ld_26,  daa_27,   jr_28,  add_29,   ld_2A,  dec_2B,  inc_2C,  dec_2D,   ld_2E,  cpl_2F,
/*3*/   jr_30,   ld_31,   ld_32,  inc_33,  inc_34,  dec_35,   ld_36,  scf_37,   jr_38,  add_39,   ld_3A,  dec_3B,  inc_3C,  dec_3D,   ld_3E,  ccf_3F,
/*4*/   ld_40,   ld_41,   ld_42,   ld_43,   ld_44,   ld_45,   ld_46,   ld_47,   ld_48,   ld_49,   ld_4A,   ld_4B,   ld_4C,   ld_4D,   ld_4E,   ld_4F,
/*5*/   ld_50,   ld_51,   ld_52,   ld_53,   ld_54,   ld_55,   ld_56,   ld_57,   ld_58,   ld_59,   ld_5A,   ld_5B,   ld_5C,   ld_5D,   ld_5E,   ld_5F,
/*6*/   ld_60,   ld_61,   ld_62,   ld_63,   ld_64,   ld_65,   ld_66,   ld_67,   ld_68,   ld_69,   ld_6A,   ld_6B,   ld_6C,   ld_6D,   ld_6E,   ld_6F,
/*7*/   ld_70,   ld_71,   ld_72,   ld_73,   ld_74,   ld_75, halt_76,   ld_77,   ld_78,   ld_79,   ld_7A,   ld_7B,   ld_7C,   ld_7D,   ld_7E,   ld_7F,
/*8*/  add_80,  add_81,  add_82,  add_83,  add_84,  add_85,  add_86,  add_87,  adc_88,  adc_89,  adc_8A,  adc_8B,  adc_8C,  adc_8D,  adc_8E,  adc_8F,
/*9*/  sub_90,  sub_91,  sub_92,  sub_93,  sub_94,  sub_95,  sub_96,  sub_97,  sbc_98,  sbc_99,  sbc_9A,  sbc_9B,  sbc_9C,  sbc_9D,  sbc_9E,  sbc_9F,
/*A*/  and_A0,  and_A1,  and_A2,  and_A3,  and_A4,  and_A5,  and_A6,  and_A7,  xor_A8,  xor_A9,  xor_AA,  xor_AB,  xor_AC,  xor_AD,  xor_AE,  xor_AF,
/*B*/   or_B0,   or_B1,   or_B2,   or_B3,   or_B4,   or_B5,   or_B6,   or_B7,   cp_B8,   cp_B9,   cp_BA,   cp_BB,   cp_BC,   cp_BD,   cp_BE,   cp_BF,
/*C*/  ret_C0,  pop_C1,   jp_C2,   jp_C3, call_C4, push_C5,  add_C6,  rst_C7,  ret_C8,  ret_C9,   jp_CA,PREFIX_CB, call_CC, call_CD, adc_CE,  rst_CF,
/*D*/  ret_D0,  pop_D1, jp_D2,miss_instr, call_D4, push_D5,  sub_D6,  rst_D7,  ret_D8, reti_D9,   jp_DA,miss_instr,call_DC,miss_instr,sbc_DE, rst_DF,
/*E*/  ldh_E0,  pop_E1, ld_E2,miss_instr,miss_instr,push_E5, and_E6,  rst_E7,  add_E8,   jp_E9,   ld_EA,miss_instr,miss_instr,miss_instr,xor_EE,rst_EF,
/*F*/  ldh_F0,  pop_F1, ld_F2, di_F3, miss_instr,  push_F5,   or_F6,  rst_F7,   ld_F8,   ld_F9,   ld_FA,  ei_FB,miss_instr,miss_instr, cp_FE, rst_FF
};










// common names:
// d8:  immediate 8 bit value
// d16: immediate 16 bit value
// a8:  8 bit unsigned data, which are added to $FF00 in certain instructions (replacement for missing IN and OUT instructions)
// a16: 16 bit address
// r8: means 8 bit signed data, which are added to program counter
// note: on gameboy PC appears to be incremented before the instruction is executed -
// so relative jump instructions (jr) here still need to add its operand length to pc, or to r8 itself 



// Main instructions implementation:
// 0x00
     
void miss_instr(Machine* const) {
	// not implemented instruction
	printf("MISSING INSTRUCTION!\n");	
}





void nop_00(Machine* const) {
	// no operation is performed
	// operands: 0
	// clock cyles: 4
	
	printf("NOP\n");
}





void ld_01(Machine* const mach) {
	// LD BC, d16
	// load immediate 16 bits value into BC
	// operands: 2
	// clock cyles: 10 or 12 ?
	const auto pc = mach->cpu.GetPC();
	const auto d16 = mach->memory.ReadU16(pc);
	mach->cpu.SetBC(d16);
	mach->cpu.AddPC(2);


	printf("LD BC, %x\n", d16);
}








void ld_02(Machine* const mach) {
	// LD (BC), A
	// value in register A is stored in memory location pointed by BC
	// operands: 0
	// clock cycles: 7 or 8 ?
	const auto bc = mach->cpu.GetBC();
	const auto a = mach->cpu.GetA();
	mach->memory.WriteU8(bc, a);
	


	printf("LD (BC), A; ->  BC(%x), A(%x)\n", bc, a);
}







void inc_03(Machine* const mach) {
	// INC BC
	// adds one to BC
	// operands: 0
	// clock cyles: 6 or 8 ?
	const auto bc = mach->cpu.GetBC();
	const uint16_t result = bc + 1;
	

	printf("INC BC; -> BC(%x), Result(%x)\n", bc, result);
}








void inc_04(Machine* const mach) { 
	// INC B
	// adds one to B
	// operands: 0
	// clock cyles: 4
	// flags affected Z 0 H -
	const auto b = mach->cpu.GetB();
	const auto result = mach->cpu.INC(b);
	mach->cpu.SetB(result);
	

	printf("INC B; -> B(%x), Result(%x) | ", b, result);
	mach->cpu.ShowFlags();
}







void dec_05(Machine* const mach) {
	// DEC B
	// decrement B by 1
	// operands: 0
	// clock cycles: 4
	// flags affected Z 1 H -
	const auto b = mach->cpu.GetB();
	const auto result = mach->cpu.DEC(b);
	mach->cpu.SetB(result);
	

	printf("DEC B; -> B(%x), Result(%x) | ", b, result);
	mach->cpu.ShowFlags();
}






void ld_06(Machine* const mach) {
	// LD B, d8
	// loads immediate 8 bit value into B
	// operands: 1
	// clock cycles: 7 or 8 ?
	const auto pc = mach->cpu.GetPC();
	const auto d8 = mach->memory.ReadU8(pc);
	mach->cpu.SetB(d8);
	mach->cpu.AddPC(1);


	printf("LD B, %x\n", d8);
}






void rlca_07(Machine* const){ ASSERT_INSTR_IMPL();  }
void ld_08(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void add_09(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_0A(Machine* const)  { ASSERT_INSTR_IMPL();  }





void dec_0B(Machine* const mach) {
	// DEC BC
	// decrement BC
	// operands: 0
	// clock cycles: 8
	const auto bc = mach->cpu.GetBC();
	const uint16_t result = bc - 1;
	mach->cpu.SetBC(result);
	
	
	printf("DEC BC; -> BC(%x), Result(%x)\n", bc, result);
}





void inc_0C(Machine* const mach) { 
	// INC C
	// increment C
	// operands: 0
	// clock cycles: 4
	// flags affected: Z 0 H -
	const auto c = mach->cpu.GetC();
	const auto result = mach->cpu.INC(c);
	mach->cpu.SetC(result);
	printf("INC C; C(%x), Result(%x) | ", c, result);
	mach->cpu.ShowFlags();
}






void dec_0D(Machine* const mach) {
	// DEC C
	// subtract C by one
	// operands: 0
	// clock cycles: 4
	// flags affected: Z 1 H
	const auto c = mach->cpu.GetC();
	const auto result = mach->cpu.DEC(c);
	mach->cpu.SetC(result);
	


	printf("DEC C; -> C(%x), Result(%x) | ", c, result);
	mach->cpu.ShowFlags();
}







void ld_0E(Machine* const mach) { 
	// LD C, d8
	// loads immediate 8 bit value into C
	// operands: 1
	// clock cycles: 7 or 8 ?
	const auto pc = mach->cpu.GetPC();
	const auto d8 = mach->memory.ReadU8(pc);
	mach->cpu.SetC(d8);
	mach->cpu.AddPC(1);

	printf("LD C, %x\n", d8);
}






void rrca_0F(Machine* const){ ASSERT_INSTR_IMPL();  }












// 0x10
void stop_10(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }






void ld_11(Machine* const mach) {
	// LD DE, d16
	// store immediate d16 value into DE
	// operands: 2
	// clock cycles: 12
	const auto pc = mach->cpu.GetPC();
	const auto d16 = mach->memory.ReadU16(pc);
	mach->cpu.SetDE(d16);
	mach->cpu.AddPC(2);
	
	
	printf("LD DE, %x\n", d16);
}







void ld_12(Machine* const mach) {
	// LD (DE), A
	// store A into mem address pointed by DE
	// operands: 0
	// clock cycles: 8
	const auto de = mach->cpu.GetDE();
	const auto a = mach->cpu.GetA();
	mach->memory.WriteU8(de, a);
	
	
	printf("LD (DE), A; -> DE(%x), A(%x)\n", de, a);
}







void inc_13(Machine* const mach) {
	// INC DE
	// increment DE
	// operands: 0
	// clock cycles: 8
	const auto de = mach->cpu.GetDE();
	const uint16_t result = de + 1;
	mach->cpu.SetDE(result);
	
	
	printf("INC DE; -> DE(%x), Result(%x)\n", de, result);
}








void inc_14(Machine* const) { ASSERT_INSTR_IMPL();  }
void dec_15(Machine* const) { ASSERT_INSTR_IMPL();  }







void ld_16(Machine* const mach) {
	// LD D, d8
	// immediate 8 bit value stored into D
	// operands: 1
	// clock cycles: 8
	const auto pc = mach->cpu.GetPC();
	const auto d8 = mach->memory.ReadU8(pc);
	mach->cpu.SetD(d8);
	mach->cpu.AddPC(1);
	
	
	printf("LD D, %x\n", d8);
}








void rla_17(Machine* const) { ASSERT_INSTR_IMPL();  }








void jr_18(Machine* const mach) {
	// JR r8
	// Add r8 to pc and jump to it.
	// operands: 1
	// clock cycles: 12
	const auto pc = mach->cpu.GetPC();
	const auto r8 = mach->memory.ReadS8(pc);
	const uint16_t address = (pc+r8) + 1;
	mach->cpu.SetPC(address);


	printf("JR %x\n", address);
}






void add_19(Machine* const mach) {
	// ADD HL, DE
	// add DE into HL
	// operands: 0
	// clock cycles: 8
	// flags affected: - 0 H C
	const auto hl = mach->cpu.GetHL();
	const auto de = mach->cpu.GetDE();
	mach->cpu.ADDHL(de);
	const auto result = mach->cpu.GetHL();
	
	
	
	printf("LD HL, DE; -> HL(%x), DE(%x), Result(%x) | ", hl, de, result);
	mach->cpu.ShowFlags();
}









void ld_1A(Machine* const mach) {
	// LD A, (DE)
	// store value in mem address pointed by DE into A
	// operands: 0
	// clock cycles: 8
	const auto de = mach->cpu.GetDE();
	const auto value = mach->memory.ReadU8(de);
	mach->cpu.SetA(value);
	
	
	printf("LD A, (DE); -> DE(%x), (DE)(%x)\n", de, value);
}






void dec_1B(Machine* const) { ASSERT_INSTR_IMPL();  }






void inc_1C(Machine* const mach) {
	// INC E
	// operands: 0
	// clock cycles: 4
	// flags affected: Z 0 H -
	const auto e = mach->cpu.GetE();
	const auto result = mach->cpu.INC(e);
	mach->cpu.SetE(result);
	
	
	printf("INC E; -> E(%x), Result(%x) | ", e, result);
	mach->cpu.ShowFlags();
}





void dec_1D(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_1E(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void rra_1F(Machine* const) { ASSERT_INSTR_IMPL();  }














// 0x20
void jr_20(Machine* const mach) {
	// JR NZ, r8
	// jump if Z flags is reset
	// operands: 1
	// clock cycles: 12 if jumps, 8 if not

	const auto pc = mach->cpu.GetPC();
	const auto r8 = mach->memory.ReadS8(pc);
	const uint16_t jump_addr = (pc+r8) + 1;

	if(mach->cpu.GetFlags(Cpu::FLAG_Z) == 0)
		mach->cpu.SetPC(jump_addr);
	else 
		mach->cpu.AddPC(1);


	printf("JR NZ, %x\n", jump_addr);
}








void ld_21(Machine* const mach) {
	// LD HL, d16
	// load immediate 16 bit value into HL
	// operands: 2
	// clock cycles: 10 or 12
	const auto pc = mach->cpu.GetPC();
	const auto d16 = mach->memory.ReadU16(pc);
	mach->cpu.SetHL(d16);
	mach->cpu.AddPC(2);


	printf("LD HL, %x\n", d16);
}






void ld_22(Machine* const mach) {
	// LD (HL+), A / or /  LD (HLI), A / or / LDI (HL), A
	// Put A into memory address HL. Increment HL
	// operands: 0
	// clock cycles: 8
	const auto hl = mach->cpu.GetHL();
	const auto a = mach->cpu.GetA();
	mach->memory.WriteU8(hl, a);
	mach->cpu.SetHL(hl + 1);
	
	
	printf("LD (HL+), A; -> HL(%x), A(%x)\n", hl, a);
}







void inc_23(Machine* const mach) {
	// INC HL
	// operands: 0
	// clock cycles: 8
	const auto hl = mach->cpu.GetHL();
	const uint16_t result = hl + 1;
	mach->cpu.SetHL(result);
	

	printf("INC HL; -> HL(%x), Result(%x)\n", hl, result);
}





void inc_24(Machine* const){ ASSERT_INSTR_IMPL();  }
void dec_25(Machine* const){ ASSERT_INSTR_IMPL();  }
void ld_26(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void daa_27(Machine* const){ ASSERT_INSTR_IMPL();  }






void jr_28(Machine* const mach) {
	// JP Z, r8
	// jump if Z flag is set
	// operands: 1
	// clock cycles: if jumps 12, else 8
	const auto pc = mach->cpu.GetPC();
	const auto r8 = mach->memory.ReadS8(pc);
	const auto zero_flag = mach->cpu.GetFlags(Cpu::FLAG_Z);
	const uint16_t jump_addr = (pc+r8) + 1;
	
	if(zero_flag)
		mach->cpu.SetPC(jump_addr);
	else
		mach->cpu.AddPC(1);
	
	printf("JP Z, %x\n", jump_addr);
}






void add_29(Machine* const) { ASSERT_INSTR_IMPL();  }








void ld_2A(Machine* const mach) {
	// LD A, (HL+)
	// store value in address pointed by HL into A, increment HL
	// operands: 0
	// clock cycles: 8
	const auto hl = mach->cpu.GetHL();
	const auto value = mach->memory.ReadU8(hl);
	mach->cpu.SetA(value);
	mach->cpu.SetHL(hl + 1);
	 

	printf("LD A, (HL+); -> HL(%x), (HL)(%x)\n", hl, value);
}










void dec_2B(Machine* const mach) {
	// DEC HL
	// decrement register HL by 1
	// operands: 0
	// clock cycles: 8
	const auto hl = mach->cpu.GetHL();
	const uint16_t result = hl - 1;
	mach->cpu.SetHL(result);
	
	
	printf("DEC HL; -> HL(%x), Result(%x)\n", hl, result);
}






void inc_2C(Machine* const){ ASSERT_INSTR_IMPL();  }
void dec_2D(Machine* const){ ASSERT_INSTR_IMPL();  }
void ld_2E(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }



void cpl_2F(Machine* const mach) {
	// CPL
	// Complement A register, flip all bits
	// operands: 0
	// clock cycles: 4
	// flags affected: - 1 1 -
	const auto a = mach->cpu.GetA();
	const uint8_t result = ~a;
	mach->cpu.SetA(result);
	mach->cpu.SetF(Cpu::FLAG_N | Cpu::FLAG_H);
	
	
	printf("CPL ; -> A(%x), Result(%x)\n", a, result);
}










// 0x30
void jr_30(Machine* const mach) {
	// JR NC, r8
	// jump if C flag is reset
	// operands: 1
	// clock cycles: 12 if jump 8 if not
	
	const auto carry_flag = mach->cpu.GetFlags(Cpu::FLAG_C);
	const auto pc = mach->cpu.GetPC();
	const auto r8 = mach->memory.ReadS8(pc);
	const uint16_t jump_addr = (pc+r8) + 1;
	
	if(!carry_flag)
		mach->cpu.SetPC(jump_addr);
	else
		mach->cpu.AddPC(1);
	
	printf("JR NC, %x\n", jump_addr);
}







void ld_31(Machine* const mach) {
	// LD SP, d16
	// loads immediate 16 bits value into SP
	// operands: 2
	// clock cycles: 10 or 12 ?
	const auto pc = mach->cpu.GetPC();
	const auto d16 = mach->memory.ReadU16(pc);
	mach->cpu.SetSP(d16);
	mach->cpu.AddPC(2); 

	printf("LD SP, %x\n", d16);
}







void ld_32(Machine* const mach) {
	// LD (HL-), A  / or / LD (HLD), A / or / LDD (HL), A
	// store A into memory pointed by HL, Decrements HL
	// operands: 0
	// clock cycles: 8
	const auto a = mach->cpu.GetA();
	const auto hl = mach->cpu.GetHL();	
	mach->memory.WriteU8(hl, a);
	mach->cpu.SetHL(hl - 1);
	

	printf("LD (HL-), A; -> HL(%x) , A(%x)\n", hl, a);
}





void inc_33(Machine* const){ ASSERT_INSTR_IMPL();  }





void inc_34(Machine* const mach) {
	// INC (HL)
	// increment value pointed by hl in memory
	// operands: 0
	// clock cycles: 12
	const auto hl = mach->cpu.GetHL();
	const auto value = mach->memory.ReadU8(hl);
	const auto result = mach->cpu.INC(value);
	mach->memory.WriteU8(hl, result);

	printf("INC (HL); -> HL(%X), (HL)(%x), Result(%x) | ", hl, value, result);
	mach->cpu.ShowFlags();
}




void dec_35(Machine* const){ ASSERT_INSTR_IMPL();  }





void ld_36(Machine* const mach) {
	// LD (HL), d8
	// store d8 into mem address pointed by HL
	// operands: 1
	// clock cycles: 12
	const auto pc = mach->cpu.GetPC();
	const auto hl = mach->cpu.GetHL();
	const auto d8 = mach->memory.ReadU8(pc);
	mach->memory.WriteU8(hl, d8);
	mach->cpu.AddPC(1);
	
	printf("LD (HL), %x; -> HL(%x)\n", d8, hl);
}






void scf_37(Machine* const){ ASSERT_INSTR_IMPL();  }






void jr_38(Machine* const mach) {
	// JR C, r8
	// jump if C flag is set
	// operands: 1
	// clock cycles: if jumps 12, else 8
	const auto pc = mach->cpu.GetPC();
	const auto r8 = mach->memory.ReadS8(pc);
	const auto carry_flag = mach->cpu.GetFlags(Cpu::FLAG_C);
	const uint16_t jump_addr = (pc+r8) + 1;

	if(carry_flag)
		mach->cpu.SetPC(jump_addr);
	else
		mach->cpu.AddPC(1);


	printf("JR C, %x\n", jump_addr);
}





void add_39(Machine* const){ ASSERT_INSTR_IMPL();  }
void ld_3A(Machine* const) { ASSERT_INSTR_IMPL();  }
void dec_3B(Machine* const){ ASSERT_INSTR_IMPL();  }




void inc_3C(Machine* const mach) {
	// INC A
	// increment A
	// operands: 0
	// clock cycles: 4
	// flags affected: Z 0 H -
	const auto a = mach->cpu.GetA();
	const auto result = mach->cpu.INC(a);
	mach->cpu.SetA(result);

	printf("INC A; -> A(%x), Result(%x) | ", a, result);
	mach->cpu.ShowFlags();
}




void dec_3D(Machine* const mach) { 
	// DEC A
	// decrement A
	// operands: 0
	// clock cycles: 4
	// flags affected: Z 1 H -
	const auto a = mach->cpu.GetA();
	const auto result = mach->cpu.DEC(a);
	mach->cpu.SetA(result);

	printf("DEC A; -> A(%x), Result(%x) | ", a, result);
	mach->cpu.ShowFlags();
}








void ld_3E(Machine* const mach) { 
	// LD A, d8
	// loads immediate 8 bit value into A
	// operands: 1
	// clock cycles: 7 or 8 ?
	const auto pc = mach->cpu.GetPC();
	const auto d8 = mach->memory.ReadU8(pc);
	mach->cpu.SetA(d8);
	mach->cpu.AddPC(1);

	printf("LD A, %x\n", d8);
}





void ccf_3F(Machine* const){ ASSERT_INSTR_IMPL();  }






// 0x40
void ld_40(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_41(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_42(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_43(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_44(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_45(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_46(Machine* const) { ASSERT_INSTR_IMPL();  }








void ld_47(Machine* const mach) {
	// LD B, A
	// value in A is stored in B
	// operands: 0
	// clock cycles: 4
	const auto a = mach->cpu.GetA();
	mach->cpu.SetB(a);
	
	
	printf("LD B, A; -> A(%x)\n", a);
}







void ld_48(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_49(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_4A(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_4B(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_4C(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_4D(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_4E(Machine* const) { ASSERT_INSTR_IMPL();  }





void ld_4F(Machine* const mach) {
	// LD C, A
	// value in A is stored in C
	// operands: 0
	// clock cycles: 4
	const auto a = mach->cpu.GetA();
	mach->cpu.SetC(a);
	
	
	printf("LD C, A; -> A(%x)\n", a);
}









// 0x50
void ld_50(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_51(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_52(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_53(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_54(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_55(Machine* const) { ASSERT_INSTR_IMPL();  }








void ld_56(Machine* const mach) {
	// LD D, (HL)
	// value in memory address pointed by HL is stored in D
	// operands: 0
	// clock cycles: 8
	const auto hl = mach->cpu.GetHL();
	const auto value = mach->memory.ReadU8(hl);
	mach->cpu.SetD(value); 
	

	printf("LD D, (HL); -> HL(%x), (HL)(%x)\n", hl, value);
}









void ld_57(Machine* const mach) {
	// LD D, A
	// the value in A is loaded into D
	// operands: 0
	// clock cycles: 4
	const auto a = mach->cpu.GetA();
	mach->cpu.SetD(a);
	

	printf("LD D, A; -> A(%x)\n", a);
}







void ld_58(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_59(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_5A(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_5B(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_5C(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_5D(Machine* const) { ASSERT_INSTR_IMPL();  }







void ld_5E(Machine* const mach) {
	// LD E, (HL)
	// value in address pointed by HL is stored into E
	// operands: 0
	// clock cycles: 8
	const auto hl = mach->cpu.GetHL();
	const auto value = mach->memory.ReadU8(hl);
	mach->cpu.SetE(value);
	


	printf("LD E, (HL); -> HL(%x), (HL)(%x)\n", hl, value);
}







void ld_5F(Machine* const mach) {
	// LD E, A
	// value in A is stored in E
	// operands: 0
	// clock cycles: 4
	const auto a = mach->cpu.GetA();
	mach->cpu.SetE(a);
	
	
	printf("LD E, A; -> A(%x)\n", a);
}









// 0x60
void ld_60(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_61(Machine* const) { ASSERT_INSTR_IMPL();  }








void ld_62(Machine* const mach) {
	// LD H, D
	// value in D is stored into H
	// operands: 0
	// clock cycles: 4
	
	const auto d = mach->cpu.GetD();
	mach->cpu.SetH(d);
	

	printf("LD H, D; -> D(%x)\n", d);
}




void ld_63(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_64(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_65(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_66(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_67(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_68(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_69(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_6A(Machine* const) { ASSERT_INSTR_IMPL();  }







void ld_6B(Machine* const mach) {
	// LD L, E
	// value in E is stored in L
	// operands: 0
	// clock cycles: 4
	const auto e = mach->cpu.GetE();
	mach->cpu.SetL(e);
	

	printf("LD L, E; -> E(%x)\n", e);
}









void ld_6C(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_6D(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_6E(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_6F(Machine* const) { ASSERT_INSTR_IMPL();  }






// 0x70
void ld_70(Machine* const mach) {
	// LD (HL), B
	// value in B is stored into address pointed by HL
	// operands: 0
	// clock cycles: 8
	const auto hl = mach->cpu.GetHL();
	const auto b = mach->cpu.GetB();
	mach->memory.WriteU8(hl, b);
	

	printf("LD (HL), B; -> HL(%x), B(%x)\n", hl, b);
}











void ld_71(Machine* const mach) {
	// LD (HL), C
	// value in C is stored into address pointed by HL
	// operands: 0
	// clock cycles: 8
	const auto hl = mach->cpu.GetHL();
	const auto c  = mach->cpu.GetC();
	mach->memory.WriteU8(hl, c);
	

	printf("LD (HL), C; -> HL(%x), C(%x)\n", hl, c);
}








void ld_72(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_73(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_74(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_75(Machine* const) { ASSERT_INSTR_IMPL();  }
void halt_76(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_77(Machine* const) { ASSERT_INSTR_IMPL();  }






void ld_78(Machine* const mach) {
	// LD A, B
	// store value in B into A
	// operands: 0
	// clock cycles: 4
	const auto b = mach->cpu.GetB();
	mach->cpu.SetA(b);
	
	
	printf("LD A, B; -> B(%x)\n", b);
}







void ld_79(Machine* const mach) {
	// LD A, C
	// value in C is stored in A
	// operands: 0
	// clock cycles: 4
	const auto c = mach->cpu.GetC();
	mach->cpu.SetA(c);
	
	
	printf("LD A, C; -> C(%x)\n", c);
}










void ld_7A(Machine* const mach) {
	// LD A, D
	// value in D is stored in A
	// operands: 0
	// clock cycles: 4
	const auto d = mach->cpu.GetD();
	mach->cpu.SetA(d);
	
 
	printf("LD A, D; -> D(%x)\n", d);
}







void ld_7B(Machine* const) { ASSERT_INSTR_IMPL();  }






void ld_7C(Machine* const mach) {
	// LD A, H
	// store value in H into A
	// operands: 0
	// clock cycles: 4
	const auto h = mach->cpu.GetH();
	mach->cpu.SetA(h);
	
	
	printf("LD A, H; -> H(%x)\n", h);
}







void ld_7D(Machine* const) { ASSERT_INSTR_IMPL();  }






void ld_7E(Machine* const mach) {
	// LD A, (HL)
	// value in mem pointed by HL is stored in A
	// operands: 0
	// clock cycles: 8
	const auto hl = mach->cpu.GetHL();
	const auto value = mach->memory.ReadU8(hl);
	mach->cpu.SetA(value);
	
	printf("LD A, (HL); -> HL(%x), (HL)(%x)\n", hl, value);
}







void ld_7F(Machine* const) { ASSERT_INSTR_IMPL();  }









// 0x90
void add_80(Machine* const) { ASSERT_INSTR_IMPL();  }
void add_81(Machine* const) { ASSERT_INSTR_IMPL();  }
void add_82(Machine* const) { ASSERT_INSTR_IMPL();  }
void add_83(Machine* const) { ASSERT_INSTR_IMPL();  }
void add_84(Machine* const) { ASSERT_INSTR_IMPL();  }
void add_85(Machine* const) { ASSERT_INSTR_IMPL();  }
void add_86(Machine* const) { ASSERT_INSTR_IMPL();  }






void add_87(Machine* const mach) {
	// ADD A, A
	// add A into A
	// operands: 0
	// clock cycles: 4
	// flags affected: Z 0 H C
	const auto a = mach->cpu.GetA();
	const auto result = mach->cpu.ADD(a, a);
	mach->cpu.SetA(result);
	

	printf("ADD A, A; -> A(%x), Result(%x) | ", a, result);
	mach->cpu.ShowFlags();
}







void adc_88(Machine* const) { ASSERT_INSTR_IMPL();  }
void adc_89(Machine* const) { ASSERT_INSTR_IMPL();  }
void adc_8A(Machine* const) { ASSERT_INSTR_IMPL();  }
void adc_8B(Machine* const) { ASSERT_INSTR_IMPL();  }
void adc_8C(Machine* const) { ASSERT_INSTR_IMPL();  }
void adc_8D(Machine* const) { ASSERT_INSTR_IMPL();  }
void adc_8E(Machine* const) { ASSERT_INSTR_IMPL();  }
void adc_8F(Machine* const) { ASSERT_INSTR_IMPL();  }






// 0x90
void sub_90(Machine* const) { ASSERT_INSTR_IMPL();  }
void sub_91(Machine* const) { ASSERT_INSTR_IMPL();  }
void sub_92(Machine* const) { ASSERT_INSTR_IMPL();  }
void sub_93(Machine* const) { ASSERT_INSTR_IMPL();  }
void sub_94(Machine* const) { ASSERT_INSTR_IMPL();  }
void sub_95(Machine* const) { ASSERT_INSTR_IMPL();  }
void sub_96(Machine* const) { ASSERT_INSTR_IMPL();  }
void sub_97(Machine* const) { ASSERT_INSTR_IMPL();  }
void sbc_98(Machine* const) { ASSERT_INSTR_IMPL();  }
void sbc_99(Machine* const) { ASSERT_INSTR_IMPL();  }
void sbc_9A(Machine* const) { ASSERT_INSTR_IMPL();  }
void sbc_9B(Machine* const) { ASSERT_INSTR_IMPL();  }
void sbc_9C(Machine* const) { ASSERT_INSTR_IMPL();  }
void sbc_9D(Machine* const) { ASSERT_INSTR_IMPL();  }
void sbc_9E(Machine* const) { ASSERT_INSTR_IMPL();  }
void sbc_9F(Machine* const) { ASSERT_INSTR_IMPL();  }









// 0xA0
void and_A0(Machine* const) { ASSERT_INSTR_IMPL();  }





void and_A1(Machine* const mach) {
	// AND B
	// logical AND on B with A, result in A
	// operands: 0
	// clock cycles: 4
	// flags affected: Z 0 1 0
	const auto b = mach->cpu.GetB();
	const auto a = mach->cpu.GetA();
	const auto result = mach->cpu.AND(b, a);
	mach->cpu.SetA(result);
	
	
	printf("AND B; -> B(%x), A(%x), Result(%x) | ", b, a, result);
	mach->cpu.ShowFlags();
}





void and_A2(Machine* const) { ASSERT_INSTR_IMPL();  }
void and_A3(Machine* const) { ASSERT_INSTR_IMPL();  }
void and_A4(Machine* const) { ASSERT_INSTR_IMPL();  }
void and_A5(Machine* const) { ASSERT_INSTR_IMPL();  }
void and_A6(Machine* const) { ASSERT_INSTR_IMPL();  }






void and_A7(Machine* const mach) {
	// AND A
	// Logically AND A with A, result in A.
	// operands: 0
	// clock cycles: 4
	// flags affected: Z 0 1 0
	const auto a = mach->cpu.GetA();
	const auto result = mach->cpu.AND(a, a);
	mach->cpu.SetA(result);
	
	
	printf("AND A; -> A(%x), Result(%x) | ", a, result);
	mach->cpu.ShowFlags();
}







void xor_A8(Machine* const) { ASSERT_INSTR_IMPL();  }






void xor_A9(Machine* const mach) {
	// XOR C
	// logical XOR on C with A, result in A
	// operands: 0
	// clock cycles: 4
	// flags affected: Z 0 0 0
	const auto a = mach->cpu.GetA();
	const auto c = mach->cpu.GetC();
	const auto result = mach->cpu.XOR(c, a);
	mach->cpu.SetA(result);
	
	
	printf("XOR C; -> C(%x), A(%x), Result(%x) | ", c, a, result);
	mach->cpu.ShowFlags();
}






void xor_AA(Machine* const) { ASSERT_INSTR_IMPL();  }
void xor_AB(Machine* const) { ASSERT_INSTR_IMPL();  }
void xor_AC(Machine* const) { ASSERT_INSTR_IMPL();  }
void xor_AD(Machine* const) { ASSERT_INSTR_IMPL();  }
void xor_AE(Machine* const) { ASSERT_INSTR_IMPL();  }






void xor_AF(Machine* const mach) {
	// XOR A
	// bitwise xor in a with a
	// operands: 0
	// clock cycles: 4
	// flags affected: Z 0 0 0
	const auto a = mach->cpu.GetA();
	const auto result = mach->cpu.XOR(a, a);
	mach->cpu.SetA(result);
	

	printf("XOR A; -> A(%x), Result(%x) | ", a, result);
	mach->cpu.ShowFlags();
}











// 0xB0
void or_B0(Machine* const mach) {
	// OR B
	// logical or on B with A, result in A
	// operands: 0
	// clock cycles: 4
	// flags affected: Z 0 0 0
	const auto b = mach->cpu.GetB();
	const auto a = mach->cpu.GetA();
	const auto result = mach->cpu.OR(b, a);
	mach->cpu.SetA(result);
	
	
	printf("OR B; -> B(%x), A(%x), Result(%x) | ", b, a, result);
	mach->cpu.ShowFlags();
}









void or_B1(Machine* const mach) {
	// OR C
	// or C with A, result in A
	// operands: 0
	// clock cycles: 4
	// flags affected: Z 0 0 0
	const auto a = mach->cpu.GetA();
	const auto c = mach->cpu.GetC();
	const auto result = mach->cpu.OR(c, a);
	mach->cpu.SetA(result);
	
	
	
	printf("OR C; -> A(%x), C(%x), Result(%x) | ", a, c, result);
	mach->cpu.ShowFlags();
}





void or_B2(Machine* const) { ASSERT_INSTR_IMPL();  }
void or_B3(Machine* const) { ASSERT_INSTR_IMPL();  }
void or_B4(Machine* const) { ASSERT_INSTR_IMPL();  }
void or_B5(Machine* const) { ASSERT_INSTR_IMPL();  }








void or_B6(Machine* const mach) {
	// OR (HL)
	// value in memory address pointed by HL is or'ed with A, result in A
	// operands: 0
	// clock cycles: 8
	// flags affected: Z 0 0 0
	const auto a = mach->cpu.GetA();
	const auto hl = mach->cpu.GetHL();
	const auto value = mach->memory.ReadU8(hl);
	const auto result = mach->cpu.OR(value, a);
	mach->cpu.SetA(result);
	

	printf("OR (HL); -> HL(%x), (HL)(%x), A(%x), Result(%x) | ", hl, value, a, result);
	mach->cpu.ShowFlags();
}








void or_B7(Machine* const) { ASSERT_INSTR_IMPL();  }
void cp_B8(Machine* const) { ASSERT_INSTR_IMPL();  }
void cp_B9(Machine* const) { ASSERT_INSTR_IMPL();  }
void cp_BA(Machine* const) { ASSERT_INSTR_IMPL();  }
void cp_BB(Machine* const) { ASSERT_INSTR_IMPL();  }
void cp_BC(Machine* const) { ASSERT_INSTR_IMPL();  }
void cp_BD(Machine* const) { ASSERT_INSTR_IMPL();  }
void cp_BE(Machine* const) { ASSERT_INSTR_IMPL();  }
void cp_BF(Machine* const) { ASSERT_INSTR_IMPL();  }









// 0xC0
void ret_C0(Machine* const mach) { 
	// RET NZ
	// return if zero flag is reset
	// operands: 0
	// clock cycles: 20 if return, 8 if not
	const auto zero_flag = mach->cpu.GetFlags(Cpu::FLAG_Z);
	if (!zero_flag) {
		const auto addr = mach->PopStack16();
		mach->cpu.SetPC(addr);
	}
	else {
		
	}

	printf("RET NZ\n");
}







void pop_C1(Machine* const mach) {
	// POP BC
	// operands: 0
	// clock cycles: 12
	const auto value = mach->PopStack16();
	mach->cpu.SetBC(value);
	
	
	printf("POP BC;\n");
}







void jp_C2(Machine* const mach)   { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }








void jp_C3(Machine* const mach) {
	// JP a16
	// 16 bit address is copied to PC
	// operands: 2
	// clock cycles: 10 or 16 ?
	const auto pc = mach->cpu.GetPC();
	const auto a16 = mach->memory.ReadU16(pc);
	mach->cpu.SetPC(a16);

	printf("JP %x\n", a16);
}






void call_C4(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }






void push_C5(Machine* const mach) {
	// PUSH BC
	// Push register pair BC onto stack.
	// operands: 0
	// clock cycles: 16
	const auto bc = mach->cpu.GetBC();
	mach->PushStack16(bc);
	
	
	printf("PUSH BC\n");
}







void add_C6(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void rst_C7(Machine* const)  { ASSERT_INSTR_IMPL();  }







void ret_C8(Machine* const mach) {
	// RET Z
	// return if z flag is set
	// operands: 0
	// clock cycles: if jump 20. if not 8
	if(mach->cpu.GetFlags(Cpu::FLAG_Z)) {
		const auto address = mach->PopStack16();
		mach->cpu.SetPC(address);
	}
	else {
		
	}
	
	printf("RET Z\n");
}







void ret_C9(Machine* const mach) {
	// RET
	// return from subroutine
	// pop 2 bytes from stack and jump to that address
	// operands: 0
	// clock cycles: 16

	const auto address = mach->PopStack16();
	mach->cpu.SetPC(address);

	printf("RET\n");
}






void jp_CA(Machine* const mach) {
	// JP Z, a16
	// jump to immediate 16 bit address if flag Z is set
	// operands: 2
	// clock cycles: if jump 16. if not 12
	const auto pc = mach->cpu.GetPC();
	const auto a16 = mach->memory.ReadU16(pc);
	const auto zero_flag = mach->cpu.GetFlags(Cpu::FLAG_Z);
	
	if(zero_flag)
		mach->cpu.SetPC(a16);
	else
		mach->cpu.AddPC(2);
	
	printf("JP Z, %x\n", a16);
}







void PREFIX_CB(Machine* const mach) {
	// PREFIX_CB will call a CB instruction
	const auto pc = mach->cpu.GetPC();
	const auto op = mach->memory.ReadU8(pc);
	mach->cpu.AddPC(1);
	printf("CB INSTRUCTION: %x | ", op);
	cb_instructions[op](&mach->cpu);
}







void call_CC(Machine* const mach)   { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }








void call_CD(Machine* const mach) {
	// CALL a16
	// call subroutine at immediate 16 bits address
	// stack grows backwards ?
	// operands: 2
	// clock cycles: 24
	const auto pc = mach->cpu.GetPC();
	const auto a16 = mach->memory.ReadU16(pc);

	mach->PushStack16(pc + 2);
	mach->cpu.SetPC(a16);

	printf("CALL %x\n", a16);
}






void adc_CE(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void rst_CF(Machine* const)  { ASSERT_INSTR_IMPL();  }










// 0xD0
void ret_D0(Machine* const mach) { 
	// RET NC
	// return if C flag is reset
	// operands: 0
	// clock cycles: 20 if return 8 if not
	const auto carry_flag = mach->cpu.GetFlags(Cpu::FLAG_C);

	if(!carry_flag)
		mach->cpu.SetPC(mach->PopStack16());
	else
		


	printf("RET NC;\n");
}









void pop_D1(Machine* const mach) {
	// POP DE
	// Pop two bytes off stack into register pair nn.
	// operands: 0
	// clock cycles: 12
	const auto value = mach->PopStack16();
	mach->cpu.SetDE(value);
	
	
	printf("POP DE;\n");
}







void jp_D2(Machine* const mach)   { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
// MISSING D3 ----
void call_D4(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }








void push_D5(Machine* const mach) {
	// PUSH DE
	// push DE into stack
	// operands: 0
	// clock cycles: 16
	const auto de = mach->cpu.GetDE();
	mach->PushStack16(de);
	
	
	printf("PUSH DE\n");
}








void sub_D6(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void rst_D7(Machine* const)  { ASSERT_INSTR_IMPL();  }
void ret_D8(Machine* const)  { ASSERT_INSTR_IMPL();  }


void reti_D9(Machine* const mach) {
	// RETI
	// return from interrupt/subroutine - 
	// pop 2 bytes of the stack, jump to that address, enable interrupts
	// operands: 0
	// clock cycles: 16
	const auto addr = mach->PopStack16();
	mach->cpu.SetPC(addr);
	mach->SetIME(true);
}





void jp_DA(Machine* const mach)   { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
// MISSING DB -----
void call_DC(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
// MISSING DD -----
void sbc_DE(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void rst_DF(Machine* const)  { ASSERT_INSTR_IMPL();  }









// 0xE0
void ldh_E0(Machine* const mach) {
	// LDH (a8), A
	// store value in A into memory address 0xFF00 + a8
	// operands: 1
	// clock cycles: 12
	const auto a = mach->cpu.GetA();
	const auto pc = mach->cpu.GetPC();
	const auto a8 = mach->memory.ReadU8(pc);
	mach->memory.WriteU8(0xFF00 + a8, a);
	mach->cpu.AddPC(1);

	printf("LDH (0xFF00 + %x), A; -> A(%x)\n", a8, a);
}









void pop_E1(Machine* const mach) {
	// POP HL
	// pop 2 bytes off stack into register HL
	// operands: 0
	// clock cycles: 12
	const auto value = mach->PopStack16();
	mach->cpu.SetHL(value);
	

	printf("POP HL\n");
}








void ld_E2(Machine* const mach) {
	// LD (C), A
	// store value in A into memory address 0xFF00 + C
	// operand length: 0
	// clock cycles: 8
	const auto c = mach->cpu.GetC();
	const auto a = mach->cpu.GetA();
	mach->memory.WriteU8(0xFF00 + c, a);
	printf("LD (C), A; -> C(%x), A(%x)\n", c, a);
}






// MISSING E3 ----
// MISSING E4 ----







void push_E5(Machine* const mach) {
	// PUSH HL
	// push hl register into stack
	// operands: 0
	// clock cycles: 16
	const auto hl = mach->cpu.GetHL();
	mach->PushStack16(hl);
	

	printf("PUSH HL\n");
}









void and_E6(Machine* const mach) {
	// AND d8
	// logical AND d8 with A, result in A.
	// operands: 1
	// clock cycles: 8
	// flags affected: Z 0 1 0
	const auto a = mach->cpu.GetA();
	const auto pc = mach->cpu.GetPC();
	const auto d8 = mach->memory.ReadU8(pc);
	const auto result = mach->cpu.AND(d8, a);
	mach->cpu.SetA(result);
	mach->cpu.AddPC(1);
	
	printf("AND %x; -> A(%x), Result(%x) | ", d8, a, result);
	mach->cpu.ShowFlags();
}






void rst_E7(Machine* const) { ASSERT_INSTR_IMPL();  }










void add_E8(Machine* const mach) {
	// ADD SP, operands: 2
	// add immediate signed 8 bit data to SP
	// operands: 1
	// clock cycles: 16
	// flags affected: 0 0 H C
	const auto pc = mach->cpu.GetPC();
	const auto sp = mach->cpu.GetSP();
	const auto r8 = mach->memory.ReadS8(pc);
	const uint32_t result = sp + r8;
	const uint8_t flags_result = CheckH_11th_bit(sp, r8) | CheckC_15th_bit(result);
	mach->cpu.SetF(flags_result);
	
	mach->cpu.SetSP(result & 0xffff);
	mach->cpu.AddPC(1);
	
	printf("ADD SP, %i; -> SP(%x) | ", r8, result);
	mach->cpu.ShowFlags();
}










void jp_E9(Machine* const mach) {
	// JP (HL)
	// Jump to address contained in HL
	// operands: 0
	// clock cycles: 4
	const auto hl = mach->cpu.GetHL();
	mach->cpu.SetPC(hl);
	
	printf("JP (HL); HL -> (%x)\n", hl);
}









void ld_EA(Machine* const mach) {
	// LD (a16), A
	// store value in A into immediate 16 bits address
	// operands: 2
	// clock cycles: 16
	const auto pc = mach->cpu.GetPC();
	const auto a16 = mach->memory.ReadU16(pc);
	const auto a = mach->cpu.GetA();
	mach->memory.WriteU8(a16, a);
	mach->cpu.AddPC(2);


	printf("LD (%x), A; -> A(%x)\n", a16, a);
}







// MISSING EB -----
// MISSING EC -----
// MISSING ED -----
void xor_EE(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }





void rst_EF(Machine* const mach) {
	// RST 28H
	// push present address onto stack, and jump to 0x0000 + 0x28
	// operands: 0
	// clock cycles: 16
	const auto pc = mach->cpu.GetPC();
	mach->PushStack16(pc);
	mach->cpu.SetPC(0x0028);
	
	printf("RST 28H\n");
}












// 0XF0
void ldh_F0(Machine* const mach) {
	// LDH A, (a8)
	// put content of memory address  (0xFF00 + immediate 8 bit value(a8)) into A
	// operands: 1
	// clock cycles: 12
	const auto pc = mach->cpu.GetPC();
	const auto a8 = mach->memory.ReadU8(pc);
	const uint16_t evaluated_address = 0xFF00 + a8;
	const auto value = mach->memory.ReadU8(evaluated_address);
	mach->cpu.SetA(value);
	mach->cpu.AddPC(1);


	printf("LDH A, (0xff00 + %x); -> A(%x)\n", a8, value);
}








void pop_F1(Machine* const mach) {
	// POP AF
	// pop 16 bits from stack into AF
	// operands: 0
	// clock cycles: 12
	// flags affected: all
	const auto value = mach->PopStack16();
	mach->cpu.SetAF(value);
	
	
	printf("POP AF\n");
}







void ld_F2(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }










void di_F3(Machine* const mach) {
	// DI
	// resets both interrupt flip-flops
	// thus preventing maskable interrupts from triggering
	// operands: 0
	// clock cycles: 4
	// TODO: back here when interrupts are implemented
	mach->SetIME(false);
	const auto interrupt_enabled = mach->memory.GetIE();
	mach->memory.SetIE(interrupt_enabled & ~INTERRUPT_IMA);
	
	printf("DI\n");
}










// MISSING F4 ----





void push_F5(Machine* const mach) {
	// PUSH AF
	// push register AF into stack
	// operands: 0
	// clock cycles: 16
	mach->PushStack16(mach->cpu.GetAF());
	

	printf("PUSH AF\n");
}







void or_F6(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void rst_F7(Machine* const) { ASSERT_INSTR_IMPL();  }
void ld_F8(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_F9(Machine* const)  { ASSERT_INSTR_IMPL();  }








void ld_FA(Machine* const mach) {
	// LD A, (a16)
	// value in address pointe immediate 16 bit value is stored into A
	// operands: 2
	// clock cycles: 16
	const auto pc = mach->cpu.GetPC();
	const auto a16 = mach->memory.ReadU16(pc);
	const auto value = mach->memory.ReadU8(a16);
	mach->cpu.SetA(value);
	mach->cpu.AddPC(2);

	printf("LD A, (%x); -> A(%x)\n", a16, value);
}









void ei_FB(Machine* const mach) { 
	// EI
	// enable interrupts, but not immediatly
	// interrupts are enabled after the next instructions is executed
	// operands: 0
	// clock cycles: 4
	// TODO: back here when interrupts are implement
	printf("EI\n");
	mach->SetIME(true);
	
}


// FC MISSING -----
// FD MISSING -----






void cp_FE(Machine* const mach) {
	// CP d8
	// compare A with immediate 8 bits value d8, throws alway the result
	// operands: 1
	// clock cycles: 8
	// flags affected: Z 1 H C
	const auto pc = mach->cpu.GetPC();
	const auto a = mach->cpu.GetA();
	const auto d8 = mach->memory.ReadU8(pc);
	const auto result = mach->cpu.SUB(a, d8);
	mach->cpu.AddPC(1);

	printf("CP %x; -> A(%X), Result(%x) | ", d8, a, result);
	mach->cpu.ShowFlags();
}






void rst_FF(Machine* const) { ASSERT_INSTR_IMPL();  }











}
