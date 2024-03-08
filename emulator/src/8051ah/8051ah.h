#include "../utils.h"
#include "memory.h"
#include "cpu.h"
#include "interface.h"
#include "opcode.h"
#include "instruction.h"

#pragma once

typedef struct device_t {
  cpu_t cpu;
  iram_balt_t iram_balt;
  pin_state_t pin;
} device_t;

void init_device(device_t *device, rom_t *rom);
void run_device(device_t *device);

#define init_8051ah_device(arg) init_device(arg)
#define run_8051ah_device(arg) run_device(arg)
