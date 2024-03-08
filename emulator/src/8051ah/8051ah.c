#include "8051ah.h"
#include "opcode.h"

void init_device(device_t *device, rom_t *rom)
{
  if (!device) return;
  init_ram(&device->cpu.iram);
  init_rom(&device->cpu.rom, rom, rom == NULL ? false : true);
  init_ram_balt(device->iram_balt, &device->cpu.iram);
}

void run_device(device_t *device)
{
  if (!device) return;
  while (true) {
    if (device->cpu.pc == ROM_SIZE) break;
    uint8_t ins = device->cpu.rom[device->cpu.pc];
    switch (ins) {
      case OP_ORL_a_to_db:
        ORL_a_to_db(&device->cpu);
        break;
      case OP_ORL_id_to_db:
        ORL_id_to_db(&device->cpu);
        break;
      case OP_ORL_id_to_a:
        ORL_id_to_a(&device->cpu);
        break;
      case OP_ORL_db_to_a:
        ORL_db_to_a(&device->cpu);
        break;
      case OP_ORL_ir0_to_a:
      case OP_ORL_ir1_to_a:
        ORL_ir_to_a(ins, &device->cpu);
        break;
      case OP_ORL_r0_to_a:
      case OP_ORL_r1_to_a:
      case OP_ORL_r2_to_a:
      case OP_ORL_r3_to_a:
      case OP_ORL_r4_to_a:
      case OP_ORL_r5_to_a:
      case OP_ORL_r6_to_a:
      case OP_ORL_r7_to_a:
        ORL_r_to_a(ins, &device->cpu);
        break;
      case OP_ANL_a_to_db:
        ANL_a_to_db(&device->cpu);
        break;
      case OP_ANL_id_to_db:
        ANL_id_to_db(&device->cpu);
        break;
      case OP_ANL_id_to_a:
        ANL_id_to_a(&device->cpu);
        break;
      case OP_ANL_db_to_a:
        ANL_db_to_a(&device->cpu);
        break;
      case OP_ANL_ir0_to_a:
      case OP_ANL_ir1_to_a:
        ANL_ir_to_a(ins, &device->cpu);
        break;
      case OP_ANL_r0_to_a:
      case OP_ANL_r1_to_a:
      case OP_ANL_r2_to_a:
      case OP_ANL_r3_to_a:
      case OP_ANL_r4_to_a:
      case OP_ANL_r5_to_a:
      case OP_ANL_r6_to_a:
      case OP_ANL_r7_to_a:
        ANL_r_to_a(ins, &device->cpu);
        break;
      case OP_XRL_a_to_db:
        XRL_a_to_db(&device->cpu);
        break;
      case OP_XRL_id_to_db:
        XRL_id_to_db(&device->cpu);
        break;
      case OP_XRL_id_to_a:
        XRL_id_to_a(&device->cpu);
        break;
      case OP_XRL_db_to_a:
        XRL_db_to_a(&device->cpu);
        break;
      case OP_XRL_ir0_to_a:
      case OP_XRL_ir1_to_a:
        XRL_ir_to_a(ins, &device->cpu);
        break;
      case OP_XRL_r0_to_a:
      case OP_XRL_r1_to_a:
      case OP_XRL_r2_to_a:
      case OP_XRL_r3_to_a:
      case OP_XRL_r4_to_a:
      case OP_XRL_r5_to_a:
      case OP_XRL_r6_to_a:
      case OP_XRL_r7_to_a:
        XRL_r_to_a(ins, &device->cpu);
        break;
      case OP_MOV_id_to_a:
        MOV_id_to_a(&device->cpu);
        break;
      case OP_MOV_id_to_ir0:
      case OP_MOV_id_to_ir1:
        MOV_id_to_ir(ins, &device->cpu);
        break;
      case OP_MOV_id_to_r0:
      case OP_MOV_id_to_r1:
      case OP_MOV_id_to_r2:
      case OP_MOV_id_to_r3:
      case OP_MOV_id_to_r4:
      case OP_MOV_id_to_r5:
      case OP_MOV_id_to_r6:
      case OP_MOV_id_to_r7:
        MOV_id_to_r(ins, &device->cpu);
        break;
      case OP_CLR_c:
        CLR_c(&device->cpu);
        break;
      case OP_CLR_dbi:
        device->cpu.pc = device->cpu.pc + 1;
        CLR_dbi(device->iram_balt[device->cpu.rom[device->cpu.pc]], &device->cpu);
        break;
      case OP_SETB_c:
        SETB_c(&device->cpu);
        break;
      case OP_SETB_dbi:
        device->cpu.pc = device->cpu.pc + 1;
        SETB_dbi(device->iram_balt[device->cpu.rom[device->cpu.pc]], &device->cpu);
        break;
      case OP_MOV_dbi_to_c:
        device->cpu.pc = device->cpu.pc + 1;
        MOV_dbi_to_c(device->iram_balt[device->cpu.rom[device->cpu.pc]], &device->cpu);
        break;
      case OP_MOV_c_to_dbi:
        device->cpu.pc = device->cpu.pc + 1;
        MOV_c_to_dbi(device->iram_balt[device->cpu.rom[device->cpu.pc]], &device->cpu);
        break;
      case OP_LJMP:
        LJMP(&device->cpu);
        break;
      case OP_NOP:
        break;
    }
    device->cpu.pc = device->cpu.pc + 1;
  }
}
