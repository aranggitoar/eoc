#include "../utils.h"

#pragma once

// Amount of 8 bit blocks.
#define IRAM_SIZE 148
#define ROM_SIZE 4096
#define EMEM_SIZE 65536
#define EMEM_64K_LIMIT EMEM_SIZE
#define EMEM_32K_LIMIT 32768
#define EMEM_16K_LIMIT 16384
#define EMEM_8K_LIMIT 8192

/** Register Addresses **/
// Blocks of registers are addressed with 's' and 'e' at the end of the
// name to indicate 'start' and 'end' of the block. Bit-addressable
// registers are commented with 'BA'.
// NOTE: Doesn't seem to be functionally necessary, remove?
typedef enum mmap_t {
  R_B0s   = 0x00,
  R_B0e   = 0x07,
  R_B1s   = 0x08,
  R_B1e   = 0x0F,
  R_B2s   = 0x10,
  R_B2e   = 0x17,
  R_B3s   = 0x18,
  R_B3e   = 0x1F,
  BaSs    = 0x20, // BA   0
  BaSe    = 0x2F, // BA   127
  GPs     = 0x30,
  GPe     = 0x7F,
  P0      = 0x80, // BA   128-136
  SP      = 0x81,
  DPL     = 0x81,
  DPH     = 0x82,
  TCON    = 0x88, // BA   137-144
  TMOD    = 0x89,
  TL0     = 0x8A,
  TL1     = 0x8B,
  TH0     = 0x8C,
  TH1     = 0x8D,
  P1      = 0x90, // BA   145-152
  SCON    = 0x98, // BA   153-160
  SBUF    = 0x99,
  P2      = 0xA0, // BA   161-168
  IE      = 0xA8, // BA   169-176
  P3      = 0xB0, // BA   177-184
  IP      = 0xB8, // BA   185-192
  PSW     = 0xD0, // BA   193-200
  A       = 0xE0, // BA   201-208
  B       = 0xF0  // BA   209-216
} mmap_t;

// Bit-addressable addresses for lookup table.
// NOTE: Doesn't seem to be functionally necessary, remove?
typedef enum mmap_ba_t {
  BaSs_ba   = 0x00, // 0
  BaSe_ba   = 0x7F, // 127
  P0s_ba    = 0x80, // 128
  P0e_ba    = 0x88, // 136
  TCONs_ba  = 0x89, // 137
  TCONe_ba  = 0x90, // 144
  P1s_ba    = 0x91, // 145
  P1e_ba    = 0x98, // 152
  SCONs_ba  = 0x99, // 153
  SCONe_ba  = 0xA0, // 160
  P2s_ba    = 0xA1, // 161
  P2e_ba    = 0xA8, // 168
  IEs_ba    = 0xA9, // 169
  IEe_ba    = 0xB0, // 176
  P3s_ba    = 0xB1, // 177
  P3e_ba    = 0xB8, // 184
  IPs_ba    = 0xB9, // 185
  IPe_ba    = 0xC0, // 192
  PSWs_ba   = 0xC1, // 193
  PSWe_ba   = 0xC8, // 200
  As_ba     = 0xC9, // 201
  Ae_ba     = 0xD0, // 208
  Bs_ba     = 0xD1, // 209
  Be_ba     = 0xD8, // 216
} mmap_ba_t;

// Bit-address lookup table.
typedef struct balt_single_t {
  uint8_t *ptr;
  uint8_t idx;
} balt_single_t;
typedef balt_single_t iram_balt_t[216];

/** Program Counter **/
// Separate from IRAM.
// TODO: Decide whether to use a union of x2 uint8_t and x1 uint16_t or
// simply x1 uint16_t.
/* typedef uint8_t pc_8b_t[2]; */
typedef uint16_t pc_t;
/* typedef union pc_t { */
/*   pc_8b_t halfs; */
/*   pc_16b_t full; */
/* } pc_t; */

/** Bank of Working Registers **/
// x4 @ 0-31
typedef uint8_t bwr_t[8];

/** 128 Bit-addressable Space **/
// x1 @ 32-47
typedef uint8_t bas_t[16];

/** x80 8-bit General Purpose Registers **/
// x1 @ 48-127
typedef uint8_t gp_t[80];

/** Data Pointer **/
// Low x1 @ 130 & High x1 @ 131
typedef struct dptr_8b_t {
  uint8_t DPL;
  uint8_t DPH;
} dptr_8b_t;
typedef uint16_t dptr_16b_t;
typedef union dptr_t {
  dptr_8b_t halfs;
  dptr_16b_t full;
} dptr_t;


/** Timer/Counter Control/Status Register **/
// x1 @ 136 - bit-addressable
// TODO: Add details.
typedef uint8_t tcon_t;

/** Timer/Counter Mode Register **/
// x1 @ 137
// 7: GATE  Gating control. When set timer/counter "x" is enabled only
//          while "INTx" pin is high and "TRx" control bit is set. When
//          cleared, timer/counter is enabled whenever control bit is set.
// 6: C/T   Timer or Counter selector. Cleared for Timer operation (input
//          from internal system clock). Set for Counter operation (input
//          from "Tx" input pin).
typedef uint8_t tmod_t;

/** Serial Port Control **/
// x1 @ 152 - bit-addressable
// TODO: Add details.
typedef uint8_t scon_t;

/** Serial Port Data Buffer **/
// x1 @ 153
// Becomes a transmit buffer if a byte is moved into it, or a receive
// buffer if a byte is moved out of it.
typedef uint8_t sbuf_t;

/** Interrupt Enable **/
// x1 @ 168 - bit-addressable
// 7: EA    Enable All control bit. Cleared by software to disable all
//          interrupts, independent of 0-4.
// 6: -     reserved
// 5: -     reserved
// 4: ES    Enable Serial port control bit. For software to enable
//          interrupts from TI or RI flags.
// 3: ET1   Same as above, but for timer/counter 1.
// 2: EX1   Same as above, but for INT1.
// 1: ET0   Same as above, but for timer/counter 0.
// 0: EX0   Same as above, but for INT0.
typedef uint8_t ie_t;

/** Port (0 - 3) **/
// x4 @ 128, 144, 160, 176 - bit-addressable
// All ports consists of a latch, an output driver, and an input buffer.
// External memory accesses are handled by the output drivers and input
// buffers of P0 and P2, where on 16-bit addresses, P2 are the high byte.
// Port 3 are multifunctional, each 8 bit has different functions.
// 7: RD    read data control output. Active low pulse is generated by
//          hardware when external data memory is read.
// 6: WR    write data control output. Active low pulse is generated by
//          hardware when external data memory is written.
// 5: T1    timer/counter 1 external input or test pin.
// 4: T0    timer/counter 0 external input or test pin.
// 3: INT1  interrupt 1 input pin. Low-level or falling-edge triggered.
// 2: INT0  interrupt 0 input pin. Low-level or falling-edge triggered.
// 1: TXD   transmit Data pin for serial port in UART mode. Clock output in
//          shift register mode.
// 0: RXD   receive Data pin for serial port in UART mode. Data I/O pin in
//          shift register mode.
typedef uint8_t px_t;

/** Stack Pointer **/
// x1 @ 129
// Incremented before data is stored during PUSH and CALL executions, the
// stack may reside anywhere in on-chip RAM, but always initialized to
// 0x07 after reset, so the stack always begins at 0x08.
typedef uint8_t sp_t;

/** Interrupt Priority **/
// x1 @ 184 - bit-addressable
// 7: -     reserved
// 6: -     reserved
// 5: -     reserved
// 4: PS    Serial port Priority control bit. For software to specify
//          high/low priority interrupts for Serial port.
// 3: PT1   Same as above, but for timer/counter 1.
// 2: PX1   Same as above, but for INT1.
// 1: PT0   Same as above, but for timer/counter 0.
// 0: PX0   Same as above, but for INT0.
typedef uint8_t ip_t;

/** Program Status Word **/
// x1 @ 208
// Each 8 bit has different functions.
// 7: CY    carry flag set/cleared by hardware/software during certain
//          arithmetic and logical instructions.
// 6: AC    auxilliary carry flag set/cleared by hardware during add/sub
//          instructions to indicate carry/borrow out of bit 3.
// 5: F0    user-defined status flag.
// 4: RS1   working register bank control 1 by software.
//          (RS1: 0, RS0: 0), Bank 0 @ 0-7;   (RS1: 0, RS0: 1), Bank 1 @ 8-15;
//          (RS1: 1, RS0: 0), Bank 2 @ 16-23; (RS1: 1, RS0: 1), Bank 3 @ 24-31;
// 3: RS0   working register bank control 0 by software.
// 2: OV    set/cleared by hardware during arithmetic instructions to
//          indicate overflow conditions.
// 1: -     user-defined status flag.
// 0: P     set/cleared by hardware each instruction cycle to indicate an
//          odd/even number of "one" bits in the accumulator, i.e. even
//          parity.
typedef uint8_t psw_t;

/** Accumulator **/
// x1 @ 224
// Holds source and result of arithmetic instructions, be source or
// destination for logical operations.
typedef uint8_t a_t;

/** B **/
// x1 @ 240
// Used in conjunction with the accumulator as the second input operand
// and to return bits of the result in multiplication and division.
typedef uint8_t b_t;

/** Special Function Registers **/
// Accessible through direct addressing and simply calling the symbols.
// It is part of IRAM conceptually in MCS-51s with 128 x 8 bits of IRAM
// memory, but part of IRAM literally in MCS-51s with 256 x 8 bits of IRAM
// memory in the same space as the upper 128 x 8 bits.
// TODO: Create types for each register and write any documentations their
// function there.
typedef struct sfr_t {
  px_t P0;
  sp_t SP;
  dptr_t DPTR;
  tcon_t TCON;
  tmod_t TMOD;
  uint8_t TL0;    // (138) Timer 0 Low byte
  uint8_t TL1;    // (139) Timer 1 Low byte
  uint8_t TH0;    // (140) Timer 0 High byte
  uint8_t TH1;    // (141) Timer 1 High byte
  px_t P1;
  scon_t SCON;
  sbuf_t SBUF;
  px_t P2;
  ie_t IE;
  px_t P3;
  ip_t IP;
  psw_t PSW;
  a_t A;
  b_t B;
} sfr_t;

/** IRAM (Separated) **/
// Except SFR are accessible through direct/indirect addressing.
typedef struct iram_separated_t {
  bwr_t R[4];
  bas_t BaS;
  gp_t GP;
  sfr_t SFR;
} iram_separated_t;

/** IRAM (Compact) **/
// 128 x 8 bits for all register banks, bit-addressable space, and general
// purpose registers, 20 x 8 bits for all SFRs.
typedef uint8_t iram_compact_t[IRAM_SIZE];

// Type punning IRAM for both closer resemblance of the actual device and
// ease of usage.
typedef union iram_t {
  iram_separated_t separated;
  iram_compact_t compact;
} iram_t;

/** ROM (Program Memory) **/
// 4096 x 8 bits on chip.
typedef uint8_t rom_t[ROM_SIZE];

/** Interrupt Source Service Routine Addresses **/
// In the style of IE and IP, it's called IS for interrupt source.
typedef enum rom_issra_t {
  SX0 = 0x03,
  ST0 = 0x0B,
  SX1 = 0x13,
  ST1 = 0x1B,
  SS  = 0x23,
} rom_issra_t;

/** External RAM and ROM **/
// Max addressability of 64 kilobytes.
typedef uint8_t emem_t[EMEM_SIZE];

void init_ram(iram_t *iram);
void init_ram_balt(iram_balt_t iram_balt, iram_t *iram);

void init_rom(rom_t *rom, rom_t *custom_rom, bool is_custom);
uint8_t* read_rom(rom_t *rom, uint8_t addr);
void init_erom(emem_t *erom, uint16_t limit);
