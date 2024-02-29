/* #include <stdlib.h> */
#include <string.h>
#include <stdbool.h>
#include "8051ah.h"

cpu_t* init_cpu(rom_t *rom)
{
  iram_t iram = {};
  iram.separated.SFR = (sfr_t){
    .P0 = 0x0000, 
    .SP = 0x07,
    .DPTR = 0x0000,
    .TCON = 0x00,
    .TMOD = 0x00,
    .TL0 = 0x00,
    .TL1 = 0x00,
    .TH0 = 0x00,
    .TH1 = 0x00,
    .P1 = 0xFF,
    .SCON = 0x00,
    .SBUF = 0x00, // Supposed to be indeterminate.
    .P2 = 0xFF,
    .IE = 0x00, // X's are supposed to be indeterminate 0XX00000B.
    .P3 = 0xFF,
    .IP = 0x00, // X's are supposed to be indeterminate XXX00000B.
    .PSW = 0x00,
    .A = 0x00,
    .B = 0x00,
  };
  // ONLY FOR TESTING, REMOVE CODE AFTERWARDS
  iram.separated.R[0][0] = 1;
  // As PSW is initialized as 0x00, the working register would be the
  // first bank as the middle 2 bits of PSW are 0.
  /* memcpy(iram.separated.R[0], &iram.separated.R_B0[0], sizeof(uint8_t)); */

  return &(cpu_t){.pc = 0x0000, .iram = &iram, .rom = rom};
}

void run_cpu(cpu_t *cpu)
{
  while (true) {
    // Find a better way as this would be run and set for every iteration.
    set_active_working_register_bank(cpu->iram);
  }
}
