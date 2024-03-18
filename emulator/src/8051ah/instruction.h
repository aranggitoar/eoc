/* 8051AH (MCS-51) assembly instruction set and helper functions, grouped
   by their functionality and not arranged by their opcodes. */
#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#include <8051ah/memory.h>
#include <8051ah/cpu.h>

/** ABBREVIATIONS **/
/* id: immediate data
   db: direct byte
   dbi: direct bit
   ir: indirect ram
   eir: indirect external ram
   r: register
   a: accumulator
   co: complement
   c: carry
   dptr: data pointer
   edptr: dptr to external ram */

/*************/
/*  OPCODES  */
/*************/

// bit addr, data addr, code addr in the reference are location addresses
// of the bit/byte or 11-bit/16-bit destination addresses
typedef enum iopcode_t {
  OP_NOP                      = 0x00,
  OP_AJMP                     = 0x01,
  OP_LJMP                     = 0x02,
  OP_RR                       = 0x03,
  OP_INC_a                    = 0x04,
  OP_INC_db                   = 0x05,
  OP_INC_ir0                  = 0x06,
  OP_INC_ir1                  = 0x07,
  OP_INC_r0                   = 0x08,
  OP_INC_r1                   = 0x09,
  OP_INC_r2                   = 0x0A,
  OP_INC_r3                   = 0x0B,
  OP_INC_r4                   = 0x0C,
  OP_INC_r5                   = 0x0D,
  OP_INC_r6                   = 0x0E,
  OP_INC_r7                   = 0x0F,
  OP_JBC                      = 0x10,
  OP_ACALL                    = 0x11,
  OP_LCALL                    = 0x12,
  OP_RRC                      = 0x13,
  OP_DEC_a                    = 0x14,
  OP_DEC_db                   = 0x15,
  OP_DEC_ir0                  = 0x16,
  OP_DEC_ir1                  = 0x17,
  OP_DEC_r0                   = 0x18,
  OP_DEC_r1                   = 0x19,
  OP_DEC_r2                   = 0x1A,
  OP_DEC_r3                   = 0x1B,
  OP_DEC_r4                   = 0x1C,
  OP_DEC_r5                   = 0x1D,
  OP_DEC_r6                   = 0x1E,
  OP_DEC_r7                   = 0x1F,
  OP_JB                       = 0x20,
  OP_AJMP_1                   = 0x21, // exact duplicate of 0x01
  OP_RET                      = 0x22,
  OP_RL                       = 0x23,
  OP_ADD_id                   = 0x24,
  OP_ADD_db                   = 0x25,
  OP_ADD_ir0                  = 0x26,
  OP_ADD_ir1                  = 0x27,
  OP_ADD_r0                   = 0x28,
  OP_ADD_r1                   = 0x29,
  OP_ADD_r2                   = 0x2A,
  OP_ADD_r3                   = 0x2B,
  OP_ADD_r4                   = 0x2C,
  OP_ADD_r5                   = 0x2D,
  OP_ADD_r6                   = 0x2E,
  OP_ADD_r7                   = 0x2F,
  OP_JNB                      = 0x30,
  OP_ACALL_1                  = 0x31, // exact duplicate of 0x11
  OP_RETI                     = 0x32,
  OP_RLC                      = 0x33,
  OP_ADDC_id                  = 0x34,
  OP_ADDC_db                  = 0x35,
  OP_ADDC_ir0                 = 0x36,
  OP_ADDC_ir1                 = 0x37,
  OP_ADDC_r0                  = 0x38,
  OP_ADDC_r1                  = 0x39,
  OP_ADDC_r2                  = 0x3A,
  OP_ADDC_r3                  = 0x3B,
  OP_ADDC_r4                  = 0x3C,
  OP_ADDC_r5                  = 0x3D,
  OP_ADDC_r6                  = 0x3E,
  OP_ADDC_r7                  = 0x3F,
  OP_JC                       = 0x40,
  OP_AJMP_2                   = 0x41, // exact duplicate of 0x01
  OP_ORL_a_to_db              = 0x42,
  OP_ORL_id_to_db             = 0x43,
  OP_ORL_id_to_a              = 0x44,
  OP_ORL_db_to_a              = 0x45,
  OP_ORL_ir0_to_a             = 0x46,
  OP_ORL_ir1_to_a             = 0x47,
  OP_ORL_r0_to_a              = 0x48,
  OP_ORL_r1_to_a              = 0x49,
  OP_ORL_r2_to_a              = 0x4A,
  OP_ORL_r3_to_a              = 0x4B,
  OP_ORL_r4_to_a              = 0x4C,
  OP_ORL_r5_to_a              = 0x4D,
  OP_ORL_r6_to_a              = 0x4E,
  OP_ORL_r7_to_a              = 0x4F,
  OP_JNC                      = 0x50,
  OP_ACALL_2                  = 0x51, // exact duplicate of 0x11
  OP_ANL_a_to_db              = 0x52,
  OP_ANL_id_to_db             = 0x53,
  OP_ANL_id_to_a              = 0x54,
  OP_ANL_db_to_a              = 0x55,
  OP_ANL_ir0_to_a             = 0x56,
  OP_ANL_ir1_to_a             = 0x57,
  OP_ANL_r0_to_a              = 0x58,
  OP_ANL_r1_to_a              = 0x59,
  OP_ANL_r2_to_a              = 0x5A,
  OP_ANL_r3_to_a              = 0x5B,
  OP_ANL_r4_to_a              = 0x5C,
  OP_ANL_r5_to_a              = 0x5D,
  OP_ANL_r6_to_a              = 0x5E,
  OP_ANL_r7_to_a              = 0x5F,
  OP_JZ                       = 0x60,
  OP_AJMP_3                   = 0x61, // exact duplicate of 0x01
  OP_XRL_a_to_db              = 0x62,
  OP_XRL_id_to_db             = 0x63,
  OP_XRL_id_to_a              = 0x64,
  OP_XRL_db_to_a              = 0x65,
  OP_XRL_ir0_to_a             = 0x66,
  OP_XRL_ir1_to_a             = 0x67,
  OP_XRL_r0_to_a              = 0x68,
  OP_XRL_r1_to_a              = 0x69,
  OP_XRL_r2_to_a              = 0x6A,
  OP_XRL_r3_to_a              = 0x6B,
  OP_XRL_r4_to_a              = 0x6C,
  OP_XRL_r5_to_a              = 0x6D,
  OP_XRL_r6_to_a              = 0x6E,
  OP_XRL_r7_to_a              = 0x6F,
  OP_JNZ                      = 0x70,
  OP_ACALL_3                  = 0x71, // exact duplicate of 0x11
  OP_ORL_dbi_to_c             = 0x72,
  OP_JMP                      = 0x73,
  OP_MOV_id_to_a              = 0x74,
  OP_MOV_id_to_db             = 0x75,
  OP_MOV_id_to_ir0            = 0x76,
  OP_MOV_id_to_ir1            = 0x77,
  OP_MOV_id_to_r0             = 0x78,
  OP_MOV_id_to_r1             = 0x79,
  OP_MOV_id_to_r2             = 0x7A,
  OP_MOV_id_to_r3             = 0x7B,
  OP_MOV_id_to_r4             = 0x7C,
  OP_MOV_id_to_r5             = 0x7D,
  OP_MOV_id_to_r6             = 0x7E,
  OP_MOV_id_to_r7             = 0x7F,
  OP_SJMP                     = 0x80,
  OP_AJMP_4                   = 0x81, // exact duplicate of 0x01
  OP_ANL_dbi_to_c             = 0x82,
  OP_MOVC_pc_to_a             = 0x83,
  OP_DIV                      = 0x84,
  OP_MOV_db_to_db             = 0x85,
  OP_MOV_ir0_to_db            = 0x86,
  OP_MOV_ir1_to_db            = 0x87,
  OP_MOV_r0_to_db             = 0x88,
  OP_MOV_r1_to_db             = 0x89,
  OP_MOV_r2_to_db             = 0x8A,
  OP_MOV_r3_to_db             = 0x8B,
  OP_MOV_r4_to_db             = 0x8C,
  OP_MOV_r5_to_db             = 0x8D,
  OP_MOV_r6_to_db             = 0x8E,
  OP_MOV_r7_to_db             = 0x8F,
  OP_MOV_16bit_id_to_dptr     = 0x90,
  OP_ACALL_4                  = 0x91, // exact duplicate of 0x11
  OP_MOV_c_to_dbi             = 0x92,
  OP_MOVC_dptr_to_a           = 0x93,
  OP_SUBB_id                  = 0x94,
  OP_SUBB_db                  = 0x95,
  OP_SUBB_ir0                 = 0x96,
  OP_SUBB_ir1                 = 0x97,
  OP_SUBB_r0                  = 0x98,
  OP_SUBB_r1                  = 0x99,
  OP_SUBB_r2                  = 0x9A,
  OP_SUBB_r3                  = 0x9B,
  OP_SUBB_r4                  = 0x9C,
  OP_SUBB_r5                  = 0x9D,
  OP_SUBB_r6                  = 0x9E,
  OP_SUBB_r7                  = 0x9F,
  OP_ORL_co_of_dbi_to_c       = 0xA0,
  OP_AJMP_5                   = 0xA1, // exact duplicate of 0x01
  OP_MOV_dbi_to_c             = 0xA2,
  OP_INC_dptr                 = 0xA3,
  OP_MUL                      = 0xA4,
  OP_reserved                 = 0xA5,
  OP_MOV_db_to_ir0            = 0xA6,
  OP_MOV_db_to_ir1            = 0xA7,
  OP_MOV_db_to_r0             = 0xA8,
  OP_MOV_db_to_r1             = 0xA9,
  OP_MOV_db_to_r2             = 0xAA,
  OP_MOV_db_to_r3             = 0xAB,
  OP_MOV_db_to_r4             = 0xAC,
  OP_MOV_db_to_r5             = 0xAD,
  OP_MOV_db_to_r6             = 0xAE,
  OP_MOV_db_to_r7             = 0xAF,
  OP_ANL_co_of_dbi_to_c       = 0xB0,
  OP_ACALL_5                  = 0xB1, // exact duplicate of 0x11
  OP_CPL_dbi                  = 0xB2,
  OP_CPL_c                    = 0xB3,
  OP_CJNE_id_to_a             = 0xB4,
  OP_CJNE_db_to_a             = 0xB5,
  OP_CJNE_id_to_ir0           = 0xB6,
  OP_CJNE_id_to_ir1           = 0xB7,
  OP_CJNE_id_to_r0            = 0xB8,
  OP_CJNE_id_to_r1            = 0xB9,
  OP_CJNE_id_to_r2            = 0xBA,
  OP_CJNE_id_to_r3            = 0xBB,
  OP_CJNE_id_to_r4            = 0xBC,
  OP_CJNE_id_to_r5            = 0xBD,
  OP_CJNE_id_to_r6            = 0xBE,
  OP_CJNE_id_to_r7            = 0xBF,
  OP_PUSH                     = 0xC0,
  OP_AJMP_6                   = 0xC1, // exact duplicate of 0x01
  OP_CLR_dbi                  = 0xC2,
  OP_CLR_c                    = 0xC3,
  OP_SWAP                     = 0xC4,
  OP_XCH_db                   = 0xC5,
  OP_XCH_ir0                  = 0xC6,
  OP_XCH_ir1                  = 0xC7,
  OP_XCH_r0                   = 0xC8,
  OP_XCH_r1                   = 0xC9,
  OP_XCH_r2                   = 0xCA,
  OP_XCH_r3                   = 0xCB,
  OP_XCH_r4                   = 0xCC,
  OP_XCH_r5                   = 0xCD,
  OP_XCH_r6                   = 0xCE,
  OP_XCH_r7                   = 0xCF,
  OP_POP                      = 0xD0,
  OP_ACALL_6                  = 0xD1, // exact duplicate of 0x11
  OP_SETB_dbi                 = 0xD2,
  OP_SETB_c                   = 0xD3,
  OP_DA                       = 0xD4,
  OP_DJNZ_r0                  = 0xD8,
  OP_DJNZ_r1                  = 0xD9,
  OP_DJNZ_r2                  = 0xDA,
  OP_DJNZ_r3                  = 0xDB,
  OP_DJNZ_r4                  = 0xDC,
  OP_DJNZ_r5                  = 0xDD,
  OP_DJNZ_r6                  = 0xDE,
  OP_DJNZ_r7                  = 0xDF,
  OP_MOVX_16bit_edptr_to_a    = 0xE0,
  OP_AJMP_7                   = 0xE1, // exact duplicate of 0x01
  OP_MOVX_eir0_to_a           = 0xE2,
  OP_MOVX_eir1_to_a           = 0xE3,
  OP_CLR_a                    = 0xE4,
  OP_MOV_db_to_a              = 0xE5,
  OP_MOV_ir0_to_a             = 0xE6,
  OP_MOV_ir1_to_a             = 0xE7,
  OP_MOV_r0_to_a              = 0xE8,
  OP_MOV_r1_to_a              = 0xE9,
  OP_MOV_r2_to_a              = 0xEA,
  OP_MOV_r3_to_a              = 0xEB,
  OP_MOV_r4_to_a              = 0xEC,
  OP_MOV_r5_to_a              = 0xED,
  OP_MOV_r6_to_a              = 0xEE,
  OP_MOV_r7_to_a              = 0xEF,
  OP_MOVX_a_to_16bit_edptr    = 0xF0,
  OP_ACALL_7                  = 0xF1, // exact duplicate of 0x11
  OP_MOVX_a_to_eir0           = 0xF2,
  OP_MOVX_a_to_eir1           = 0xF3,
  OP_CPL_a                    = 0xF4,
  OP_MOV_a_to_db              = 0xF5,
  OP_MOV_a_to_ir0             = 0xF6,
  OP_MOV_a_to_ir1             = 0xF7,
  OP_MOV_a_to_r0              = 0xF8,
  OP_MOV_a_to_r1              = 0xF9,
  OP_MOV_a_to_r2              = 0xFA,
  OP_MOV_a_to_r3              = 0xFB,
  OP_MOV_a_to_r4              = 0xFC,
  OP_MOV_a_to_r5              = 0xFD,
  OP_MOV_a_to_r6              = 0xFE,
  OP_MOV_a_to_r7              = 0xFF,
} iopcode_t;

/***************************/
/*  ARITHMETIC OPERATIONS  */
/***************************/

void ADD_r(iopcode_t ins, cpu_t *cpu);
void ADD_db(cpu_t *cpu);
void ADD_ir(iopcode_t ins, cpu_t *cpu);
void ADD_id(cpu_t *cpu);
void ADDC_r();
void ADDC_db();
void ADDC_ir();
void ADDC_id();
void SUBB_r();
void SUBB_db();
void SUBB_ir();
void SUBB_id();
void INC_a(cpu_t *cpu);
void INC_r(iopcode_t ins, cpu_t *cpu);
void INC_db(cpu_t *cpu);
void INC_ir(iopcode_t ins, cpu_t *cpu);
void INC_dptr();
void DEC_a(cpu_t *cpu);
void DEC_r(iopcode_t ins, cpu_t *cpu);
void DEC_db(cpu_t *cpu);
void DEC_ir(iopcode_t ins, cpu_t *cpu);
void MUL();
void DIV();
void DA();

/************************/
/*  LOGICAL OPERATIONS  */
/************************/

void ANL_r_to_a(iopcode_t ins, cpu_t *cpu);
void ANL_db_to_a(cpu_t *cpu);
void ANL_ir_to_a(iopcode_t ins, cpu_t *cpu);
void ANL_id_to_a(cpu_t *cpu);
void ANL_a_to_db(cpu_t *cpu);
void ANL_id_to_db(cpu_t *cpu);
// More in Boolean Variable Manipulation group.
void ORL_r_to_a(iopcode_t ins, cpu_t *cpu);
void ORL_db_to_a(cpu_t *cpu);
void ORL_ir_to_a(iopcode_t ins, cpu_t *cpu);
void ORL_id_to_a(cpu_t *cpu);
void ORL_a_to_db(cpu_t *cpu);
void ORL_id_to_db(cpu_t *cpu);
// More in Boolean Variable Manipulation group.
void XRL_r_to_a(iopcode_t ins, cpu_t *cpu);
void XRL_db_to_a(cpu_t *cpu);
void XRL_ir_to_a(iopcode_t ins, cpu_t *cpu);
void XRL_id_to_a(cpu_t *cpu);
void XRL_a_to_db(cpu_t *cpu);
void XRL_id_to_db(cpu_t *cpu);
void CLR_a(cpu_t *cpu);
// More in Boolean Variable Manipulation group.
void CPL_a();
// More in Boolean Variable Manipulation group.
void RL(cpu_t *cpu);
void RLC(cpu_t *cpu);
void RR(cpu_t *cpu);
void RRC(cpu_t *cpu);
void SWAP();

/******************************/
/* DATA TRANSFER INSTRUCTIONS */
/******************************/

void MOV_r_to_a();
void MOV_db_to_a();
void MOV_ir_to_a();
void MOV_id_to_a(cpu_t *cpu);
void MOV_a_to_r();
void MOV_db_to_r();
void MOV_id_to_r(iopcode_t ins, cpu_t *cpu);
void MOV_a_to_db();
void MOV_r_to_db();
void MOV_db_to_db();
void MOV_ir_to_db();
void MOV_id_to_db();
void MOV_a_to_ir();
void MOV_db_to_ir();
void MOV_id_to_ir(iopcode_t ins, cpu_t *cpu);
void MOV_16bit_id_to_dptr();
// More in Boolean Variable Manipulation group.
void MOVC_dptr_to_a();
void MOVC_pc_to_a();
void MOVX_eir_to_a();
void MOVX_16bit_edptr_to_a();
void MOVX_a_to_eir();
void MOVX_a_to_16bit_edptr();
void PUSH(cpu_t *cpu);
void POP();
void XCH_r();
void XCH_db();
void XCH_ir();
void XCHD_ir();

/*********************************/
/* BOOLEAN VARIABLE MANIPULATION */
/*********************************/

void CLR_c(cpu_t *cpu);
void CLR_dbi(balt_single_t addr);
void SETB_c(cpu_t *cpu);
void SETB_dbi(balt_single_t addr);
void CPL_c();
void CPL_dbi();
void ANL_dbi_to_c();
void ANL_co_of_dbi_to_c();
void ORL_dbi_to_c();
void ORL_co_of_dbi_to_c();
void MOV_dbi_to_c(balt_single_t addr, cpu_t *cpu);
void MOV_c_to_dbi(balt_single_t addr, cpu_t *cpu);
#define MOV(i, o) _Generic((i), \
  char: _Generic((o), \
          char: MOV_db_to_r), \
)(i, o)
void JC();
void JNC();
void JB(balt_single_t addr, cpu_t *cpu);
void JNB();
void JBC(balt_single_t addr, cpu_t *cpu, bool clear_bit);

/*****************************************/
/* PROGRAM BRANCHING AND MACHINE CONTROL */
/*****************************************/

void ACALL(iopcode_t ins, cpu_t *cpu);
void LCALL(cpu_t *cpu);
void RET(cpu_t *cpu);
void RETI();
void AJMP(iopcode_t ins, cpu_t *cpu);
void LJMP(cpu_t *cpu);
void SJMP();
void JMP();
void JZ();
void JNZ();
void CJNE_db_to_a();
void CJNE_id_to_a();
void CJNE_id_to_r();
void CJNE_id_to_ir();
void DJNZ_r();
void DJNZ_db();
void NOP();

#endif /* INSTRUCTION_H_INCLUDED */
