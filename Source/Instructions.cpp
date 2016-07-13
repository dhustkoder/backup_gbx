#include <iostream>
#include "Machine.h"
#include "Instructions.h"

namespace gbx {





InstructionFunction main_instructions[0x80] = 
{
/*          0      1      2       3       4       5      6        7      8       9      A       B       C       D      E        F  */
/* 0 */  nop_00, ld_01, ld_02, inc_03, inc_04, dec_05, ld_06, rlca_07, ld_08, add_09, ld_0A, dec_0B, inc_0C, dec_0D, ld_0E, rrca_0F,
/* 1 */ stop_10, ld_11, ld_12, inc_13, inc_14, dec_15, ld_16,  rla_17, jr_18, add_19, ld_1A, dec_1B, inc_1C, dec_1D, ld_1E, rra_1F,
/* 2 */   jr_20, ld_21, ld_22, inc_23, inc_24, dec_25, ld_26,  daa_27, jr_28, add_29, ld_2A, dec_2B, inc_2C, dec_2D, ld_2E, cpl_2F,
/* 3 */   jr_30, ld_31, ld_32, inc_33, inc_34, dec_35, ld_36,  scf_37, jr_38, add_39, ld_3A, dec_3B, inc_3C, dec_3D, ld_3E, ccf_3F,
/* 4 */   ld_40, ld_41, ld_42,  ld_43,  ld_44,  ld_45, ld_46,   ld_47, ld_48,  ld_49, ld_4A,  ld_4B , ld_4C,  ld_4D, ld_4E,  ld_4F,
/* 5 */   ld_50, ld_51, ld_52,  ld_53,  ld_54,  ld_55, ld_56,   ld_57, ld_58,  ld_59, ld_5A,  ld_5B , ld_5C,  ld_5D, ld_5E,  ld_5F,
/* 6 */   ld_60, ld_61, ld_62,  ld_63,  ld_64,  ld_65, ld_66,   ld_67, ld_68,  ld_69, ld_6A,  ld_6B , ld_6C,  ld_6D, ld_6E,  ld_6F,
/* 7 */   ld_70, ld_71, ld_72,  ld_73,  ld_74,  ld_75, halt_76, ld_77, ld_78,  ld_79, ld_7A,  ld_7B , ld_7C,  ld_7D, ld_7E,  ld_7F
};



// Main instructions implementation:

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
void jr_30(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 2; }
void ld_31(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 3; }
void ld_32(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void inc_33(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void inc_34(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void dec_35(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_36(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 2; }
void scf_37(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void jr_38(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 2; }
void add_39(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_3A(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void dec_3B(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void inc_3C(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void dec_3D(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_3E(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 2; }
void ccf_3F(Machine* mach){ std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
// 0x40
void ld_40(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_41(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_42(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_43(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_44(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_45(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_46(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_47(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_48(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_49(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_4A(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_4B(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_4C(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_4D(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_4E(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_4F(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
// 0x50
void ld_50(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_51(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_52(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_53(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_54(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_55(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_56(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_57(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_58(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_59(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_5A(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_5B(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_5C(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_5D(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_5E(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_5F(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
// 0x60
void ld_60(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_61(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_62(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_63(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_64(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_65(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_66(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_67(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_68(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_69(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_6A(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_6B(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_6C(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_6D(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_6E(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_6F(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
// 0x70
void ld_70(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_71(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_72(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_73(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_74(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_75(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void halt_76(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_77(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_78(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_79(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_7A(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_7B(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_7C(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_7D(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_7E(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }
void ld_7F(Machine* mach) { std::cout << __func__ << '\n'; mach->cpu.pc += 1; }



}
