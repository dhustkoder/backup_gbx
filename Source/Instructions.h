#ifndef GBX_INSTRUCTIONS_H_
#define GBX_INSTRUCTIONS_H_

namespace gbx {

struct Machine;

using InstructionFunction = void(*)(Machine*);
extern InstructionFunction main_instructions[0x30];

// Main Instructions:
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





























}

#endif