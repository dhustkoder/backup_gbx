#ifndef GBX_INSTRUCTIONS_H_
#define GBX_INSTRUCTIONS_H_

namespace gbx {

class Machine;

using InstructionFunction = void(*)(Machine* const);
extern InstructionFunction main_instructions[0x100];

// Main Instructions:
extern void miss_instr(Machine* const);
// 0x00
extern void nop_00(Machine* const);
extern void ld_01(Machine* const);
extern void ld_02(Machine* const);
extern void inc_03(Machine* const);
extern void inc_04(Machine* const);
extern void dec_05(Machine* const);
extern void ld_06(Machine* const);
extern void rlca_07(Machine* const);
extern void ld_08(Machine* const);
extern void add_09(Machine* const);
extern void ld_0A(Machine* const);
extern void dec_0B(Machine* const);
extern void inc_0C(Machine* const);
extern void dec_0D(Machine* const);
extern void ld_0E(Machine* const);
extern void rrca_0F(Machine* const);
// 0x10
extern void stop_10(Machine* const);
extern void ld_11(Machine* const);
extern void ld_12(Machine* const);
extern void inc_13(Machine* const);
extern void inc_14(Machine* const);
extern void dec_15(Machine* const);
extern void ld_16(Machine* const);
extern void rla_17(Machine* const);
extern void jr_18(Machine* const);
extern void add_19(Machine* const);
extern void ld_1A(Machine* const);
extern void dec_1B(Machine* const);
extern void inc_1C(Machine* const);
extern void dec_1D(Machine* const);
extern void ld_1E(Machine* const);
extern void rra_1F(Machine* const);
// 0x20
extern void jr_20(Machine* const);
extern void ld_21(Machine* const);
extern void ld_22(Machine* const);
extern void inc_23(Machine* const);
extern void inc_24(Machine* const);
extern void dec_25(Machine* const);
extern void ld_26(Machine* const);
extern void daa_27(Machine* const);
extern void jr_28(Machine* const);
extern void add_29(Machine* const);
extern void ld_2A(Machine* const);
extern void dec_2B(Machine* const);
extern void inc_2C(Machine* const);
extern void dec_2D(Machine* const);
extern void ld_2E(Machine* const);
extern void cpl_2F(Machine* const);
// 0x30
extern void jr_30(Machine* const);
extern void ld_31(Machine* const);
extern void ld_32(Machine* const);
extern void inc_33(Machine* const);
extern void inc_34(Machine* const);
extern void dec_35(Machine* const);
extern void ld_36(Machine* const);
extern void scf_37(Machine* const);
extern void jr_38(Machine* const);
extern void add_39(Machine* const);
extern void ld_3A(Machine* const);
extern void dec_3B(Machine* const);
extern void inc_3C(Machine* const);
extern void dec_3D(Machine* const);
extern void ld_3E(Machine* const);
extern void ccf_3F(Machine* const);
// 0x40
extern void ld_40(Machine* const);
extern void ld_41(Machine* const);
extern void ld_42(Machine* const);
extern void ld_43(Machine* const);
extern void ld_44(Machine* const);
extern void ld_45(Machine* const);
extern void ld_46(Machine* const);
extern void ld_47(Machine* const);
extern void ld_48(Machine* const);
extern void ld_49(Machine* const);
extern void ld_4A(Machine* const);
extern void ld_4B(Machine* const);
extern void ld_4C(Machine* const);
extern void ld_4D(Machine* const);
extern void ld_4E(Machine* const);
extern void ld_4F(Machine* const);
// 0x50
extern void ld_50(Machine* const);
extern void ld_51(Machine* const);
extern void ld_52(Machine* const);
extern void ld_53(Machine* const);
extern void ld_54(Machine* const);
extern void ld_55(Machine* const);
extern void ld_56(Machine* const);
extern void ld_57(Machine* const);
extern void ld_58(Machine* const);
extern void ld_59(Machine* const);
extern void ld_5A(Machine* const);
extern void ld_5B(Machine* const);
extern void ld_5C(Machine* const);
extern void ld_5D(Machine* const);
extern void ld_5E(Machine* const);
extern void ld_5F(Machine* const);
// 0x60
extern void ld_60(Machine* const);
extern void ld_61(Machine* const);
extern void ld_62(Machine* const);
extern void ld_63(Machine* const);
extern void ld_64(Machine* const);
extern void ld_65(Machine* const);
extern void ld_66(Machine* const);
extern void ld_67(Machine* const);
extern void ld_68(Machine* const);
extern void ld_69(Machine* const);
extern void ld_6A(Machine* const);
extern void ld_6B(Machine* const);
extern void ld_6C(Machine* const);
extern void ld_6D(Machine* const);
extern void ld_6E(Machine* const);
extern void ld_6F(Machine* const);
// 0x70
extern void ld_70(Machine* const);
extern void ld_71(Machine* const);
extern void ld_72(Machine* const);
extern void ld_73(Machine* const);
extern void ld_74(Machine* const);
extern void ld_75(Machine* const);
extern void halt_76(Machine* const);
extern void ld_77(Machine* const);
extern void ld_78(Machine* const);
extern void ld_79(Machine* const);
extern void ld_7A(Machine* const);
extern void ld_7B(Machine* const);
extern void ld_7C(Machine* const);
extern void ld_7D(Machine* const);
extern void ld_7E(Machine* const);
extern void ld_7F(Machine* const);
// 0x80
extern void add_80(Machine* const);
extern void add_81(Machine* const);
extern void add_82(Machine* const);
extern void add_83(Machine* const);
extern void add_84(Machine* const);
extern void add_85(Machine* const);
extern void add_86(Machine* const);
extern void add_87(Machine* const);
extern void adc_88(Machine* const);
extern void adc_89(Machine* const);
extern void adc_8A(Machine* const);
extern void adc_8B(Machine* const);
extern void adc_8C(Machine* const);
extern void adc_8D(Machine* const);
extern void adc_8E(Machine* const);
extern void adc_8F(Machine* const);
// 0x90
extern void sub_90(Machine* const);
extern void sub_91(Machine* const);
extern void sub_92(Machine* const);
extern void sub_93(Machine* const);
extern void sub_94(Machine* const);
extern void sub_95(Machine* const);
extern void sub_96(Machine* const);
extern void sub_97(Machine* const);
extern void sbc_98(Machine* const);
extern void sbc_99(Machine* const);
extern void sbc_9A(Machine* const);
extern void sbc_9B(Machine* const);
extern void sbc_9C(Machine* const);
extern void sbc_9D(Machine* const);
extern void sbc_9E(Machine* const);
extern void sbc_9F(Machine* const);
// 0xA0
extern void and_A0(Machine* const);
extern void and_A1(Machine* const);
extern void and_A2(Machine* const);
extern void and_A3(Machine* const);
extern void and_A4(Machine* const);
extern void and_A5(Machine* const);
extern void and_A6(Machine* const);
extern void and_A7(Machine* const);
extern void xor_A8(Machine* const);
extern void xor_A9(Machine* const);
extern void xor_AA(Machine* const);
extern void xor_AB(Machine* const);
extern void xor_AC(Machine* const);
extern void xor_AD(Machine* const);
extern void xor_AE(Machine* const);
extern void xor_AF(Machine* const);
// 0xB0
extern void or_B0(Machine* const);
extern void or_B1(Machine* const);
extern void or_B2(Machine* const);
extern void or_B3(Machine* const);
extern void or_B4(Machine* const);
extern void or_B5(Machine* const);
extern void or_B6(Machine* const);
extern void or_B7(Machine* const);
extern void cp_B8(Machine* const);
extern void cp_B9(Machine* const);
extern void cp_BA(Machine* const);
extern void cp_BB(Machine* const);
extern void cp_BC(Machine* const);
extern void cp_BD(Machine* const);
extern void cp_BE(Machine* const);
extern void cp_BF(Machine* const);
// 0xC0
extern void ret_C0(Machine* const);
extern void pop_C1(Machine* const);
extern void jp_C2(Machine* const);
extern void jp_C3(Machine* const);
extern void call_C4(Machine* const);
extern void push_C5(Machine* const);
extern void add_C6(Machine* const);
extern void rst_C7(Machine* const);
extern void ret_C8(Machine* const);
extern void ret_C9(Machine* const);
extern void jp_CA(Machine* const);
extern void PREFIX_CB(Machine* const);
extern void call_CC(Machine* const);
extern void call_CD(Machine* const);
extern void adc_CE(Machine* const);
extern void rst_CF(Machine* const);

// 0xD0
extern void ret_D0(Machine* const);
extern void pop_D1(Machine* const);
extern void jp_D2(Machine* const);
// MISSING ----
extern void call_D4(Machine* const);
extern void push_D5(Machine* const);
extern void sub_D6(Machine* const);
extern void rst_D7(Machine* const);
extern void ret_D8(Machine* const);
extern void reti_D9(Machine* const);
extern void jp_DA(Machine* const);
// MISSING -----
extern void call_DC(Machine* const);
// MISSING -----
extern void sbc_DE(Machine* const);
extern void rst_DF(Machine* const);

// 0xE0
extern void ldh_E0(Machine* const);
extern void pop_E1(Machine* const);
extern void ld_E2(Machine* const);
// MISSING ----
// MISSING ----
extern void push_E5(Machine* const);
extern void and_E6(Machine* const);
extern void rst_E7(Machine* const);
extern void add_E8(Machine* const);
extern void jp_E9(Machine* const);
extern void ld_EA(Machine* const);
// MISSING -----
// MISSING -----
// MISSING -----
extern void xor_EE(Machine* const);
extern void rst_EF(Machine* const);

// 0XF0
extern void ldh_F0(Machine* const);
extern void pop_F1(Machine* const);
extern void ld_F2(Machine* const);
extern void di_F3(Machine* const);
// MISSING ----
extern void push_F5(Machine* const);
extern void or_F6(Machine* const);
extern void rst_F7(Machine* const);
extern void ld_F8(Machine* const);
extern void ld_F9(Machine* const);
extern void ld_FA(Machine* const);
extern void ei_FB(Machine* const);
// MISSING -----
// MISSING -----
extern void cp_FE(Machine* const);
extern void rst_FF(Machine* const);





















}

#endif
