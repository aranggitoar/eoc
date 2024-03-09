#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include <8051ah/memory.h>

typedef struct cpu_t {
  pc_t pc;
  iram_t iram;
  rom_t rom;
} cpu_t;

#endif /* CPU_H_INCLUDED */
