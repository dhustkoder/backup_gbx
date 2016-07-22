#include "Machine.h"
#include "Instructions.h"


namespace gbx {


InstructionFunction cb_instructions[0x100] = {
/*        0        1        2        3        4        5        6        7        8        9        A        B        C        D        E        F      */
/*0*/  rlc_00,  rlc_01,  rlc_02,  rlc_03,  rlc_04,  rlc_05,  rlc_06,  rlc_07,  rrc_08,  rrc_09,   rrc_0A, rrc_0B,  rrc_0C,  rrc_0D,  rrc_0E,  rrc_0F,
/*1*/   rl_10,   rl_11,   rl_12,   rl_13,   rl_14,   rl_15,   rl_16,   rl_17,   rr_18,   rr_19,   rr_1A,   rr_1B,   rr_1C,   rr_1D,   rr_1E,   rr_1F,
/*2*/  sla_20,  sla_21,  sla_22,  sla_23,  sla_24,  sla_25,  sla_26,  sla_27,  sra_28,  sra_29,   sra_2A,  sra_2B, sra_2C,  sra_2D,  sra_2E,  sra_2F,
/*3*/ swap_30, swap_31, swap_32, swap_33, swap_34, swap_35, swap_36, swap_37,  srl_38,  srl_39,  srl_3A,  srl_3B,  srl_3C,  srl_3D,  srl_3E,  srl_3F,
/*4*/  bit_40,  bit_41,  bit_42,  bit_43,  bit_44,  bit_45,  bit_46,  bit_47,  bit_48,  bit_49,  bit_4A,  bit_4B,  bit_4C,  bit_4D,  bit_4E,  bit_4F,
/*5*/  bit_50,  bit_51,  bit_52,  bit_53,  bit_54,  bit_55,  bit_56,  bit_57,  bit_58,  bit_59,  bit_5A,  bit_5B,  bit_5C,  bit_5D,  bit_5E,  bit_5F,
/*6*/  bit_60,  bit_61,  bit_62,  bit_63,  bit_64,  bit_65,  bit_66,  bit_67,  bit_68,  bit_69,  bit_6A,  bit_6B,  bit_6C,  bit_6D,  bit_6E,  bit_6F,
/*7*/  bit_70,  bit_71,  bit_72,  bit_73,  bit_74,  bit_75, halt_76,  bit_77,  bit_78,  bit_79,  bit_7A,  bit_7B,  bit_7C,  bit_7D,  bit_7E,  bit_7F,
/*8*/  res_80,  res_81,  res_82,  res_83,  res_84,  res_85,  res_86,  res_87,  res_88,  res_89,  res_8A,  res_8B,  res_8C,  res_8D,  res_8E,  res_8F,
/*9*/  res_90,  res_91,  res_92,  res_93,  res_94,  res_95,  res_96,  res_97,  res_98,  res_99,  res_9A,  res_9B,  res_9C,  res_9D,  res_9E,  res_9F,
/*A*/  res_A0,  res_A1,  res_A2,  res_A3,  res_A4,  res_A5,  res_A6,  res_A7,  res_A8,  res_A9,  res_AA,  res_AB,  res_AC,  res_AD,  res_AE,  res_AF,
/*B*/  res_B0,  res_B1,  res_B2,  res_B3,  res_B4,  res_B5,  res_B6,  res_B7,  res_B8,  res_B9,  res_BA,  res_BB,  res_BC,  res_BD,  res_BE,  res_BF,
/*C*/  set_C0,  set_C1,  set_C2,  set_C3,  set_C4,  set_C5,  set_C6,  set_C7,  set_C8,  set_C9,  set_CA,  set_CB,  set_CC,  set_CD,  set_CE,  set_CF,
/*D*/  set_D0,  set_D1,  set_D2,  set_D3,  set_D4,  set_D5,  set_D6,  set_D7,  set_D8,  set_D9,  set_DA,  set_DB,  set_DC,  set_DD,  set_DE,  set_DF,
/*E*/  set_E0,  set_E1,  set_E2,  set_E3,  set_E4,  set_E5,  set_E6,  set_E7,  set_E8,  set_E9,  set_EA,  set_EB,  set_EC,  set_ED,  set_EE,  set_EF,
/*F*/  set_F0,  set_F1,  set_F2,  set_F3,  set_F4,  set_F5,  set_F6,  set_F7,  set_F8,  set_F9,  set_FA,  set_FB,  set_FC,  set_ED,  set_FE,  set_FF
};



// note: all CB instructons are 2 bytes long, no need to increment PC
// this is done by the CB instructions caller.



// CB Instructions Implementation:
// 0x00
void rlc_00(Machine* const) { ASSERT_INSTR_IMPL(); }
void rlc_01(Machine* const) { ASSERT_INSTR_IMPL(); }
void rlc_02(Machine* const) { ASSERT_INSTR_IMPL(); }
void rlc_03(Machine* const) { ASSERT_INSTR_IMPL(); }
void rlc_04(Machine* const) { ASSERT_INSTR_IMPL(); }
void rlc_05(Machine* const) { ASSERT_INSTR_IMPL(); }
void rlc_06(Machine* const) { ASSERT_INSTR_IMPL(); }
void rlc_07(Machine* const) { ASSERT_INSTR_IMPL(); }
void rrc_08(Machine* const) { ASSERT_INSTR_IMPL(); }
void rrc_09(Machine* const) { ASSERT_INSTR_IMPL(); }
void rrc_0A(Machine* const) { ASSERT_INSTR_IMPL(); }
void rrc_0B(Machine* const) { ASSERT_INSTR_IMPL(); }
void rrc_0C(Machine* const) { ASSERT_INSTR_IMPL(); }
void rrc_0D(Machine* const) { ASSERT_INSTR_IMPL(); }
void rrc_0E(Machine* const) { ASSERT_INSTR_IMPL(); }
void rrc_0F(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x01
void rl_10(Machine* const) { ASSERT_INSTR_IMPL(); }
void rl_11(Machine* const) { ASSERT_INSTR_IMPL(); }
void rl_12(Machine* const) { ASSERT_INSTR_IMPL(); }
void rl_13(Machine* const) { ASSERT_INSTR_IMPL(); }
void rl_14(Machine* const) { ASSERT_INSTR_IMPL(); }
void rl_15(Machine* const) { ASSERT_INSTR_IMPL(); }
void rl_16(Machine* const) { ASSERT_INSTR_IMPL(); }
void rl_17(Machine* const) { ASSERT_INSTR_IMPL(); }
void rr_18(Machine* const) { ASSERT_INSTR_IMPL(); }
void rr_19(Machine* const) { ASSERT_INSTR_IMPL(); }
void rr_1A(Machine* const) { ASSERT_INSTR_IMPL(); }
void rr_1B(Machine* const) { ASSERT_INSTR_IMPL(); }
void rr_1C(Machine* const) { ASSERT_INSTR_IMPL(); }
void rr_1D(Machine* const) { ASSERT_INSTR_IMPL(); }
void rr_1E(Machine* const) { ASSERT_INSTR_IMPL(); }
void rr_1F(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x02
void sla_20(Machine* const) { ASSERT_INSTR_IMPL(); }
void sla_21(Machine* const) { ASSERT_INSTR_IMPL(); }
void sla_22(Machine* const) { ASSERT_INSTR_IMPL(); }
void sla_23(Machine* const) { ASSERT_INSTR_IMPL(); }
void sla_24(Machine* const) { ASSERT_INSTR_IMPL(); }
void sla_25(Machine* const) { ASSERT_INSTR_IMPL(); }
void sla_26(Machine* const) { ASSERT_INSTR_IMPL(); }
void sla_27(Machine* const) { ASSERT_INSTR_IMPL(); }
void sra_28(Machine* const) { ASSERT_INSTR_IMPL(); }
void sra_29(Machine* const) { ASSERT_INSTR_IMPL(); }
void sra_2A(Machine* const) { ASSERT_INSTR_IMPL(); }
void sra_2B(Machine* const) { ASSERT_INSTR_IMPL(); }
void sra_2C(Machine* const) { ASSERT_INSTR_IMPL(); }
void sra_2D(Machine* const) { ASSERT_INSTR_IMPL(); }
void sra_2E(Machine* const) { ASSERT_INSTR_IMPL(); }
void sra_2F(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x03
void swap_30(Machine* const) { ASSERT_INSTR_IMPL(); }
void swap_31(Machine* const) { ASSERT_INSTR_IMPL(); }
void swap_32(Machine* const) { ASSERT_INSTR_IMPL(); }
void swap_33(Machine* const) { ASSERT_INSTR_IMPL(); }
void swap_34(Machine* const) { ASSERT_INSTR_IMPL(); }
void swap_35(Machine* const) { ASSERT_INSTR_IMPL(); }
void swap_36(Machine* const) { ASSERT_INSTR_IMPL(); }







void swap_37(Machine* const mach) {
    // SWAP A
    // swap upper & lower bits of A
    // bytes: 2
    // clock cycles: 8
    // flags affected: Z 0 0 0
    const auto a = mach->cpu.GetA();
    const auto result = mach->cpu.SWAP(a);
    mach->cpu.SetA(result);
    
    
    printf("SWAP A; -> A(%x), Result(%x) | ", a, result);
    mach->cpu.ShowFlags();
}








void srl_38(Machine* const) { ASSERT_INSTR_IMPL(); }
void srl_39(Machine* const) { ASSERT_INSTR_IMPL(); }
void srl_3A(Machine* const) { ASSERT_INSTR_IMPL(); }
void srl_3B(Machine* const) { ASSERT_INSTR_IMPL(); }
void srl_3C(Machine* const) { ASSERT_INSTR_IMPL(); }
void srl_3D(Machine* const) { ASSERT_INSTR_IMPL(); }
void srl_3E(Machine* const) { ASSERT_INSTR_IMPL(); }
void srl_3F(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x04
void bit_40(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_41(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_42(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_43(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_44(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_45(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_46(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_47(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_48(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_49(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_4A(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_4B(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_4C(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_4D(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_4E(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_4F(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x05
void bit_50(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_51(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_52(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_53(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_54(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_55(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_56(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_57(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_58(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_59(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_5A(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_5B(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_5C(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_5D(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_5E(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_5F(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x06
void bit_60(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_61(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_62(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_63(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_64(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_65(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_66(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_67(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_68(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_69(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_6A(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_6B(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_6C(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_6D(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_6E(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_6F(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x07
void bit_70(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_71(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_72(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_73(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_74(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_75(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_76(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_77(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_78(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_79(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_7A(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_7B(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_7C(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_7D(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_7E(Machine* const) { ASSERT_INSTR_IMPL(); }
void bit_7F(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x08
void res_80(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_81(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_82(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_83(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_84(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_85(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_86(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_87(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_88(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_89(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_8A(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_8B(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_8C(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_8D(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_8E(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_8F(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x09
void res_90(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_91(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_92(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_93(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_94(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_95(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_96(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_97(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_98(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_99(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_9A(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_9B(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_9C(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_9D(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_9E(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_9F(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x0A
void res_A0(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_A1(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_A2(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_A3(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_A4(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_A5(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_A6(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_A7(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_A8(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_A9(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_AA(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_AB(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_AC(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_AD(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_AE(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_AF(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x0B
void res_B0(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_B1(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_B2(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_B3(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_B4(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_B5(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_B6(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_B7(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_B8(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_B9(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_BA(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_BB(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_BC(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_BD(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_BE(Machine* const) { ASSERT_INSTR_IMPL(); }
void res_BF(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x0C
void set_C0(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_C1(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_C2(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_C3(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_C4(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_C5(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_C6(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_C7(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_C8(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_C9(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_CA(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_CB(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_CC(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_CD(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_CE(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_CF(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x0D
void set_D0(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_D1(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_D2(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_D3(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_D4(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_D5(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_D6(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_D7(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_D8(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_D9(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_DA(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_DB(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_DC(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_DD(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_DE(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_DF(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x0E
void set_E0(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_E1(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_E2(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_E3(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_E4(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_E5(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_E6(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_E7(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_E8(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_E9(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_EA(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_EB(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_EC(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_ED(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_EE(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_EF(Machine* const) { ASSERT_INSTR_IMPL(); }
// 0x0F
void set_F0(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_F1(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_F2(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_F3(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_F4(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_F5(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_F6(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_F7(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_F8(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_F9(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_FA(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_FB(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_FC(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_FD(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_FE(Machine* const) { ASSERT_INSTR_IMPL(); }
void set_FF(Machine* const) { ASSERT_INSTR_IMPL(); }























}