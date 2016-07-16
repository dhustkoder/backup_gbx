#include <stdio.h>
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











// Main instructions implementation:
// 0x00

void miss_instr(Machine* const mach) {
	// not implemented instruction
	printf("%X: MISSING INSTRUCTION %X\n", mach->cpu.pc, mach->cpu.op);
	++mach->cpu.pc;
}



void nop_00(Machine* const mach) {
	// no operation is performed
	// bytes: 1
	// clock cyles: 4
	printf("%X: NOP\n", mach->cpu.pc);
	++mach->cpu.pc;
}


void ld_01(Machine* const mach) {
	// LD BC, d16
	// load immediate 16 bits value into BC
	// bytes: 3
	// clock cyles: 10 or 12 ?
	
	mach->memory.Read16(mach->cpu.pc + 1, &mach->cpu.B, &mach->cpu.C);

	printf("%X: LD BC, %X\n", mach->cpu.pc, mach->cpu.GetBC());
	mach->cpu.pc += 3;
}




void ld_02(Machine* const mach) {
	// LD (BC), A
	// value in register A is stored in memory location pointed by BC
	// bytes: 1
	// clock cycles: 7 or 8 ?
	mach->memory.Write8(mach->cpu.GetBC(), mach->cpu.A);

	printf("%X: LD (BC), A ; ->  BC = (%X), A = (%X)\n", mach->cpu.pc, mach->cpu.GetBC(), mach->cpu.A);
	++mach->cpu.pc;
}




void inc_03(Machine* const mach) {
	// INC BC
	// adds one to BC
	// bytes: 1
	// clock cyles: 6 or 8 ?
	mach->cpu.AddBC(1);

	printf("%X: INC BC; -> BC(%X)\n", mach->cpu.pc, mach->cpu.GetBC());
	++mach->cpu.pc;
}





void inc_04(Machine* const mach) { 
	// INC B
	// adds one to B
	// bytes: 1
	// clock cyles: 4
	// flags affected Z 0 H -
	

	if( (mach->cpu.B & 0x0F) == 0x0F) {
		mach->cpu.SetFlags(Cpu::Flags::H);
	}
	
	if( ( ++mach->cpu.B ) == 0 ) {
		mach->cpu.SetFlags(Cpu::Flags::Z);
	}

	printf("%X: INC B; -> B(%X)\n", mach->cpu.pc, mach->cpu.B);
	mach->cpu.UnsetFlags(Cpu::Flags::N);
	++mach->cpu.pc;
}




void dec_05(Machine* const mach) {
	// DEC B
	// decrement B by 1
	// bytes: 1
	// clock cycles: 4
	// flags affected Z 1 H -

	if(mach->cpu.B == 0) {
		mach->cpu.SetFlags(Cpu::Flags::H);
	}
	else if(mach->cpu.B == 1) {
		mach->cpu.SetFlags(Cpu::Flags::Z);
	}

	--mach->cpu.B;

	printf("%X: DEC B; -> B(%X)\n", mach->cpu.pc, mach->cpu.B);
	mach->cpu.SetFlags(Cpu::Flags::N);
	mach->cpu.pc += 1;
}



void ld_06(Machine* const mach) {
	// LD B, d8
	// loads immediate 8 bit value into B
	// bytes: 2
	// clock cycles: 7 or 8 ?
	mach->cpu.B = mach->memory.Read8(mach->cpu.pc + 1);
	printf("%X: LD B, %X\n", mach->cpu.pc, mach->cpu.B);
	mach->cpu.pc += 2; 
}






void rlca_07(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void ld_08(Machine* mach)  { puts(__func__); mach->cpu.pc += 3; }
void add_09(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_0A(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }
void dec_0B(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void inc_0C(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }



void dec_0D(Machine* const mach) {
	// DEC C
	// subtract C by one
	// bytes: 1
	// clock cycles: 4
	// flags affected: Z 1 H

	if( mach->cpu.C == 0 ) {
		mach->cpu.SetFlags(Cpu::Flags::H);
	}
	else if(mach->cpu.C == 1) {
		mach->cpu.SetFlags(Cpu::Flags::Z);
	}

	--mach->cpu.C;

	printf("%X: DEC C ; -> C(%X)\n", mach->cpu.pc, mach->cpu.C);
	mach->cpu.SetFlags(Cpu::Flags::N);
	mach->cpu.pc += 1; 
}



void ld_0E(Machine* const mach) { 
	// LD C, d8
	// loads immediate 8 bit value into C
	// bytes: 2
	// clock cycles: 7 or 8 ?
	mach->cpu.C = mach->memory.Read8(mach->cpu.pc + 1);
	printf("%X: LD C, %X\n", mach->cpu.pc, mach->cpu.C);
	mach->cpu.pc += 2;
}





void rrca_0F(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }









// 0x10
void stop_10(Machine* mach){ puts(__func__); mach->cpu.pc += 2; }
void ld_11(Machine* mach)  { puts(__func__); mach->cpu.pc += 3; }
void ld_12(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }
void inc_13(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void inc_14(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void dec_15(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_16(Machine* mach)  { puts(__func__); mach->cpu.pc += 2; }
void rla_17(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void jr_18(Machine* mach)  { puts(__func__); mach->cpu.pc += 2; }
void add_19(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_1A(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }
void dec_1B(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void inc_1C(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void dec_1D(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_1E(Machine* mach)  { puts(__func__); mach->cpu.pc += 2; }
void rra_1F(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }









// 0x20


void jr_20(Machine* const mach) {
	// JR NZ, r8
	// jump if Z flags is reset
	// bytes: 2
	// clock cycles: 12 if jumps, 8 if not

	const int8_t r8 = static_cast<int8_t>(mach->memory.Read8(mach->cpu.pc + 1));

	printf("%X: JR NZ, %d\n", mach->cpu.pc, r8);

	if(mach->cpu.GetFlags(Cpu::Flags::Z) == 0)
		mach->cpu.pc += r8;
	else
		mach->cpu.pc += 2;
}





void ld_21(Machine* const mach) {
	// LD HL, d16
	// load immediate 16 bit value into HL
	// bytes: 3
	// clock cycles: 10 or 12
	mach->memory.Read16(mach->cpu.pc + 1, &mach->cpu.H, &mach->cpu.L);
	printf("%X: LD HL, %X\n", mach->cpu.pc, mach->cpu.GetHL());
	mach->cpu.pc += 3; 
}



void ld_22(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void inc_23(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void inc_24(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void dec_25(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void ld_26(Machine* mach) { puts(__func__); mach->cpu.pc += 2; }
void daa_27(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void jr_28(Machine* mach) { puts(__func__); mach->cpu.pc += 2; }
void add_29(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void ld_2A(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void dec_2B(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void inc_2C(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void dec_2D(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void ld_2E(Machine* mach) { puts(__func__); mach->cpu.pc += 2; }
void cpl_2F(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }






// 0x30
void jr_30(Machine* mach) { puts(__func__); mach->cpu.pc += 2; }



void ld_31(Machine* const mach) {
	// LD SP, d16
	// loads immediate 16 bits value into SP
	// bytes: 3
	// clock cycles: 10 or 12 ?
	mach->cpu.sp = mach->memory.Read16(mach->cpu.pc + 1);
	printf("%X: LD SP, %X\n", mach->cpu.pc, mach->cpu.sp);
	mach->cpu.pc += 3; 
}


void ld_32(Machine* const mach) {
	// LD (HL-), A or LDD (HL), A
	// store A into memory pointed by HL, Decrements HL
	// bytes: 1
	// clock cycles: 8
	const uint16_t HL = mach->cpu.GetHL();
	mach->memory.Write8(HL, mach->cpu.A);
	mach->cpu.SubHL(1);
	printf("%X: LD (HL-), A ; -> HL(%X) , A(%X)\n", mach->cpu.pc, HL, mach->cpu.A);
	mach->cpu.pc += 1; 
}





void inc_33(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void inc_34(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void dec_35(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void ld_36(Machine* mach) { puts(__func__); mach->cpu.pc += 2; }
void scf_37(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void jr_38(Machine* mach) { puts(__func__); mach->cpu.pc += 2; }
void add_39(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void ld_3A(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void dec_3B(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void inc_3C(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void dec_3D(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }


void ld_3E(Machine* const mach) { 
	// LD A, d8
	// loads immediate 8 bit value into A
	// bytes: 2
	// clock cycles: 7 or 8 ?
	
	mach->cpu.A = mach->memory.Read8(mach->cpu.pc + 1);
	printf("%X: LD A, %X\n", mach->cpu.pc, mach->cpu.A);
	mach->cpu.pc += 2;
}


void ccf_3F(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }






// 0x40
void ld_40(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_41(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_42(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_43(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_44(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_45(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_46(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_47(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_48(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_49(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_4A(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_4B(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_4C(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_4D(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_4E(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_4F(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }




// 0x50
void ld_50(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_51(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_52(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_53(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_54(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_55(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_56(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }



void ld_57(Machine* const mach) {
	// LD D, A
	// the value in A is loaded into D
	// bytes: 1
	// clock cycles: 4
	mach->cpu.D = mach->cpu.A;
	printf("%X: LD D, A; -> A(%X)\n", mach->cpu.pc, mach->cpu.A);
	++mach->cpu.pc;
}




void ld_58(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_59(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_5A(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_5B(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_5C(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_5D(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_5E(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_5F(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }





// 0x60
void ld_60(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_61(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_62(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_63(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_64(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_65(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_66(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_67(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_68(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_69(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_6A(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_6B(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_6C(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_6D(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_6E(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_6F(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }






// 0x70
void ld_70(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_71(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_72(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_73(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_74(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_75(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void halt_76(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_77(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_78(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_79(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }



void ld_7A(Machine* mach) {
	// LD D, A
	// value A is stored in D
	// bytes: 1
	// clock cycles: 4

	mach->cpu.D = mach->cpu.A;
	printf("%X: LD D, A; -> A(%X)\n", mach->cpu.pc, mach->cpu.A);
	mach->cpu.pc += 1; 
}



void ld_7B(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_7C(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_7D(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_7E(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_7F(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }






// 0x90
void add_80(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void add_81(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void add_82(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void add_83(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void add_84(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void add_85(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void add_86(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void add_87(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void adc_88(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void adc_89(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void adc_8A(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void adc_8B(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void adc_8C(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void adc_8D(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void adc_8E(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void adc_8F(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }






// 0x90
void sub_90(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sub_91(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sub_92(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sub_93(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sub_94(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sub_95(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sub_96(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sub_97(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sbc_98(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sbc_99(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sbc_9A(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sbc_9B(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sbc_9C(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sbc_9D(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sbc_9E(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sbc_9F(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }







// 0xA0
void and_A0(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void and_A1(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void and_A2(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void and_A3(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void and_A4(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void and_A5(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void and_A6(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void and_A7(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void xor_A8(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void xor_A9(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void xor_AA(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void xor_AB(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void xor_AC(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void xor_AD(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void xor_AE(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }



void xor_AF(Machine* const mach) {
	// XOR A
	// bitwise xor in a with a
	// bytes: 1
	// clock cycles: 4
	// flags affected: Z 0 0 0

	mach->cpu.A ^= mach->cpu.A;

	if(mach->cpu.A == 0) {
		mach->cpu.SetFlags(Cpu::Flags::Z);
	}

	printf("%X: XOR A; -> A(%X)\n", mach->cpu.pc, mach->cpu.A);
	mach->cpu.UnsetFlags(Cpu::Flags::N | Cpu::Flags::H | Cpu::Flags::C);
	++mach->cpu.pc;
}






// 0xB0
void or_B0(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void or_B1(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void or_B2(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void or_B3(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void or_B4(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void or_B5(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void or_B6(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void or_B7(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void cp_B8(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void cp_B9(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void cp_BA(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void cp_BB(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void cp_BC(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void cp_BD(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void cp_BE(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void cp_BF(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }






// 0xC0
void ret_C0(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }
void pop_C1(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }
void jp_C2(Machine* mach)   { puts(__func__); mach->cpu.pc += 3; }


void jp_C3(Machine* const mach)   { 
	// JP a16
	// 16 bit address is copied to PC
	// bytes: 3
	// clock cycles: 10 or 16 ?
	const uint16_t a16 = mach->memory.Read16(mach->cpu.pc + 1);
	printf("%X: JP %X\n", mach->cpu.pc, a16);
	mach->cpu.pc = a16;
}






void call_C4(Machine* mach) { puts(__func__); mach->cpu.pc += 3; }
void push_C5(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void add_C6(Machine* mach)  { puts(__func__); mach->cpu.pc += 2; }
void rst_C7(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }
void ret_C8(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }

void ret_C9(Machine* const mach) {
	// RET
	// return from subroutine
	// pop 2 bytes from stack and jump to that address
	// bytes: 1
	// clock cycles: 16
	const auto address = mach->memory.Read16(++mach->cpu.sp);
	printf("%X: RET\n", mach->cpu.pc);
	mach->cpu.pc = address;
}



void jp_CA(Machine* mach)   { puts(__func__); mach->cpu.pc += 3; }
void PREFIX_CB(Machine* mach) { puts(__func__); mach->cpu.pc += 2; }
void call_CC(Machine* mach) { puts(__func__); mach->cpu.pc += 3; }



void call_CD(Machine* const mach) {
	// CALL a16
	// call subroutine at immediate 16 bits address
	// stack grows backwards ?
	// bytes: 3
	// clock cycles: 24
	const auto address = mach->memory.Read16(mach->cpu.pc + 1);

	// store pc + 3 into stack
	mach->memory.Write16(mach->cpu.sp--, mach->cpu.pc + 3);


	printf("%X: CALL %X\n", mach->cpu.pc, address);
	mach->cpu.pc = address; 
}




void adc_CE(Machine* mach)  { puts(__func__); mach->cpu.pc += 2; }
void rst_CF(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }








// 0xD0
void ret_D0(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }
void pop_D1(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }
void jp_D2(Machine* mach)   { puts(__func__); mach->cpu.pc += 3; }
// MISSING ----
void call_D4(Machine* mach) { puts(__func__); mach->cpu.pc += 3; }
void push_D5(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void sub_D6(Machine* mach)  { puts(__func__); mach->cpu.pc += 2; }
void rst_D7(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }
void ret_D8(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }
void reti_D9(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void jp_DA(Machine* mach)   { puts(__func__); mach->cpu.pc += 3; }
// MISSING -----
void call_DC(Machine* mach) { puts(__func__); mach->cpu.pc += 3; }
// MISSING -----
void sbc_DE(Machine* mach)  { puts(__func__); mach->cpu.pc += 2; }
void rst_DF(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }







// 0xE0
void ldh_E0(Machine* mach) { puts(__func__); mach->cpu.pc += 2; }
void pop_E1(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_E2(Machine* mach)  { puts(__func__); mach->cpu.pc += 2; }
// MISSING ----
// MISSING ----
void push_E5(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void and_E6(Machine* mach) { puts(__func__); mach->cpu.pc += 2; }
void rst_E7(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void add_E8(Machine* mach) { puts(__func__); mach->cpu.pc += 2; }
void jp_E9(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }


void ld_EA(Machine* const mach) {
	// LD (a16), A
	// store value in A into immediate 16 bits address
	// bytes: 3
	// clock cycles: 16
	const auto address = mach->memory.Read16(mach->cpu.pc + 1);
	mach->memory.Write8(address, mach->cpu.A);
	printf("%X: LD (a16), A; -> a16(%X), A(%X)\n", mach->cpu.pc, address, mach->cpu.A);
	mach->cpu.pc += 3; 
}




// MISSING -----
// MISSING -----
// MISSING -----
void xor_EE(Machine* mach) { puts(__func__); mach->cpu.pc += 2; }
void rst_EF(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }







// 0XF0
void ldh_F0(Machine* mach) { puts(__func__); mach->cpu.pc += 2; }
void pop_F1(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_F2(Machine* mach)  { puts(__func__); mach->cpu.pc += 2; }


void di_F3(Machine* const mach) {
	// DI
	// resets both interrupt flip-flops
	// thus preventing maskable interrupts from triggering
	// bytes: 1
	// clock cycles: 4
	// TODO: back here when interrupts are implemented

	printf("%X: DI\n", mach->cpu.pc);
	++mach->cpu.pc; 
}




// MISSING ----
void push_F5(Machine* mach){ puts(__func__); mach->cpu.pc += 1; }
void or_F6(Machine* mach)  { puts(__func__); mach->cpu.pc += 2; }
void rst_F7(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }
void ld_F8(Machine* mach)  { puts(__func__); mach->cpu.pc += 2; }
void ld_F9(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }
void ld_FA(Machine* mach)  { puts(__func__); mach->cpu.pc += 3; }
void ei_FB(Machine* mach)  { puts(__func__); mach->cpu.pc += 1; }
// MISSING -----
// MISSING -----
void cp_FE(Machine* mach)  { puts(__func__); mach->cpu.pc += 2; }
void rst_FF(Machine* mach) { puts(__func__); mach->cpu.pc += 1; }











}
