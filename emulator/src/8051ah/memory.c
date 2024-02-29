#include "memory.h"
#include "../utils.h"

bwr_t* set_active_working_register_bank(iram_t *iram)
{
  // RS1 is declared as 2 if 1 so that the sum of any combination of RS1
  // and RS0 would be different: (0, 1) = 1; (2 [1], 0) = 2; (2 [1], 1) =
  // 3; (0, 0) = 0.
  uint8_t idx = CHBI(iram->separated.SFR.PSW, 4) ? 2 : 0 + CHBI(iram->separated.SFR.PSW, 3);
  switch (idx) {
    case 1: return &iram->separated.R[1];
    case 2: return &iram->separated.R[2];
    case 3: return &iram->separated.R[3];
    default: return &iram->separated.R[0];
  }
}
