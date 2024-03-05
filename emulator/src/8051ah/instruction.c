#include "instruction.h"

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

static uint8_t get_reg_idx(uint8_t opcode) {
  return (CHBI(opcode, 0) << 0 | CHBI(opcode, 1) << 1 | CHBI(opcode, 2) << 2);
}

static uint8_t get_wrb_idx(psw_t psw) {
  return (psw >> 3) & 0x03;
}

/******************************/
/* DATA TRANSFER INSTRUCTIONS */
/******************************/

void MOV_r_to_a();
void MOV_db_to_a();
void MOV_ir_to_a();
void MOV_id_to_a();

void MOV_a_to_r();
void MOV_db_to_r();
void MOV_id_to_r(uint8_t ins, cpu_t *cpu)
{
  // Get working register bank index from RS1 and RS0, then pointer
  // arithmetic to assign data to the targeted register.
  cpu->pc = cpu->pc + 1; // As the opcode is two bytes.
  uint8_t wrb_idx = get_wrb_idx(cpu->iram.separated.SFR.PSW);
  *(cpu->iram.separated.R[wrb_idx] + get_reg_idx(ins)) = *(cpu->rom + cpu->pc);
};

void MOV_a_db();
void MOV_r_to_db();
void MOV_db_to_db();
void MOV_ir_to_db();
void MOV_id_to_db();

void MOV_a_to_ir();
void MOV_db_to_ir();
void MOV_id_to_ir();
void MOV_16bit_id_to_dptr();

// DIRECT
void PUSH(iram_t *iram)
{
  iram->separated.SFR.SP++;
}


/*********************************/
/* BOOLEAN VARIABLE MANIPULATION */
/*********************************/

void MOV_dbi_to_c();
void MOV_c_to_dbi();
