#include <stdio.h>
#include <Utix/Assert.h>
#include "Machine.h"
#include "Instructions.h"

namespace gbx {



InstructionFunction main_instructions[0x100] = 
{
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






#ifdef _DEBUG
#define ASSERT_INSTR_IMPL() puts(__func__); ASSERT_MSG(false, "Instruction Not Implemented!")
#else
#define ASSERT_INSTR_IMPL() puts(__func__);
#endif



// common names:
// d8:  immediate 8 bit value
// d16: immediate 16 bit value
// a8:  8 bit unsigned data, which are added to $FF00 in certain instructions (replacement for missing IN and OUT instructions)
// a16: 16 bit address
// r8: means 8 bit signed data, which are added to program counter




// Main instructions implementation:
// 0x00

void miss_instr(Machine* const mach) {
	// not implemented instruction
	mach->cpu.AddPC(1);
	
	printf("MISSING INSTRUCTION! opcode: %x\n", mach->cpu.GetOP());	
}



void nop_00(Machine* const mach) {
	// no operation is performed
	// bytes: 1
	// clock cyles: 4
	mach->cpu.AddPC(1);
	printf("NOP\n");
}


void ld_01(Machine* const mach) {
	// LD BC, d16
	// load immediate 16 bits value into BC
	// bytes: 3
	// clock cyles: 10 or 12 ?
	const auto pc = mach->cpu.GetPC();
	const auto d16 = mach->memory.ReadU16(pc + 1);
	mach->cpu.SetBC(d16);
	mach->cpu.AddPC(3);


	printf("LD BC, %x\n", d16);
}




void ld_02(Machine* const mach) {
	// LD (BC), A
	// value in register A is stored in memory location pointed by BC
	// bytes: 1
	// clock cycles: 7 or 8 ?
	const auto bc = mach->cpu.GetBC();
	const auto a = mach->cpu.GetA();

	mach->memory.WriteU8(bc, a);
	mach->cpu.AddPC(1);


	printf("LD (BC), A; ->  BC = (%x), A = (%x)\n", bc, a);
}




void inc_03(Machine* const mach) {
	// INC BC
	// adds one to BC
	// bytes: 1
	// clock cyles: 6 or 8 ?
	const auto bc = mach->cpu.GetBC() + 1;
	mach->cpu.SetBC(bc);
	mach->cpu.AddPC(1);

	printf("INC BC; -> BC(%x)\n", bc);
}





void inc_04(Machine* const mach) { 
	// INC B
	// adds one to B
	// bytes: 1
	// clock cyles: 4
	// flags affected Z 0 H -
	const auto b = mach->cpu.GetB();
	const auto result = mach->cpu.ADDWithZNH(b, 1);
	mach->cpu.SetB(result);
	mach->cpu.AddPC(1);

	printf("INC B; -> B(%x)\n", result);
}




void dec_05(Machine* const mach) {
	// DEC B
	// decrement B by 1
	// bytes: 1
	// clock cycles: 4
	// flags affected Z 1 H -
	const auto b = mach->cpu.GetB();
	const auto result = mach->cpu.SUBWithZNH(b, 1);
	mach->cpu.SetB(result);
	mach->cpu.AddPC(1);

	printf("DEC B; -> B(%x)\n", result);
}



void ld_06(Machine* const mach) {
	// LD B, d8
	// loads immediate 8 bit value into B
	// bytes: 2
	// clock cycles: 7 or 8 ?
	const auto pc = mach->cpu.GetPC();
	const auto d8 = mach->memory.ReadU8(pc + 1);
	mach->cpu.SetB(d8);
	mach->cpu.AddPC(2);


	printf("LD B, %x\n", d8); 
}






void rlca_07(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_08(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(3); }
void add_09(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_0A(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void dec_0B(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void inc_0C(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }



void dec_0D(Machine* const mach) {
	// DEC C
	// subtract C by one
	// bytes: 1
	// clock cycles: 4
	// flags affected: Z 1 H
	const auto c = mach->cpu.GetC();
	const auto result = mach->cpu.SUBWithZNH(c, 1);
	mach->cpu.SetC(result);
	mach->cpu.AddPC(1);

	printf("DEC C; -> C(%x)\n", result);
}



void ld_0E(Machine* const mach) { 
	// LD C, d8
	// loads immediate 8 bit value into C
	// bytes: 2
	// clock cycles: 7 or 8 ?
	const auto pc = mach->cpu.GetPC();
	const auto d8 = mach->memory.ReadU8(pc + 1);
	mach->cpu.SetC(d8);
	mach->cpu.AddPC(2);

	printf("LD C, %x\n", d8);
}





void rrca_0F(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }









// 0x10
void stop_10(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void ld_11(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(3); }
void ld_12(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void inc_13(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void inc_14(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void dec_15(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_16(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void rla_17(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void jr_18(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void add_19(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_1A(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void dec_1B(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void inc_1C(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void dec_1D(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_1E(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void rra_1F(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }









// 0x20


void jr_20(Machine* const mach) {
	// JR NZ, r8
	// jump if Z flags is reset
	// bytes: 2
	// clock cycles: 12 if jumps, 8 if not

	const auto pc = mach->cpu.GetPC();
	const auto r8 = mach->memory.ReadS8(pc + 1);

	if(mach->cpu.GetFlags(Cpu::FLAG_Z) == 0)
		mach->cpu.AddPC(r8+2);
	else 
		mach->cpu.AddPC(2);


	printf("JR NZ, %d\n", r8);
}





void ld_21(Machine* const mach) {
	// LD HL, d16
	// load immediate 16 bit value into HL
	// bytes: 3
	// clock cycles: 10 or 12
	const auto pc = mach->cpu.GetPC();
	const auto d16 = mach->memory.ReadU16(pc + 1);
	mach->cpu.SetHL(d16);
	mach->cpu.AddPC(3);


	printf("LD HL, %x\n", d16);
}



void ld_22(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }





void inc_23(Machine* const mach) {
	// INC HL
	// bytes: 1
	// clock cycles: 8
	const auto result = mach->cpu.GetHL() + 1;
	mach->cpu.SetHL(result);
	mach->cpu.AddPC(1);

	printf("INC HL; -> HL(%x)\n", result);
}





void inc_24(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void dec_25(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_26(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void daa_27(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }


void jr_28(Machine* const mach) {
	// JP Z, r8
	// jump if Z flag is set
	// bytes: 2
	// clock cycles: if jumps 12, else 8
	const auto pc = mach->cpu.GetPC();
	const auto r8 = mach->memory.ReadS8(pc + 1);
	const auto zero_flag = mach->cpu.GetFlags(Cpu::FLAG_Z);
	mach->cpu.AddPC( zero_flag ? (r8+2) : 2 );
	
	printf("JP Z, %x\n", r8);
}



void add_29(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }





void ld_2A(Machine* const mach) {
	// LD A, (HL+)
	// store value in address pointed by HL into A, increment HL
	// bytes: 1
	// clock cycles: 8
	const auto hl = mach->cpu.GetHL();
	const auto value = mach->memory.ReadU8(hl);
	mach->cpu.SetA(value);
	mach->cpu.SetHL(hl + 1);
	mach->cpu.AddPC(1); 

	printf("LD A, (HL+); HL -> (%x)\n", hl);
}







void dec_2B(Machine* const mach) {
	// DEC HL
	// decrement register HL by 1
	// bytes: 1
	// clock cycles: 8
	const auto result = mach->cpu.GetHL() - 1;
	mach->cpu.SetHL(result);
	mach->cpu.AddPC(1);
	
	printf("DEC HL; -> HL(%x)\n", result);
}






void inc_2C(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void dec_2D(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_2E(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void cpl_2F(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }






// 0x30
void jr_30(Machine* const mach) {
	// JR NC, r8
	// jump if C flag is reset
	// bytes: 2
	// clock cycles: 12 if jump 8 if not
	
	const auto c_flag = mach->cpu.GetFlags(Cpu::FLAG_C);
	const auto pc = mach->cpu.GetPC();
	const auto r8 = mach->memory.ReadS8(pc + 1);
	
	if(!c_flag)
		mach->cpu.AddPC(r8+2);
	else
		mach->cpu.AddPC(2);
	
	printf("JR NC, %d\n", r8);
}



void ld_31(Machine* const mach) {
	// LD SP, d16
	// loads immediate 16 bits value into SP
	// bytes: 3
	// clock cycles: 10 or 12 ?
	const auto pc = mach->cpu.GetPC();
	const auto d16 = mach->memory.ReadU16(pc + 1);
	mach->cpu.SetSP(d16);
	mach->cpu.AddPC(3); 

	printf("LD SP, %x\n", d16);
}


void ld_32(Machine* const mach) {
	// LD (HL-), A or LDD (HL), A
	// store A into memory pointed by HL, Decrements HL
	// bytes: 1
	// clock cycles: 8
	const auto a = mach->cpu.GetA();
	auto hl = mach->cpu.GetHL();	
	mach->memory.WriteU8(hl--, a);
	mach->cpu.SetHL(hl);
	mach->cpu.AddPC(1);

	printf("LD (HL-), A; -> HL(%x) , A(%x)\n", hl, a);
}





void inc_33(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void inc_34(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void dec_35(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_36(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void scf_37(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }





void jr_38(Machine* const mach) {
	// JR C, r8
	// jump if C flag is set
	// bytes: 2
	// clock cycles: if jumps 12, else 8
	const auto pc = mach->cpu.GetPC();
	const auto r8 = mach->memory.ReadS8(pc + 1 );
	const auto c_flag = mach->cpu.GetFlags(Cpu::FLAG_C);

	if(c_flag)
		mach->cpu.AddPC(r8+2);
	else
		mach->cpu.AddPC(2);

	printf("JR C, %i\n", r8);
}





void add_39(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_3A(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void dec_3B(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void inc_3C(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void dec_3D(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }





void ld_3E(Machine* const mach) { 
	// LD A, d8
	// loads immediate 8 bit value into A
	// bytes: 2
	// clock cycles: 7 or 8 ?
	const auto pc = mach->cpu.GetPC();
	const auto d8 = mach->memory.ReadU8(pc + 1);
	mach->cpu.SetA(d8);
	mach->cpu.AddPC(2);

	printf("LD A, %x\n", d8);
}





void ccf_3F(Machine* const mach){ ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }






// 0x40
void ld_40(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_41(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_42(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_43(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_44(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_45(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_46(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_47(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_48(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_49(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_4A(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_4B(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_4C(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_4D(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_4E(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_4F(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }




// 0x50
void ld_50(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_51(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_52(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_53(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_54(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_55(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }





void ld_56(Machine* const mach) {
	// LD D, (HL)
	// value in memory address pointed by HL is stored in D
	// bytes: 1
	// clock cycles: 8
	const auto hl = mach->cpu.GetHL();
	const auto value = mach->memory.ReadU8(hl);
	mach->cpu.SetD(value); 
	mach->cpu.AddPC(1);

	printf("LD D, (HL); -> HL(%x), D(%x)\n", hl, value);
}





void ld_57(Machine* const mach) {
	// LD D, A
	// the value in A is loaded into D
	// bytes: 1
	// clock cycles: 4
	const auto a = mach->cpu.GetA();
	mach->cpu.SetD(a);
	mach->cpu.AddPC(1);

	printf("LD D, A; -> A(%x)\n", a);
}




void ld_58(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_59(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_5A(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_5B(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_5C(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_5D(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }




void ld_5E(Machine* const mach) {
	// LD E, (HL)
	// value in address pointed by HL is stored into E
	// bytes: 1
	// clock cycles: 8
	const auto hl = mach->cpu.GetHL();
	const auto value = mach->memory.ReadU8(hl);
	mach->cpu.SetE(value);
	mach->cpu.AddPC(1);


	printf("LD E, (HL); -> HL(%x), E(%x)\n", hl, value);
}







void ld_5F(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }





// 0x60
void ld_60(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_61(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }





void ld_62(Machine* const mach) {
	// LD H, D
	// value in D is stored into H
	// bytes: 1
	// clock cycles: 4
	
	const auto d = mach->cpu.GetD();
	mach->cpu.SetH(d);
	mach->cpu.AddPC(1);

	printf("LD H, D; -> D(%x)\n", d);
}




void ld_63(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_64(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_65(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_66(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_67(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_68(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_69(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_6A(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }





void ld_6B(Machine* const mach) {
	// LD L, E
	// value in E is stored in L
	// bytes: 1
	// clock cycles: 4
	const auto e = mach->cpu.GetE();
	mach->cpu.SetL(e);
	mach->cpu.AddPC(1);

	printf("LD L, E; -> E(%x)\n", e);
}







void ld_6C(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_6D(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_6E(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_6F(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }






// 0x70



void ld_70(Machine* const mach) {
	// LD (HL), B
	// value in B is stored into address pointed by HL
	// bytes: 1
	// clock cycles: 8
	const auto hl = mach->cpu.GetHL();
	const auto b = mach->cpu.GetB();
	mach->memory.WriteU8(hl, b);
	mach->cpu.AddPC(1);

	printf("LD (HL), B; -> HL(%x), B(%x)\n", hl, b);
}







void ld_71(Machine* const mach) {
	// LD (HL), C
	// value in C is stored into address pointed by HL
	// bytes: 1
	// clock cycles: 8
	const auto hl = mach->cpu.GetHL();
	const auto c  = mach->cpu.GetC();
	mach->memory.WriteU8(hl, c);
	mach->cpu.AddPC(1);

	printf("LD (HL), C; -> HL(%x), C(%x)\n", hl, c);
}






void ld_72(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_73(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_74(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_75(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void halt_76(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_77(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_78(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_79(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }



void ld_7A(Machine* const mach) {
	// LD A, D
	// value in D is stored in A
	// bytes: 1
	// clock cycles: 4
	const auto d = mach->cpu.GetD();
	mach->cpu.SetA(d);
	mach->cpu.AddPC(1);
 
	printf("LD A, D; -> A(%x)\n", d);
}



void ld_7B(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_7C(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_7D(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_7E(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_7F(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }






// 0x90
void add_80(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void add_81(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void add_82(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void add_83(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void add_84(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void add_85(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void add_86(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }




void add_87(Machine* const mach) {
	// ADD A, A
	// add A into A
	// bytes: 1
	// clock cycles: 4
	// flags affected: Z 0 H C
	auto a = mach->cpu.GetA();
	a = mach->cpu.ADC8(a, a);
	mach->cpu.SetA(a);
	mach->cpu.AddPC(1);


	printf("ADD A, A; -> A(%x)\n", a);
}




void adc_88(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void adc_89(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void adc_8A(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void adc_8B(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void adc_8C(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void adc_8D(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void adc_8E(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void adc_8F(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }






// 0x90
void sub_90(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sub_91(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sub_92(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sub_93(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sub_94(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sub_95(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sub_96(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sub_97(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sbc_98(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sbc_99(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sbc_9A(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sbc_9B(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sbc_9C(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sbc_9D(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sbc_9E(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sbc_9F(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }







// 0xA0
void and_A0(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void and_A1(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void and_A2(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void and_A3(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void and_A4(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void and_A5(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void and_A6(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void and_A7(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void xor_A8(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void xor_A9(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void xor_AA(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void xor_AB(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void xor_AC(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void xor_AD(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void xor_AE(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }



void xor_AF(Machine* const mach) {
	// XOR A
	// bitwise xor in a with a
	// bytes: 1
	// clock cycles: 4
	// flags affected: Z 0 0 0
	auto a = mach->cpu.GetA();
	a ^= a;

	if(a == 0)
		mach->cpu.SetF( Cpu::FLAG_Z );
	else
		mach->cpu.SetF(0);

	mach->cpu.SetA(a);
	mach->cpu.AddPC(1);

	printf("XOR A; -> A(%x)\n", a);
	mach->cpu.ShowFlags();
}






// 0xB0
void or_B0(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void or_B1(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void or_B2(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void or_B3(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void or_B4(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void or_B5(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }





void or_B6(Machine* const mach) {
	// OR (HL)
	// value in memory address pointed by HL is or'ed with A, result in A
	// bytes: 1
	// clock cycles: 8
	// flags affected: Z 0 0 0
	const auto a = mach->cpu.GetA();
	const auto hl = mach->cpu.GetHL();
	const auto value = mach->memory.ReadU8(hl);
	const auto result = mach->cpu.ORWithZNHC(value, a);
	mach->cpu.SetA(result);
	mach->cpu.AddPC(1);

	printf("OR (HL); -> (HL)(%x) | A(%x)\n", value, a);
}





void or_B7(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void cp_B8(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void cp_B9(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void cp_BA(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void cp_BB(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void cp_BC(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void cp_BD(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void cp_BE(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void cp_BF(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }






// 0xC0
void ret_C0(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void pop_C1(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void jp_C2(Machine* const mach)   { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(3); }


void jp_C3(Machine* const mach)   { 
	// JP a16
	// 16 bit address is copied to PC
	// bytes: 3
	// clock cycles: 10 or 16 ?
	const auto pc = mach->cpu.GetPC();
	const auto a16 = mach->memory.ReadU16(pc + 1);
	mach->cpu.SetPC(a16);

	printf("JP %x\n", a16);
}






void call_C4(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(3); }
void push_C5(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void add_C6(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void rst_C7(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ret_C8(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }





void ret_C9(Machine* const mach) {
	// RET
	// return from subroutine
	// pop 2 bytes from stack and jump to that address
	// bytes: 1
	// clock cycles: 16

	const auto address = mach->PopStack16();
	mach->cpu.SetPC(address);

	printf("RET\n");
}






void jp_CA(Machine* const mach)     { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(3); }
void PREFIX_CB(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void call_CC(Machine* const mach)   { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(3); }





void call_CD(Machine* const mach) {
	// CALL a16
	// call subroutine at immediate 16 bits address
	// stack grows backwards ?
	// bytes: 3
	// clock cycles: 24
	const auto pc = mach->cpu.GetPC();
	const auto a16 = mach->memory.ReadU16(pc + 1);

	// store pc + 3 into stack
	mach->PushStack16(pc + 3);
	mach->cpu.SetPC(a16);

	printf("CALL %x\n", a16);
}






void adc_CE(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void rst_CF(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }








// 0xD0
void ret_D0(Machine* const mach) { 
	// RET NC
	// return if C flag is reset
	// bytes: 1
	// clock cycles: 20 if return 8 if not
	const auto carry_flag = mach->cpu.GetFlags(Cpu::FLAG_C);

	if(carry_flag)
 		mach->cpu.AddPC(1);
	else
		mach->cpu.SetPC(mach->PopStack16());


	printf("RET NC; -> C(%x)\n", carry_flag);
}





void pop_D1(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void jp_D2(Machine* const mach)   { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(3); }
// MISSING ----
void call_D4(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(3); }
void push_D5(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void sub_D6(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void rst_D7(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ret_D8(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void reti_D9(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void jp_DA(Machine* const mach)   { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(3); }
// MISSING -----
void call_DC(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(3); }
// MISSING -----
void sbc_DE(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void rst_DF(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }







// 0xE0
void ldh_E0(Machine* const mach) {
	// LDH (a8), A
	// store value in A into memory address 0xFF00 + a8
	// bytes: 2
	// clock cycles: 12
	const auto a = mach->cpu.GetA();
	const auto pc = mach->cpu.GetPC();
	const auto a8 = mach->memory.ReadU8(pc + 1);
	mach->memory.WriteU8(0xFF00 + a8, a);
	mach->cpu.AddPC(2);

	printf("LDH (0xFF00 + %x), A\n", a8);
}






void pop_E1(Machine* const mach) {
	// POP HL
	// pop 2 bytes off stack into register HL
	// bytes: 1
	// clock cycles: 12
	const auto value = mach->PopStack16();
	mach->cpu.SetHL(value);
	mach->cpu.AddPC(1);

	printf("POP HL; -> HL(%x)\n", value);
}




void ld_E2(Machine* const mach) {
	// LD (C), A
	// store value in A into memory address 0xFF00 + C
	// bytes: 2
	// clock cycles: 8
	const auto c = mach->cpu.GetC();
	const auto a = mach->cpu.GetA();
	mach->memory.WriteU8(0xFF00 + c, a);
	mach->cpu.AddPC(2);

	printf("LD (C), A; -> C(%x), A(%x)\n", c, a);
}



// MISSING E3 ----
// MISSING E4 ----




void push_E5(Machine* const mach) {
	// PUSH HL
	// push hl register into stack
	// bytes: 1
	// clock cycles: 16
	const auto hl = mach->cpu.GetHL();
	mach->PushStack16(hl);
	mach->cpu.AddPC(1);

	printf("PUSH HL\n");
}






void and_E6(Machine* const mach) {
	// AND d8
	// and op on A immediate 8 bit value, result in A
	// bytes: 2
	// clock cycles: 8
	// flags affected: Z 0 1 0
	const auto a = mach->cpu.GetA();
	const auto pc = mach->cpu.GetPC();
	const auto d8 = mach->memory.ReadU8(pc + 1);
	const auto result = mach->cpu.ANDWithZNHC(a, d8);
	mach->cpu.SetA(result);
	mach->cpu.AddPC(2);
	
	printf("AND %x\n", d8);
}






void rst_E7(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void add_E8(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }




void jp_E9(Machine* const mach) {
	// JP (HL)
	// Jump to address contained in HL
	// bytes: 1
	// clock cycles: 4
	const auto hl = mach->cpu.GetHL();
	mach->cpu.SetPC(hl);
	
	printf("JP (HL); HL -> (%x)\n", hl);
}





void ld_EA(Machine* const mach) {
	// LD (a16), A
	// store value in A into immediate 16 bits address
	// bytes: 3
	// clock cycles: 16
	const auto pc = mach->cpu.GetPC();
	const auto a16 = mach->memory.ReadU16(pc + 1);
	const auto a = mach->cpu.GetA();
	mach->memory.WriteU8(a16, a);
	mach->cpu.AddPC(3);


	printf("LD (a16), A; -> a16(%x), A(%x)\n", a16, a);
}






// MISSING -----
// MISSING -----
// MISSING -----
void xor_EE(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void rst_EF(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }







// 0XF0
void ldh_F0(Machine* const mach) {
	// LDH A, (a8)
	// put content of memory address  (0xFF00 + immediate 8 bit value(a8)) into A
	// bytes: 2
	// clock cycles: 12
	const auto pc = mach->cpu.GetPC();
	const auto a8 = mach->memory.ReadU8(pc + 1);
	const uint16_t evaluated_address = 0xFF00 + a8;
	const auto a = mach->memory.ReadU8(evaluated_address);
	mach->cpu.SetA(a);
	mach->cpu.AddPC(2);


	printf("LDH A, (a8); -> pointer(%x), A(%x)\n", evaluated_address, a);
}






void pop_F1(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_F2(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }






void di_F3(Machine* const mach) {
	// DI
	// resets both interrupt flip-flops
	// thus preventing maskable interrupts from triggering
	// bytes: 1
	// clock cycles: 4
	// TODO: back here when interrupts are implemented
	mach->cpu.AddPC(1);

	printf("DI\n");
}






// MISSING ----
void push_F5(Machine* const mach) {
	// PUSH AF
	// push register AF into stack
	// bytes: 1
	// clock cycles: 16
	mach->PushStack16(mach->cpu.GetAF());
	mach->cpu.AddPC(1);

	printf("PUSH AF\n");
}






void or_F6(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void rst_F7(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }
void ld_F8(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(2); }
void ld_F9(Machine* const mach)  { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }



void ld_FA(Machine* const mach) {
	// LD A, (a16)
	// value in address pointe immediate 16 bit value is stored into A
	// bytes: 3
	// clock cycles: 16
	const auto pc = mach->cpu.GetPC();
	const auto a16 = mach->memory.ReadU16( pc + 1 );
	const auto value = mach->memory.ReadU8(a16);
	mach->cpu.SetA(value);
	mach->cpu.AddPC(3);

	printf("LD A, (a16); -> a16(%x), A(%x)\n", a16, value);
}




void ei_FB(Machine* const mach) { 
	// EI
	// enable interrupts, but not immediatly
	// interrupts are enabled after the next instructions is executed
	// bytes: 1
	// clock cycles: 4
	// TODO: back here when interrupts are implemented

	mach->cpu.AddPC(1); 

	printf("EI\n");
}


// FC MISSING -----
// FD MISSING -----






void cp_FE(Machine* const mach) {
	// CP d8
	// compare A with immediate 8 bits value d8, throws alway the result
	// bytes: 2
	// clock cycles: 8
	// flags affected: Z 1 H C

	const auto pc = mach->cpu.GetPC();
	const auto a = mach->cpu.GetA();
	const auto d8 = mach->memory.ReadU8(pc + 1);
	mach->cpu.SBC8(a, d8);
	mach->cpu.AddPC(2);

	printf("CP %x\n", d8);
}






void rst_FF(Machine* const mach) { ASSERT_INSTR_IMPL(); mach->cpu.AddPC(1); }











}
