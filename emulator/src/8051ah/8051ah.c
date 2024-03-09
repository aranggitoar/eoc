#include <8051ah/8051ah.h>

void init_device_8051ah(device_8051ah_t *device, rom_t *rom)
{
  if (!device) return;
  init_ram(&device->cpu.iram);
  init_rom(&device->cpu.rom, rom, rom == NULL ? false : true);
  init_ram_balt(device->iram_balt, &device->cpu.iram);
}

void run_device_8051ah(device_8051ah_t *device)
{
  if (!device) return;
  while (true) {
    if (device->cpu.pc == ROM_SIZE) break;
    iopcode_t ins = device->cpu.rom[device->cpu.pc];
    // Follows the order of typedef enum iopcode_t, except for
    // the multiple OP_AJMPs and OP_ACALLs so it would fold into
    // using/writing one function only.
    switch (ins) {
      case OP_NOP:
        break;
      case OP_AJMP:
      case OP_AJMP_1:
      case OP_AJMP_2:
      case OP_AJMP_3:
      case OP_AJMP_4:
      case OP_AJMP_5:
      case OP_AJMP_6:
      case OP_AJMP_7:
        break;
      case OP_LJMP:
        LJMP(&device->cpu);
        break;
      case OP_RR:
        break;
      case OP_INC_a:
        break;
      case OP_INC_db:
        break;
      case OP_INC_ir0:
      case OP_INC_ir1:
        break;
      case OP_INC_r0:
      case OP_INC_r1:
      case OP_INC_r2:
      case OP_INC_r3:
      case OP_INC_r4:
      case OP_INC_r5:
      case OP_INC_r6:
      case OP_INC_r7:
        break;
      case OP_JBC:
        break;
      case OP_ACALL:
      case OP_ACALL_1:
      case OP_ACALL_2:
      case OP_ACALL_3:
      case OP_ACALL_4:
      case OP_ACALL_5:
      case OP_ACALL_6:
      case OP_ACALL_7:
        break;
      case OP_LCALL:
        break;
      case OP_RRC:
        break;
      case OP_DEC_a:
        break;
      case OP_DEC_db:
        break;
      case OP_DEC_ir0:
      case OP_DEC_ir1:
        break;
      case OP_DEC_r0:
      case OP_DEC_r1:
      case OP_DEC_r2:
      case OP_DEC_r3:
      case OP_DEC_r4:
      case OP_DEC_r5:
      case OP_DEC_r6:
      case OP_DEC_r7:
        break;
      case OP_JB:
        break;
      case OP_RET:
        break;
      case OP_RL:
        break;
      case OP_ADD_id:
        break;
      case OP_ADD_db:
        break;
      case OP_ADD_ir0:
      case OP_ADD_ir1:
        break;
      case OP_ADD_r0:
      case OP_ADD_r1:
      case OP_ADD_r2:
      case OP_ADD_r3:
      case OP_ADD_r4:
      case OP_ADD_r5:
      case OP_ADD_r6:
      case OP_ADD_r7:
        break;
      case OP_JNB:
        break;
      case OP_RETI:
        break;
      case OP_RLC:
        break;
      case OP_ADDC_id:
        break;
      case OP_ADDC_db:
        break;
      case OP_ADDC_ir0:
      case OP_ADDC_ir1:
        break;
      case OP_ADDC_r0:
      case OP_ADDC_r1:
      case OP_ADDC_r2:
      case OP_ADDC_r3:
      case OP_ADDC_r4:
      case OP_ADDC_r5:
      case OP_ADDC_r6:
      case OP_ADDC_r7:
        break;
      case OP_JC:
        break;
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
      case OP_JNC:
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
      case OP_JZ:
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
      case OP_JNZ:
        break;
      case OP_ORL_dbi_to_c:
        break;
      case OP_JMP:
        break;
      case OP_MOV_id_to_a:
        MOV_id_to_a(&device->cpu);
        break;
      case OP_MOV_id_to_db:
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
      case OP_SJMP:
        break;
      case OP_ANL_dbi_to_c:
        break;
      case OP_MOVC_pc_to_a:
        break;
      case OP_DIV:
        break;
      case OP_MOV_db_to_db:
        break;
      case OP_MOV_ir0_to_db:
      case OP_MOV_ir1_to_db:
        break;
      case OP_MOV_r0_to_db:
      case OP_MOV_r1_to_db:
      case OP_MOV_r2_to_db:
      case OP_MOV_r3_to_db:
      case OP_MOV_r4_to_db:
      case OP_MOV_r5_to_db:
      case OP_MOV_r6_to_db:
      case OP_MOV_r7_to_db:
        break;
      case OP_MOV_16bit_id_to_dptr:
        break;
      case OP_MOV_c_to_dbi:
        device->cpu.pc = device->cpu.pc + 1;
        MOV_c_to_dbi(device->iram_balt[device->cpu.rom[device->cpu.pc]], &device->cpu);
        break;
      case OP_MOVC_dptr_to_a:
        break;
      case OP_SUBB_id:
        break;
      case OP_SUBB_db:
        break;
      case OP_SUBB_ir0:
      case OP_SUBB_ir1:
        break;
      case OP_SUBB_r0:
      case OP_SUBB_r1:
      case OP_SUBB_r2:
      case OP_SUBB_r3:
      case OP_SUBB_r4:
      case OP_SUBB_r5:
      case OP_SUBB_r6:
      case OP_SUBB_r7:
        break;
      case OP_ORL_co_of_dbi_to_c:
        break;
      case OP_MOV_dbi_to_c:
        device->cpu.pc = device->cpu.pc + 1;
        MOV_dbi_to_c(device->iram_balt[device->cpu.rom[device->cpu.pc]], &device->cpu);
        break;
      case OP_INC_dptr:
        break;
      case OP_MUL:
        break;
      case OP_reserved:
        break;
      case OP_MOV_db_to_ir0:
      case OP_MOV_db_to_ir1:
        break;
      case OP_MOV_db_to_r0:
      case OP_MOV_db_to_r1:
      case OP_MOV_db_to_r2:
      case OP_MOV_db_to_r3:
      case OP_MOV_db_to_r4:
      case OP_MOV_db_to_r5:
      case OP_MOV_db_to_r6:
      case OP_MOV_db_to_r7:
        break;
      case OP_ANL_co_of_dbi_to_c:
        break;
      case OP_CPL_dbi:
        break;
      case OP_CPL_c:
        break;
      case OP_CJNE_id_to_a:
        break;
      case OP_CJNE_db_to_a:
        break;
      case OP_CJNE_id_to_ir0:
      case OP_CJNE_id_to_ir1:
        break;
      case OP_CJNE_id_to_r0:
      case OP_CJNE_id_to_r1:
      case OP_CJNE_id_to_r2:
      case OP_CJNE_id_to_r3:
      case OP_CJNE_id_to_r4:
      case OP_CJNE_id_to_r5:
      case OP_CJNE_id_to_r6:
      case OP_CJNE_id_to_r7:
        break;
      case OP_PUSH:
        break;
      case OP_CLR_dbi:
        device->cpu.pc = device->cpu.pc + 1;
        CLR_dbi(device->iram_balt[device->cpu.rom[device->cpu.pc]]);
        break;
      case OP_CLR_c:
        CLR_c(&device->cpu);
        break;
      case OP_SWAP:
        break;
      case OP_XCH_db:
        break;
      case OP_XCH_ir0:
      case OP_XCH_ir1:
        break;
      case OP_XCH_r0:
      case OP_XCH_r1:
      case OP_XCH_r2:
      case OP_XCH_r3:
      case OP_XCH_r4:
      case OP_XCH_r5:
      case OP_XCH_r6:
      case OP_XCH_r7:
        break;
      case OP_POP:
        break;
      case OP_SETB_dbi:
        device->cpu.pc = device->cpu.pc + 1;
        SETB_dbi(device->iram_balt[device->cpu.rom[device->cpu.pc]]);
        break;
      case OP_SETB_c:
        SETB_c(&device->cpu);
        break;
      case OP_DA:
        break;
      case OP_DJNZ_r0:
      case OP_DJNZ_r1:
      case OP_DJNZ_r2:
      case OP_DJNZ_r3:
      case OP_DJNZ_r4:
      case OP_DJNZ_r5:
      case OP_DJNZ_r6:
      case OP_DJNZ_r7:
        break;
      case OP_MOVX_16bit_edptr_to_a:
        break;
      case OP_MOVX_eir0_to_a:
        break;
      case OP_MOVX_eir1_to_a:
        break;
      case OP_CLR_a:
        break;
      case OP_MOV_db_to_a:
        break;
      case OP_MOV_ir0_to_a:
        break;
      case OP_MOV_ir1_to_a:
        break;
      case OP_MOV_r0_to_a:
        break;
      case OP_MOV_r1_to_a:
        break;
      case OP_MOV_r2_to_a:
        break;
      case OP_MOV_r3_to_a:
        break;
      case OP_MOV_r4_to_a:
        break;
      case OP_MOV_r5_to_a:
        break;
      case OP_MOV_r6_to_a:
        break;
      case OP_MOV_r7_to_a:
        break;
      case OP_MOVX_a_to_16bit_edptr:
        break;
      case OP_MOVX_a_to_eir0:
        break;
      case OP_MOVX_a_to_eir1:
        break;
      case OP_CPL_a:
        break;
      case OP_MOV_a_to_db:
        break;
      case OP_MOV_a_to_ir0:
        break;
      case OP_MOV_a_to_ir1:
        break;
      case OP_MOV_a_to_r0:
        break;
      case OP_MOV_a_to_r1:
        break;
      case OP_MOV_a_to_r2:
        break;
      case OP_MOV_a_to_r3:
        break;
      case OP_MOV_a_to_r4:
        break;
      case OP_MOV_a_to_r5:
        break;
      case OP_MOV_a_to_r6:
        break;
      case OP_MOV_a_to_r7:
        break;
    }
    device->cpu.pc = device->cpu.pc + 1;
  }
}
