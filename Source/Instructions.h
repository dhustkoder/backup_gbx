#ifndef GBX_INSTRUCTIONS_H_
#define GBX_INSTRUCTIONS_H_
#include <stdio.h>

#ifdef _DEBUG
#include <Utix/Assert.h>
#define ASSERT_INSTR_IMPL() puts(__func__); ASSERT_MSG(false, "Instruction Not Implemented!")
#else
#define ASSERT_INSTR_IMPL() puts(__func__);
#endif

namespace gbx {

class Cpu;
class Machine;

using MainInstrFunc = void(*const)(Machine* const);
using CBInstrFunc = void(*const)(Cpu* const);

extern const MainInstrFunc main_instructions[0x100];
extern const CBInstrFunc cb_instructions[0x100];



// note: instructions are named after their mnemonic, and opcode value
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















// CB Instructions:
// 0x00
extern void rlc_00(Cpu* const);
extern void rlc_01(Cpu* const);
extern void rlc_02(Cpu* const);
extern void rlc_03(Cpu* const);
extern void rlc_04(Cpu* const);
extern void rlc_05(Cpu* const);
extern void rlc_06(Cpu* const);
extern void rlc_07(Cpu* const);
extern void rrc_08(Cpu* const);
extern void rrc_09(Cpu* const);
extern void rrc_0A(Cpu* const);
extern void rrc_0B(Cpu* const);
extern void rrc_0C(Cpu* const);
extern void rrc_0D(Cpu* const);
extern void rrc_0E(Cpu* const);
extern void rrc_0F(Cpu* const);
// 0x10
extern void rl_10(Cpu* const);
extern void rl_11(Cpu* const);
extern void rl_12(Cpu* const);
extern void rl_13(Cpu* const);
extern void rl_14(Cpu* const);
extern void rl_15(Cpu* const);
extern void rl_16(Cpu* const);
extern void rl_17(Cpu* const);
extern void rr_18(Cpu* const);
extern void rr_19(Cpu* const);
extern void rr_1A(Cpu* const);
extern void rr_1B(Cpu* const);
extern void rr_1C(Cpu* const);
extern void rr_1D(Cpu* const);
extern void rr_1E(Cpu* const);
extern void rr_1F(Cpu* const);
// 0x20
extern void sla_20(Cpu* const);
extern void sla_21(Cpu* const);
extern void sla_22(Cpu* const);
extern void sla_23(Cpu* const);
extern void sla_24(Cpu* const);
extern void sla_25(Cpu* const);
extern void sla_26(Cpu* const);
extern void sla_27(Cpu* const);
extern void sra_28(Cpu* const);
extern void sra_29(Cpu* const);
extern void sra_2A(Cpu* const);
extern void sra_2B(Cpu* const);
extern void sra_2C(Cpu* const);
extern void sra_2D(Cpu* const);
extern void sra_2E(Cpu* const);
extern void sra_2F(Cpu* const);
// 0x30
extern void swap_30(Cpu* const);
extern void swap_31(Cpu* const);
extern void swap_32(Cpu* const);
extern void swap_33(Cpu* const);
extern void swap_34(Cpu* const);
extern void swap_35(Cpu* const);
extern void swap_36(Cpu* const);
extern void swap_37(Cpu* const);
extern void srl_38(Cpu* const);
extern void srl_39(Cpu* const);
extern void srl_3A(Cpu* const);
extern void srl_3B(Cpu* const);
extern void srl_3C(Cpu* const);
extern void srl_3D(Cpu* const);
extern void srl_3E(Cpu* const);
extern void srl_3F(Cpu* const);
// 0x40
extern void bit_40(Cpu* const);
extern void bit_41(Cpu* const);
extern void bit_42(Cpu* const);
extern void bit_43(Cpu* const);
extern void bit_44(Cpu* const);
extern void bit_45(Cpu* const);
extern void bit_46(Cpu* const);
extern void bit_47(Cpu* const);
extern void bit_48(Cpu* const);
extern void bit_49(Cpu* const);
extern void bit_4A(Cpu* const);
extern void bit_4B(Cpu* const);
extern void bit_4C(Cpu* const);
extern void bit_4D(Cpu* const);
extern void bit_4E(Cpu* const);
extern void bit_4F(Cpu* const);
// 0x50
extern void bit_50(Cpu* const);
extern void bit_51(Cpu* const);
extern void bit_52(Cpu* const);
extern void bit_53(Cpu* const);
extern void bit_54(Cpu* const);
extern void bit_55(Cpu* const);
extern void bit_56(Cpu* const);
extern void bit_57(Cpu* const);
extern void bit_58(Cpu* const);
extern void bit_59(Cpu* const);
extern void bit_5A(Cpu* const);
extern void bit_5B(Cpu* const);
extern void bit_5C(Cpu* const);
extern void bit_5D(Cpu* const);
extern void bit_5E(Cpu* const);
extern void bit_5F(Cpu* const);
// 0x60
extern void bit_60(Cpu* const);
extern void bit_61(Cpu* const);
extern void bit_62(Cpu* const);
extern void bit_63(Cpu* const);
extern void bit_64(Cpu* const);
extern void bit_65(Cpu* const);
extern void bit_66(Cpu* const);
extern void bit_67(Cpu* const);
extern void bit_68(Cpu* const);
extern void bit_69(Cpu* const);
extern void bit_6A(Cpu* const);
extern void bit_6B(Cpu* const);
extern void bit_6C(Cpu* const);
extern void bit_6D(Cpu* const);
extern void bit_6E(Cpu* const);
extern void bit_6F(Cpu* const);
// 0x70
extern void bit_70(Cpu* const);
extern void bit_71(Cpu* const);
extern void bit_72(Cpu* const);
extern void bit_73(Cpu* const);
extern void bit_74(Cpu* const);
extern void bit_75(Cpu* const);
extern void bit_76(Cpu* const);
extern void bit_77(Cpu* const);
extern void bit_78(Cpu* const);
extern void bit_79(Cpu* const);
extern void bit_7A(Cpu* const);
extern void bit_7B(Cpu* const);
extern void bit_7C(Cpu* const);
extern void bit_7D(Cpu* const);
extern void bit_7E(Cpu* const);
extern void bit_7F(Cpu* const);
// 0x80
extern void res_80(Cpu* const);
extern void res_81(Cpu* const);
extern void res_82(Cpu* const);
extern void res_83(Cpu* const);
extern void res_84(Cpu* const);
extern void res_85(Cpu* const);
extern void res_86(Cpu* const);
extern void res_87(Cpu* const);
extern void res_88(Cpu* const);
extern void res_89(Cpu* const);
extern void res_8A(Cpu* const);
extern void res_8B(Cpu* const);
extern void res_8C(Cpu* const);
extern void res_8D(Cpu* const);
extern void res_8E(Cpu* const);
extern void res_8F(Cpu* const);
// 0x90
extern void res_90(Cpu* const);
extern void res_91(Cpu* const);
extern void res_92(Cpu* const);
extern void res_93(Cpu* const);
extern void res_94(Cpu* const);
extern void res_95(Cpu* const);
extern void res_96(Cpu* const);
extern void res_97(Cpu* const);
extern void res_98(Cpu* const);
extern void res_99(Cpu* const);
extern void res_9A(Cpu* const);
extern void res_9B(Cpu* const);
extern void res_9C(Cpu* const);
extern void res_9D(Cpu* const);
extern void res_9E(Cpu* const);
extern void res_9F(Cpu* const);
// 0xA0
extern void res_A0(Cpu* const);
extern void res_A1(Cpu* const);
extern void res_A2(Cpu* const);
extern void res_A3(Cpu* const);
extern void res_A4(Cpu* const);
extern void res_A5(Cpu* const);
extern void res_A6(Cpu* const);
extern void res_A7(Cpu* const);
extern void res_A8(Cpu* const);
extern void res_A9(Cpu* const);
extern void res_AA(Cpu* const);
extern void res_AB(Cpu* const);
extern void res_AC(Cpu* const);
extern void res_AD(Cpu* const);
extern void res_AE(Cpu* const);
extern void res_AF(Cpu* const);
// 0xB0
extern void res_B0(Cpu* const);
extern void res_B1(Cpu* const);
extern void res_B2(Cpu* const);
extern void res_B3(Cpu* const);
extern void res_B4(Cpu* const);
extern void res_B5(Cpu* const);
extern void res_B6(Cpu* const);
extern void res_B7(Cpu* const);
extern void res_B8(Cpu* const);
extern void res_B9(Cpu* const);
extern void res_BA(Cpu* const);
extern void res_BB(Cpu* const);
extern void res_BC(Cpu* const);
extern void res_BD(Cpu* const);
extern void res_BE(Cpu* const);
extern void res_BF(Cpu* const);
// 0xC0
extern void set_C0(Cpu* const);
extern void set_C1(Cpu* const);
extern void set_C2(Cpu* const);
extern void set_C3(Cpu* const);
extern void set_C4(Cpu* const);
extern void set_C5(Cpu* const);
extern void set_C6(Cpu* const);
extern void set_C7(Cpu* const);
extern void set_C8(Cpu* const);
extern void set_C9(Cpu* const);
extern void set_CA(Cpu* const);
extern void set_CB(Cpu* const);
extern void set_CC(Cpu* const);
extern void set_CD(Cpu* const);
extern void set_CE(Cpu* const);
extern void set_CF(Cpu* const);
// 0xD0
extern void set_D0(Cpu* const);
extern void set_D1(Cpu* const);
extern void set_D2(Cpu* const);
extern void set_D3(Cpu* const);
extern void set_D4(Cpu* const);
extern void set_D5(Cpu* const);
extern void set_D6(Cpu* const);
extern void set_D7(Cpu* const);
extern void set_D8(Cpu* const);
extern void set_D9(Cpu* const);
extern void set_DA(Cpu* const);
extern void set_DB(Cpu* const);
extern void set_DC(Cpu* const);
extern void set_DD(Cpu* const);
extern void set_DE(Cpu* const);
extern void set_DF(Cpu* const);
// 0xE0
extern void set_E0(Cpu* const);
extern void set_E1(Cpu* const);
extern void set_E2(Cpu* const);
extern void set_E3(Cpu* const);
extern void set_E4(Cpu* const);
extern void set_E5(Cpu* const);
extern void set_E6(Cpu* const);
extern void set_E7(Cpu* const);
extern void set_E8(Cpu* const);
extern void set_E9(Cpu* const);
extern void set_EA(Cpu* const);
extern void set_EB(Cpu* const);
extern void set_EC(Cpu* const);
extern void set_ED(Cpu* const);
extern void set_EE(Cpu* const);
extern void set_EF(Cpu* const);
// 0xF0
extern void set_F0(Cpu* const);
extern void set_F1(Cpu* const);
extern void set_F2(Cpu* const);
extern void set_F3(Cpu* const);
extern void set_F4(Cpu* const);
extern void set_F5(Cpu* const);
extern void set_F6(Cpu* const);
extern void set_F7(Cpu* const);
extern void set_F8(Cpu* const);
extern void set_F9(Cpu* const);
extern void set_FA(Cpu* const);
extern void set_FB(Cpu* const);
extern void set_FC(Cpu* const);
extern void set_FD(Cpu* const);
extern void set_FE(Cpu* const);
extern void set_FF(Cpu* const);









}

#endif
