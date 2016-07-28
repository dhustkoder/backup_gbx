#ifndef GBX_CBINSTRUCTIONS_H_
#define GBX_CBINSTRUCTIONS_H_

#ifdef _DEBUG
#include <Utix/Assert.h>
#define ASSERT_INSTR_IMPL() puts(__func__); ASSERT_MSG(false, "Instruction Not Implemented!")
#else
#define ASSERT_INSTR_IMPL() puts(__func__);
#endif
namespace gbx {

class Cpu;
using CBInstrFunc = void(* const)(Cpu* const);
extern const CBInstrFunc cb_instructions[0x100];




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