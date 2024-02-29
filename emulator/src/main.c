#include <stdio.h>
#include "8051ah/8051ah.h"
#include "8051ah/instruction.h"

int main()
{
  rom_t rom = {};

  cpu_t cpu = *init_cpu(&rom);
  printf("%d\n", cpu.iram->separated.R[0][0]);
  printf("%lu\n", sizeof(cpu.iram->separated));
  printf("%lu\n", sizeof(cpu.iram->compact));
  uint8_t ins[2] = {0b01111111, 0x2A};

  MOV_id_to_r(ins, cpu.iram);

  printf("%d\n", cpu.iram->separated.R[0][7]);
  /* printf("", (cpu.iram->separated.SFR.PSW >> 3) & 0x03); */
  /* PABI((0b00000000 >> 3) & 0x03); */
  /* printf("\n%d\n", (0b00000000 >> 3) & 0x03); */
  /* PABI((0b00001000 >> 3) & 0x03); */
  /* printf("\n%d\n", (0b00001000 >> 3) & 0x03); */
  /* PABI((0b00010000 >> 3) & 0x03); */
  /* printf("\n%d\n", (0b00010000 >> 3) & 0x03); */
  /* PABI((ins[0] >> 3) & 0x03); */
  /* printf("\n%d\n", (ins[0] >> 3) & 0x03); */
  return 0;
}
