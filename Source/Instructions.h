#ifndef GBX_INSTRUCTIONS_H_
#define GBX_INSTRUCTIONS_H_

namespace gbx {

struct Machine;

using InstructionFunction = void(*)(Machine*);
extern InstructionFunction main_instructions[0x100];

// Main Instructions:
extern void miss_instr(Machine*);
// 0x00
extern void nop_00(Machine*);
extern void ld_01(Machine*);
extern void ld_02(Machine*);
extern void inc_03(Machine*);
extern void inc_04(Machine*);
extern void dec_05(Machine*);
extern void ld_06(Machine*);
extern void rlca_07(Machine*);
extern void ld_08(Machine*);
extern void add_09(Machine*);
extern void ld_0A(Machine*);
extern void dec_0B(Machine*);
extern void inc_0C(Machine*);
extern void dec_0D(Machine*);
extern void ld_0E(Machine*);
extern void rrca_0F(Machine*);
// 0x10
extern void stop_10(Machine*);
extern void ld_11(Machine*);
extern void ld_12(Machine*);
extern void inc_13(Machine*);
extern void inc_14(Machine*);
extern void dec_15(Machine*);
extern void ld_16(Machine*);
extern void rla_17(Machine*);
extern void jr_18(Machine*);
extern void add_19(Machine*);
extern void ld_1A(Machine*);
extern void dec_1B(Machine*);
extern void inc_1C(Machine*);
extern void dec_1D(Machine*);
extern void ld_1E(Machine*);
extern void rra_1F(Machine*);
// 0x20
extern void jr_20(Machine*);
extern void ld_21(Machine*);
extern void ld_22(Machine*);
extern void inc_23(Machine*);
extern void inc_24(Machine*);
extern void dec_25(Machine*);
extern void ld_26(Machine*);
extern void daa_27(Machine*);
extern void jr_28(Machine*);
extern void add_29(Machine*);
extern void ld_2A(Machine*);
extern void dec_2B(Machine*);
extern void inc_2C(Machine*);
extern void dec_2D(Machine*);
extern void ld_2E(Machine*);
extern void cpl_2F(Machine*);
// 0x30
extern void jr_30(Machine*);
extern void ld_31(Machine*);
extern void ld_32(Machine*);
extern void inc_33(Machine*);
extern void inc_34(Machine*);
extern void dec_35(Machine*);
extern void ld_36(Machine*);
extern void scf_37(Machine*);
extern void jr_38(Machine*);
extern void add_39(Machine*);
extern void ld_3A(Machine*);
extern void dec_3B(Machine*);
extern void inc_3C(Machine*);
extern void dec_3D(Machine*);
extern void ld_3E(Machine*);
extern void ccf_3F(Machine*);
// 0x40
extern void ld_40(Machine*);
extern void ld_41(Machine*);
extern void ld_42(Machine*);
extern void ld_43(Machine*);
extern void ld_44(Machine*);
extern void ld_45(Machine*);
extern void ld_46(Machine*);
extern void ld_47(Machine*);
extern void ld_48(Machine*);
extern void ld_49(Machine*);
extern void ld_4A(Machine*);
extern void ld_4B(Machine*);
extern void ld_4C(Machine*);
extern void ld_4D(Machine*);
extern void ld_4E(Machine*);
extern void ld_4F(Machine*);
// 0x50
extern void ld_50(Machine*);
extern void ld_51(Machine*);
extern void ld_52(Machine*);
extern void ld_53(Machine*);
extern void ld_54(Machine*);
extern void ld_55(Machine*);
extern void ld_56(Machine*);
extern void ld_57(Machine*);
extern void ld_58(Machine*);
extern void ld_59(Machine*);
extern void ld_5A(Machine*);
extern void ld_5B(Machine*);
extern void ld_5C(Machine*);
extern void ld_5D(Machine*);
extern void ld_5E(Machine*);
extern void ld_5F(Machine*);
// 0x60
extern void ld_60(Machine*);
extern void ld_61(Machine*);
extern void ld_62(Machine*);
extern void ld_63(Machine*);
extern void ld_64(Machine*);
extern void ld_65(Machine*);
extern void ld_66(Machine*);
extern void ld_67(Machine*);
extern void ld_68(Machine*);
extern void ld_69(Machine*);
extern void ld_6A(Machine*);
extern void ld_6B(Machine*);
extern void ld_6C(Machine*);
extern void ld_6D(Machine*);
extern void ld_6E(Machine*);
extern void ld_6F(Machine*);
// 0x70
extern void ld_70(Machine*);
extern void ld_71(Machine*);
extern void ld_72(Machine*);
extern void ld_73(Machine*);
extern void ld_74(Machine*);
extern void ld_75(Machine*);
extern void halt_76(Machine*);
extern void ld_77(Machine*);
extern void ld_78(Machine*);
extern void ld_79(Machine*);
extern void ld_7A(Machine*);
extern void ld_7B(Machine*);
extern void ld_7C(Machine*);
extern void ld_7D(Machine*);
extern void ld_7E(Machine*);
extern void ld_7F(Machine*);
// 0x80
extern void add_80(Machine*);
extern void add_81(Machine*);
extern void add_82(Machine*);
extern void add_83(Machine*);
extern void add_84(Machine*);
extern void add_85(Machine*);
extern void add_86(Machine*);
extern void add_87(Machine*);
extern void adc_88(Machine*);
extern void adc_89(Machine*);
extern void adc_8A(Machine*);
extern void adc_8B(Machine*);
extern void adc_8C(Machine*);
extern void adc_8D(Machine*);
extern void adc_8E(Machine*);
extern void adc_8F(Machine*);
// 0x90
extern void sub_90(Machine*);
extern void sub_91(Machine*);
extern void sub_92(Machine*);
extern void sub_93(Machine*);
extern void sub_94(Machine*);
extern void sub_95(Machine*);
extern void sub_96(Machine*);
extern void sub_97(Machine*);
extern void sbc_98(Machine*);
extern void sbc_99(Machine*);
extern void sbc_9A(Machine*);
extern void sbc_9B(Machine*);
extern void sbc_9C(Machine*);
extern void sbc_9D(Machine*);
extern void sbc_9E(Machine*);
extern void sbc_9F(Machine*);
// 0xA0
extern void and_A0(Machine*);
extern void and_A1(Machine*);
extern void and_A2(Machine*);
extern void and_A3(Machine*);
extern void and_A4(Machine*);
extern void and_A5(Machine*);
extern void and_A6(Machine*);
extern void and_A7(Machine*);
extern void xor_A8(Machine*);
extern void xor_A9(Machine*);
extern void xor_AA(Machine*);
extern void xor_AB(Machine*);
extern void xor_AC(Machine*);
extern void xor_AD(Machine*);
extern void xor_AE(Machine*);
extern void xor_AF(Machine*);
// 0xB0
extern void or_B0(Machine*);
extern void or_B1(Machine*);
extern void or_B2(Machine*);
extern void or_B3(Machine*);
extern void or_B4(Machine*);
extern void or_B5(Machine*);
extern void or_B6(Machine*);
extern void or_B7(Machine*);
extern void cp_B8(Machine*);
extern void cp_B9(Machine*);
extern void cp_BA(Machine*);
extern void cp_BB(Machine*);
extern void cp_BC(Machine*);
extern void cp_BD(Machine*);
extern void cp_BE(Machine*);
extern void cp_BF(Machine*);
// 0xC0
extern void ret_C0(Machine*);
extern void pop_C1(Machine*);
extern void jp_C2(Machine*);
extern void jp_C3(Machine*);
extern void call_C4(Machine*);
extern void push_C5(Machine*);
extern void add_C6(Machine*);
extern void rst_C7(Machine*);
extern void ret_C8(Machine*);
extern void ret_C9(Machine*);
extern void jp_CA(Machine*);
extern void PREFIX_CB(Machine*);
extern void call_CC(Machine*);
extern void call_CD(Machine*);
extern void adc_CE(Machine*);
extern void rst_CF(Machine*);

// 0xD0
extern void ret_D0(Machine*);
extern void pop_D1(Machine*);
extern void jp_D2(Machine*);
// MISSING ----
extern void call_D4(Machine*);
extern void push_D5(Machine*);
extern void sub_D6(Machine*);
extern void rst_D7(Machine*);
extern void ret_D8(Machine*);
extern void reti_D9(Machine*);
extern void jp_DA(Machine*);
// MISSING -----
extern void call_DC(Machine*);
// MISSING -----
extern void sbc_DE(Machine*);
extern void rst_DF(Machine*);

// 0xE0
extern void ldh_E0(Machine*);
extern void pop_E1(Machine*);
extern void ld_E2(Machine*);
// MISSING ----
// MISSING ----
extern void push_E5(Machine*);
extern void and_E6(Machine*);
extern void rst_E7(Machine*);
extern void add_E8(Machine*);
extern void jp_E9(Machine*);
extern void ld_EA(Machine*);
// MISSING -----
// MISSING -----
// MISSING -----
extern void xor_EE(Machine*);
extern void rst_EF(Machine*);

// 0XF0
extern void ldh_F0(Machine*);
extern void pop_F1(Machine*);
extern void ld_F2(Machine*);
extern void di_F3(Machine*);
// MISSING ----
extern void push_F5(Machine*);
extern void or_F6(Machine*);
extern void rst_F7(Machine*);
extern void ld_F8(Machine*);
extern void ld_F9(Machine*);
extern void ld_FA(Machine*);
extern void ei_FB(Machine*);
// MISSING -----
// MISSING -----
extern void cp_FE(Machine*);
extern void rst_FF(Machine*);





















}

#endif