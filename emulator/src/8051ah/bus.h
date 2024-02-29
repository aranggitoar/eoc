#include <stdint.h>

typedef uint16_t rom_bus_t;

typedef struct {
  uint8_t OP : 5;
  uint8_t n : 3;
} register_addressing_t;

typedef struct {
  uint8_t OP;
  uint8_t direct_addr;
} direct_addressing_t;

typedef struct {
  uint8_t OP : 7;
  uint8_t R : 1; // location from R0/R1
} register_indirect_addressing_t;
