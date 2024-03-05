#include "memory.h"

void init_ram(iram_t *iram) {
  if (!iram) return;
  iram->separated = (iram_separated_t){
    .SFR = (sfr_t){
      .SP = 0x07,
      .P1 = 0xFF,
      .SBUF = 0x00, // Supposed to be indeterminate.
      .P2 = 0xFF,
      .IE = 0x00, // X's are supposed to be indeterminate 0XX00000B.
      .P3 = 0xFF,
      .IP = 0x00, // X's are supposed to be indeterminate XXX00000B.
    }
  };
}

void init_rom(rom_t *rom, rom_t *custom_rom, bool is_custom) {
  if (!rom) return;
  if (is_custom) memcpy(rom, custom_rom, sizeof(rom_t));
  else memcpy(rom, (rom_t){[0] = 0b01111111, [1] = 0b00101010, [2 ... 4095] = 0x00}, sizeof(rom_t));
}
