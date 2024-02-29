#include "instruction.h"

static uint8_t reg_idx_from_opcode(uint8_t opcode) {
  return (CHBI(opcode, 0) << 0 | CHBI(opcode, 1) << 1 | CHBI(opcode, 2) << 2);
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
void MOV_id_to_r(uint8_t data[2], iram_t *iram)
{
  // Get address of the bank's array (which is address of the first
  // register), add the index of the targeted register, write data by
  // pointing to the targeted register's address.
  /* *(*(set_active_working_register_bank(iram)) + reg_idx_from_opcode(data[0])) = data[1]; */
  // More terse and readable but for some reason inconsistent between
  // compilations, sometimes it works and sometimes it doesn't.
  iram->separated.R[(iram->separated.SFR.PSW >> 3) & 0x03][reg_idx_from_opcode(data[0])] = data[1];
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


/*********************************/
/* BOOLEAN VARIABLE MANIPULATION */
/*********************************/

void MOV_dbi_to_c();
void MOV_c_to_dbi();
