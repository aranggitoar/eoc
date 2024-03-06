#include "memory.h"
#include "cpu.h"
#include "../utils.h"

#pragma once

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

/***************************/
/*  ARITHMETIC OPERATIONS  */
/***************************/

void ADD_r();
void ADD_db();
void ADD_ir();
void ADD_id();
void ADDC_r();
void ADDC_db();
void ADDC_ir();
void ADDC_id();
void SUBB_r();
void SUBB_db();
void SUBB_ir();
void SUBB_id();
void INC_a();
void INC_r();
void INC_db();
void INC_ir();
void INC_dptr();
void DEC_a();
void DEC_r();
void DEC_db();
void DEC_ir();
void MUL();
void DIV();
void DA();

/************************/
/*  LOGICAL OPERATIONS  */
/************************/

void ANL_r_to_a();
void ANL_db_to_a();
void ANL_ir_to_a();
void ANL_id_to_a();
void ANL_a_to_db();
void ANL_id_to_db();
// More in Boolean Variable Manipulation group.
void ORL_r_to_a();
void ORL_db_to_a();
void ORL_ir_to_a();
void ORL_id_to_a();
void ORL_a_to_db();
void ORL_id_to_db();
// More in Boolean Variable Manipulation group.
void XRL_r_to_a();
void XRL_db_to_a();
void XRL_ir_to_a();
void XRL_id_to_a();
void XRL_a_to_db();
void XRL_id_to_db();
void CLR_a();
// More in Boolean Variable Manipulation group.
void CPL_a();
// More in Boolean Variable Manipulation group.
void RL();
void RLC();
void RR();
void RRC();
void SWAP();

/******************************/
/* DATA TRANSFER INSTRUCTIONS */
/******************************/

void MOV_r_to_a();
void MOV_db_to_a();
void MOV_ir_to_a();
void MOV_id_to_a();
void MOV_a_to_r();
void MOV_db_to_r();
void MOV_id_to_r(uint8_t data, cpu_t *cpu);
void MOV_a_to_db();
void MOV_r_to_db();
void MOV_db_to_db();
void MOV_ir_to_db();
void MOV_id_to_db();
void MOV_a_to_ir();
void MOV_db_to_ir();
void MOV_id_to_ir();
void MOV_16bit_id_to_dptr();
// More in Boolean Variable Manipulation group.
void MOVC_dptr_to_a();
void MOVC_pc_to_a();
void MOVX_eir_to_a();
void MOVX_16bit_edptr_to_a();
void MOVX_a_to_eir();
void MOVX_a_to_16bit_edptr();
void PUSH(iram_t *iram);
void POP();
void XCH_r();
void XCH_db();
void XCH_ir();
void XCHD_ir();

/*********************************/
/* BOOLEAN VARIABLE MANIPULATION */
/*********************************/

void CLR_c();
void CLR_dbi();
void SETB_c();
void SETB_dbi();
void CPL_c();
void CPL_dbi();
void ANL_dbi_to_c();
void ANL_co_of_dbi_to_c();
void ORL_dbi_to_c();
void ORL_co_of_dbi_to_c();
void MOV_dbi_to_c();
void MOV_c_to_dbi();
#define MOV(i, o) _Generic((i), \
  char: _Generic((o), \
          char: MOV_db_to_r), \
)(i, o)
void JC();
void JNC();
void JB();
void JNB();
void JBC();

/*****************************************/
/* PROGRAM BRANCHING AND MACHINE CONTROL */
/*****************************************/

void ACALL();
void LCALL();
void RET();
void RETI();
void AJMP();
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
