#include <iostream>
#include "Machine.h"
#include "Instructions.h"

namespace gbx {





InstructionFunction main_instructions[0x40] = 
{
/*         0      1      2       3       4       5      6        7      8       9      A       B       C       D      E        F  */
/* 0 */ nop_00, ld_01, ld_02, inc_03, inc_04, dec_05, ld_06, rlca_07, ld_08, add_09, ld_0A, dec_0B, inc_0C, dec_0D, ld_0E, rrca_0F,
/* 1 */ stop_10, ld_11, ld_12, inc_13, inc_14, dec_15, ld_16, rla_17, jr_18, add_19, ld_1A, dec_1B, inc_1C, dec_1D, ld_1E, rra_1F,
/* 2 */  jr_20, ld_21, ld_22, inc_23, inc_24, dec_25, ld_26, daa_27, jr_28, add_29, ld_2A, dec_2B, inc_2C, dec_2D, ld_2E, cpl_2F,
/* 3 */  jr_30, ld_31, ld_32, inc_33, inc_34, dec_35, ld_36, scf_37, jr_38, add_39, ld_3A, dec_3B, inc_3C, dec_3D, ld_3E, ccf_3F
};





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






}
