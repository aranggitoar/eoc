#include "../utils.h"
#include "memory.h"
#include "cpu.h"
#include "interface.h"

#pragma once

typedef struct device_t {
  cpu_t cpu;
  pin_state_t pin;
} device_t;

void init_device(device_t *device, rom_t *rom);
void run_device(device_t *device);

#define init_8051ah_cpu(arg) init_cpu(arg)
#define run_8051ah_cpu(arg) run_cpu(arg)
