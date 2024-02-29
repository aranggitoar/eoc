#include "memory.h"

typedef struct {
  pc_t pc;
  iram_t *iram;
  rom_t *rom;
} cpu_t;

cpu_t* init_cpu(rom_t *rom);
void run_cpu(cpu_t *cpu);

#define rom_8051ah_t rom_t

#define init_8051ah_cpu(arg) init_cpu(arg)
#define free_8051ah_cpu(arg) free_cpu(arg)
