#include <8051ah/instruction.h>

static uint8_t get_reg_idx(uint8_t opcode)
{
  return (((opcode >> 0) & 1) << 0) | (((opcode >> 1) & 1) << 1) | (((opcode >> 2) & 1) << 2);
}

static uint8_t get_wrb_idx(psw_t psw)
{
  return (psw >> 3) & 0x03;
}

/************************/
/*  LOGICAL OPERATIONS  */
/************************/

void ANL_r_to_a(iopcode_t ins, cpu_t *cpu)
{
  uint8_t wrb_idx = get_wrb_idx(cpu->iram.separated.SFR.PSW);
  cpu->iram.separated.SFR.A &= cpu->iram.separated.R[wrb_idx][get_reg_idx(ins)];
}
void ANL_db_to_a(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1; // As the opcode is two bytes.
  cpu->iram.separated.SFR.A &= cpu->iram.compact[cpu->rom[cpu->pc]];
}
void ANL_ir_to_a(iopcode_t ins, cpu_t *cpu)
{
  uint8_t wrb_idx = get_wrb_idx(cpu->iram.separated.SFR.PSW);
  cpu->iram.separated.SFR.A &= cpu->iram.separated.R[wrb_idx][(ins >> 0) & 1];
}
void ANL_id_to_a(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1; // As the opcode is two bytes.
  cpu->iram.separated.SFR.A &= cpu->rom[cpu->pc];
}
void ANL_a_to_db(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1; // As the opcode is two bytes.
  cpu->iram.compact[cpu->rom[cpu->pc]] &= cpu->iram.separated.SFR.A;
}
void ANL_id_to_db(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1;
  uint8_t addr = cpu->rom[cpu->pc];
  cpu->pc = cpu->pc + 1; // As the opcode is three bytes.
  *(cpu->iram.compact + addr) &= *(cpu->rom +cpu->pc);
}
// More in Boolean Variable Manipulation group.

void ORL_r_to_a(iopcode_t ins, cpu_t *cpu)
{
  uint8_t wrb_idx = get_wrb_idx(cpu->iram.separated.SFR.PSW);
  cpu->iram.separated.SFR.A |= *(cpu->iram.separated.R[wrb_idx] + get_reg_idx(ins));
}
void ORL_db_to_a(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1; // As the opcode is two bytes.
  cpu->iram.separated.SFR.A |= cpu->iram.compact[cpu->rom[cpu->pc]];
}
void ORL_ir_to_a(iopcode_t ins, cpu_t *cpu)
{
  uint8_t wrb_idx = get_wrb_idx(cpu->iram.separated.SFR.PSW);
  cpu->iram.separated.SFR.A |= cpu->iram.separated.R[wrb_idx][(ins >> 0) & 1];
}
void ORL_id_to_a(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1; // As the opcode is two bytes.
  cpu->iram.separated.SFR.A |= cpu->rom[cpu->pc];
}
void ORL_a_to_db(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1; // As the opcode is two bytes.
  cpu->iram.compact[cpu->rom[cpu->pc]] |= cpu->iram.separated.SFR.A;
}
void ORL_id_to_db(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1;
  uint8_t addr = cpu->rom[cpu->pc];
  cpu->pc = cpu->pc + 1; // As the opcode is three bytes.
  cpu->iram.compact[addr] |= cpu->rom[cpu->pc];
}
// More in Boolean Variable Manipulation group.

void XRL_r_to_a(iopcode_t ins, cpu_t *cpu)
{
  uint8_t wrb_idx = get_wrb_idx(cpu->iram.separated.SFR.PSW);
  cpu->iram.separated.SFR.A ^= cpu->iram.separated.R[wrb_idx][get_reg_idx(ins)];
}
void XRL_db_to_a(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1; // As the opcode is two bytes.
  cpu->iram.separated.SFR.A ^= cpu->iram.compact[cpu->rom[cpu->pc]];
}
void XRL_ir_to_a(iopcode_t ins, cpu_t *cpu)
{
  uint8_t wrb_idx = get_wrb_idx(cpu->iram.separated.SFR.PSW);
  cpu->iram.separated.SFR.A ^= cpu->iram.separated.R[wrb_idx][(ins >> 0) & 1];
}
void XRL_id_to_a(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1; // As the opcode is two bytes.
  cpu->iram.separated.SFR.A ^= cpu->rom[cpu->pc];
}
void XRL_a_to_db(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1; // As the opcode is two bytes.
  cpu->iram.compact[cpu->rom[cpu->pc]] ^= cpu->iram.separated.SFR.A;
}
void XRL_id_to_db(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1;
  uint8_t addr = cpu->rom[cpu->pc];
  cpu->pc = cpu->pc + 1; // As the opcode is three bytes.
  cpu->iram.compact[addr] ^= cpu->rom[cpu->pc];
}

void CLR_a(cpu_t *cpu)
{
  cpu->iram.separated.SFR.A = 0;
}

/******************************/
/* DATA TRANSFER INSTRUCTIONS */
/******************************/

void MOV_r_to_a();
void MOV_db_to_a();
void MOV_ir_to_a();
void MOV_id_to_a(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1; // As the opcode is two bytes.
  cpu->iram.separated.SFR.A = cpu->rom[cpu->pc];
}

void MOV_a_to_r();
void MOV_db_to_r();
void MOV_id_to_r(iopcode_t ins, cpu_t *cpu)
{
  // Get working register bank index from RS1 and RS0, then pointer
  // arithmetic to assign data to the targeted register.
  cpu->pc = cpu->pc + 1; // As the opcode is two bytes.
  uint8_t wrb_idx = get_wrb_idx(cpu->iram.separated.SFR.PSW);
  cpu->iram.separated.R[wrb_idx][get_reg_idx(ins)] = cpu->rom[cpu->pc];
};

void MOV_a_db();
void MOV_r_to_db();
void MOV_db_to_db();
void MOV_ir_to_db();
void MOV_id_to_db();

void MOV_a_to_ir();
void MOV_db_to_ir();
void MOV_id_to_ir(iopcode_t ins, cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1; // As the opcode is two bytes.
  uint8_t wrb_idx = get_wrb_idx(cpu->iram.separated.SFR.PSW);
  cpu->iram.separated.R[wrb_idx][(ins >> 0) & 1] = cpu->rom[cpu->pc];
}
void MOV_16bit_id_to_dptr();

// DIRECT
void PUSH(cpu_t *cpu)
{
  cpu->iram.separated.SFR.SP++;
}

/*********************************/
/* BOOLEAN VARIABLE MANIPULATION */
/*********************************/

void CLR_c(cpu_t *cpu)
{
  cpu->iram.separated.SFR.PSW &= ~(1 << 7);
}
void CLR_dbi(balt_single_t addr)
{
  *addr.ptr &= ~(1 << addr.idx);
}

void SETB_c(cpu_t *cpu)
{
  cpu->iram.separated.SFR.PSW |= 1 << 7;
}
void SETB_dbi(balt_single_t addr)
{
  *addr.ptr |= 1 << addr.idx;
}

void MOV_dbi_to_c(balt_single_t addr, cpu_t *cpu)
{
  if (((cpu->iram.separated.SFR.PSW >> 7) & 1) != ((*addr.ptr >> addr.idx) & 1))
    cpu->iram.separated.SFR.PSW ^= 1 << 7;
}
void MOV_c_to_dbi(balt_single_t addr, cpu_t *cpu)
{
  if (((*addr.ptr >> addr.idx) & 1) != ((cpu->iram.separated.SFR.PSW >> 7) & 7))
    *addr.ptr ^= 1 << addr.idx;
}

/*****************************************/
/* PROGRAM BRANCHING AND MACHINE CONTROL */
/*****************************************/

void LJMP(cpu_t *cpu)
{
  cpu->pc = cpu->rom[cpu->pc + 1] << 8 | cpu->rom[cpu->pc + 2];
}
