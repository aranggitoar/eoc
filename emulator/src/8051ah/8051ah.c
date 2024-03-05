#include "opcode.h"
#include "instruction.h"
#include "8051ah.h"

void init_device(device_t *device, rom_t *rom)
{
  if (!device) return;
  init_ram(&device->cpu.iram);
  init_rom(&device->cpu.rom, rom, rom == NULL ? false : true);
  device->pin = (pin_state_t){0};
}

void run_device(device_t *device)
{
  if (!device) return;
  while (true) {
    uint8_t ins = device->cpu.rom[device->cpu.pc];
    switch (ins) {
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
      case OP_NOP:
        return;
    }
    device->cpu.pc = device->cpu.pc + 1;
  }
}
