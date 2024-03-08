#include "memory.h"

void init_ram(iram_t *iram)
{
  if (!iram) return;
  iram->separated = (iram_separated_t){
    .SFR = (sfr_t){
      .P0 = 0x00,
      .SP = 0x07,
      .TCON = 0x00,
      .P1 = 0xFF,
      .SCON = 0x00,
      .SBUF = 0x00, // Supposed to be indeterminate.
      .P2 = 0xFF,
      .IE = 0x00, // X's are supposed to be indeterminate 0XX00000B.
      .P3 = 0xFF,
      .IP = 0x00, // X's are supposed to be indeterminate XXX00000B.
      .PSW = 0x00,
      .A = 0x00,
      .B = 0x00
    },
    .BaS = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  };
}

void init_ram_balt(iram_balt_t iram_balt, iram_t *iram)
{
  for (uint8_t i = 0; i < 16; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      iram_balt[i*8+j].ptr = &iram->separated.BaS[i];
      iram_balt[i*8+j].idx = j;
    }
  }
  uint8_t addresses[11] = {
    iram->separated.SFR.P0,
    iram->separated.SFR.TCON,
    iram->separated.SFR.P1,
    iram->separated.SFR.SCON,
    iram->separated.SFR.P2,
    iram->separated.SFR.IE,
    iram->separated.SFR.P3,
    iram->separated.SFR.IP,
    iram->separated.SFR.PSW,
    iram->separated.SFR.A,
    iram->separated.SFR.B,
  };
  for (uint8_t i = 0; i < 11; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      iram_balt[128+i*8+j].ptr = &addresses[i];
      iram_balt[128+i*8+j].idx = j;
    }
  }
}

void init_rom(rom_t *rom, rom_t *custom_rom, bool is_custom)
{
  if (!rom) return;
  if (is_custom) memcpy(rom, custom_rom, sizeof(rom_t));
  // Default ROM instructions:
  //    MOV R7, #2AH    (0, 1) 2AH is 42
  //    SETB C          (2)
  //    MOV 00H, C      (3, 4)
  //    CLR C           (5)
  //    CLR 00H         (6, 7)
  //    SETB 00H        (8, 9)
  //    MOV C, 00H      (10, 11)
  //    MOV A, #18H     (12, 13) 18H is 24
  //    ANL A, R7       (14)
  //    ANL A, 07H      (15, 16)
  //
  //    MOV @R1, #2AH   (17, 18)
  //
  //    ANL A, @R1      (19)
  //    ANL A, #18H     (20, 21) 18H is 24
  //    ANL 00H, A      (22, 23)
  //    ANL 00H, #55H   (24, 25, 26) 55H is 85
  //    LJMP FFFH       (27, 28, 29)
  //    NOP             (4095)
  else memcpy(rom, (rom_t){
      [0] = 0b01111111, [1] = 0b00101010, [2] = 0b11010011,
      [3] = 0b10010010, [4] = 0b00000000, [5] = 0b11000011,
      [6] = 0b11000010, [7] = 0b00000000, [8] = 0b11010010,
      [9] = 0b00000000, [10] = 0b10100010, [11] = 0b00000000,
      [12] = 0b01110100, [13] = 0b0011000, [14] = 0b01011111,
      [15] = 0b01010101, [16] = 0b00000111, [17] = 0b01110111,
      [18] = 0b00101010,

      [19] = 0b01010111, [20] = 0b01010100, [21] = 0b00011000, 
      [22] = 0b01010010, [23] = 0b00000000, [24] = 0b01010011,
      [25] = 0b00000000, [26] = 0b01010101, [27] = 0b00000010,
      [28] = 0b00001111, [29] = 0b11111111,
      [30 ... 4095] = 0x00}, sizeof(rom_t));
}

void init_erom(emem_t *erom, uint16_t limit)
{
}
