#include <8051ah/instruction.h>

static uint8_t get_reg_idx(uint8_t opcode)
{
  return (((opcode >> 0) & 1) << 0) | (((opcode >> 1) & 1) << 1) | (((opcode >> 2) & 1) << 2);
}

static uint8_t get_wrb_idx(psw_t psw)
{
  return (psw >> 3) & 0x03;
}

/***************************/
/*  ARITHMETIC OPERATIONS  */
/***************************/

void ADD_r(iopcode_t ins, cpu_t *cpu)
{
}

void ADD_db(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1;
  uint8_t c_states = (cpu->iram.separated.SFR.A  & 0b10001000) << 0;
  if ((cpu->iram.separated.SFR.A + cpu->iram.compact[cpu->rom[cpu->pc]]) > 0xFF) {
    cpu->iram.separated.SFR.A = (cpu->iram.separated.SFR.A + cpu->iram.compact[cpu->rom[cpu->pc]]) - 0xFF;
    cpu->iram.separated.SFR.PSW |= 1 << 2;
  } else cpu->iram.separated.SFR.A += cpu->iram.compact[cpu->rom[cpu->pc]];
  // If there is a carry out on bit 7, set carry flag.
  if (((c_states >> 7) & 1) & !((cpu->iram.separated.SFR.A >> 7) & 1))
    cpu->iram.separated.SFR.PSW |= 1 << 7;
  // If there is a carry out on bit 3, set auxiliary carry flag.
  if (((c_states >> 3) & 1) & !((cpu->iram.separated.SFR.A >> 3) & 1))
    cpu->iram.separated.SFR.PSW |= 1 << 6;
}

void ADD_ir(iopcode_t ins, cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1;
  uint8_t c_states = (cpu->iram.separated.SFR.A  & 0b10001000) << 0;
  if ((cpu->iram.separated.SFR.A + cpu->iram.separated.R[get_wrb_idx(cpu->iram.separated.SFR.PSW)][(ins >> 0) & 1]) > 0xFF) {
    cpu->iram.separated.SFR.A = (cpu->iram.separated.SFR.A + cpu->iram.separated.R[get_wrb_idx(cpu->iram.separated.SFR.PSW)][(ins >> 0) & 1]) - 0xFF;
    cpu->iram.separated.SFR.PSW |= 1 << 2;
  } else cpu->iram.separated.SFR.A += cpu->iram.separated.R[get_wrb_idx(cpu->iram.separated.SFR.PSW)][(ins >> 0) & 1];
  // If there is a carry out on bit 7, set carry flag.
  if (((c_states >> 7) & 1) & !((cpu->iram.separated.SFR.A >> 7) & 1))
    cpu->iram.separated.SFR.PSW |= 1 << 7;
  // If there is a carry out on bit 3, set auxiliary carry flag.
  if (((c_states >> 3) & 1) & !((cpu->iram.separated.SFR.A >> 3) & 1))
    cpu->iram.separated.SFR.PSW |= 1 << 6;
}

void ADD_id(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1;
  uint8_t c_states = (cpu->iram.separated.SFR.A  & 0b10001000) << 0;
  if ((cpu->iram.separated.SFR.A + cpu->rom[cpu->pc]) > 0xFF) {
    cpu->iram.separated.SFR.A = (cpu->iram.separated.SFR.A + cpu->rom[cpu->pc]) - 0xFF;
    cpu->iram.separated.SFR.PSW |= 1 << 2;
  } else cpu->iram.separated.SFR.A += cpu->rom[cpu->pc];
  // If there is a carry out on bit 7, set carry flag.
  if (((c_states >> 7) & 1) & !((cpu->iram.separated.SFR.A >> 7) & 1))
    cpu->iram.separated.SFR.PSW |= 1 << 7;
  // If there is a carry out on bit 3, set auxiliary carry flag.
  if (((c_states >> 3) & 1) & !((cpu->iram.separated.SFR.A >> 3) & 1))
    cpu->iram.separated.SFR.PSW |= 1 << 6;
}

void INC_a(cpu_t *cpu)
{
  cpu->iram.separated.SFR.A++;
}

void INC_r(iopcode_t ins, cpu_t *cpu)
{
  cpu->iram.separated.R[get_wrb_idx(cpu->iram.separated.SFR.PSW)][get_reg_idx(ins)]++;
}

void INC_db(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1;
  cpu->iram.compact[cpu->rom[cpu->pc]]++;
}

void INC_ir(iopcode_t ins, cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1;
  cpu->iram.separated.R[get_wrb_idx(cpu->iram.separated.SFR.PSW)][(ins >> 0) & 1]++;
}

void DEC_a(cpu_t *cpu)
{
  cpu->iram.separated.SFR.A--;
}

void DEC_r(iopcode_t ins, cpu_t *cpu)
{
  cpu->iram.separated.R[get_wrb_idx(cpu->iram.separated.SFR.PSW)][get_reg_idx(ins)]--;
}

void DEC_db(cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1;
  cpu->iram.compact[cpu->rom[cpu->pc]]--;
}

void DEC_ir(iopcode_t ins, cpu_t *cpu)
{
  cpu->pc = cpu->pc + 1;
  cpu->iram.separated.R[get_wrb_idx(cpu->iram.separated.SFR.PSW)][(ins >> 0) & 1]--;
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

void RL(cpu_t *cpu)
{
  cpu->iram.separated.SFR.A = cpu->iram.separated.SFR.A << 1 | cpu->iram.separated.SFR.A >> 7;
}

void RLC(cpu_t *cpu)
{
  uint8_t c = ((cpu->iram.separated.SFR.PSW >> 7) << 7);
  cpu->iram.separated.SFR.PSW = ((cpu->iram.separated.SFR.A >> 7) & 1) << 7;
  cpu->iram.separated.SFR.A = cpu->iram.separated.SFR.A << 1 | c >> 7;
}

void RR(cpu_t *cpu)
{
  cpu->iram.separated.SFR.A = cpu->iram.separated.SFR.A >> 1 | cpu->iram.separated.SFR.A << 7;
}

void RRC(cpu_t *cpu)
{
  uint8_t c = ((cpu->iram.separated.SFR.PSW >> 7) << 7);
  cpu->iram.separated.SFR.PSW = ((cpu->iram.separated.SFR.A >> 0) & 1) << 7;
  cpu->iram.separated.SFR.A = cpu->iram.separated.SFR.A >> 1 | c << 0;
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

void JB(balt_single_t addr, cpu_t *cpu)
{
  // JB is JBC without bit clear.
  JBC(addr, cpu, 0);
}

void JBC(balt_single_t addr, cpu_t *cpu, bool clear_bit)
{
  cpu->pc = cpu->pc + 1;
  uint8_t rel_addr = cpu->rom[cpu->pc];
  cpu->pc = cpu->pc + 1;
  if ((*addr.ptr >> addr.idx) & 1) {
    if (clear_bit) *addr.ptr &= ~(1 << addr.idx);
    cpu->pc = cpu->pc + rel_addr;
  }
}

/*****************************************/
/* PROGRAM BRANCHING AND MACHINE CONTROL */
/*****************************************/

void ACALL(iopcode_t ins, cpu_t *cpu)
{
  cpu->iram.separated.SFR.SP++;
  cpu->iram.compact[cpu->iram.separated.SFR.SP] = ((cpu->pc + 2) & 0b0000000011111111) >> 0;
  cpu->iram.separated.SFR.SP++;
  cpu->iram.compact[cpu->iram.separated.SFR.SP] = ((cpu->pc + 2) & 0b1111111100000000) >> 8;
  // Extract bits 5-7 from the instruction and shift them to the left by 3
  // bits, combine them with all bits from the next byte in ROM, then
  // combine them with the 5 MSB bits from the next byte in ROM.
  cpu->pc = ((cpu->pc + 2) & 0b1111100000000000) |
    ((ins & 0b11100000) << 3) |
    ((cpu->rom[cpu->pc + 1] & 0b11111111) << 0);
}

void LCALL(cpu_t *cpu)
{
  cpu->iram.separated.SFR.SP++;
  cpu->iram.compact[cpu->iram.separated.SFR.SP] = ((cpu->pc + 3) & 0b0000000011111111) >> 0;
  cpu->iram.separated.SFR.SP++;
  cpu->iram.compact[cpu->iram.separated.SFR.SP] = ((cpu->pc + 3) & 0b1111111100000000) >> 8;
  cpu->pc = cpu->rom[cpu->pc + 1] << 8 | cpu->rom[cpu->pc + 2] >> 0;
}

void RET(cpu_t *cpu)
{
  cpu->pc = cpu->iram.compact[cpu->iram.separated.SFR.SP - 1] << 8 |
    cpu->iram.compact[cpu->iram.separated.SFR.SP] >> 0;
  cpu->iram.separated.SFR.SP--;
  cpu->iram.separated.SFR.SP--;
}

void AJMP(iopcode_t ins, cpu_t *cpu)
{
  // Same with the last procedure of ACALL.
  cpu->pc = ((cpu->pc + 2) & 0b1111100000000000) |
    ((ins & 0b0000000011100000) << 3) |
    ((cpu->rom[cpu->pc + 1] & 0b11111111) << 0);
}

void LJMP(cpu_t *cpu)
{
  cpu->pc = cpu->rom[cpu->pc + 1] << 8 | cpu->rom[cpu->pc + 2];
}
