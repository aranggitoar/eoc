#include "memory.h"

#pragma once

typedef struct cpu_t {
  pc_t pc;
  iram_t iram;
  rom_t rom;
} cpu_t;
