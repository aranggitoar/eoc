#ifndef DEVICE_8051AH_H_INCLUDED
#define DEVICE_8051AH_H_INCLUDED

#include <utils.h>
#include <8051ah/memory.h>
#include <8051ah/cpu.h>
#include <8051ah/interface.h>
#include <8051ah/instruction.h>

typedef struct device_8051ah_t {
  cpu_t cpu;
  iram_balt_t iram_balt;
  pin_state_t pin;
} device_8051ah_t;

void init_device_8051ah(device_8051ah_t *device, rom_t *rom);
void run_device_8051ah(device_8051ah_t *device);

#endif /* DEVICE_8051AH_H_INCLUDED */
