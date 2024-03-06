#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#pragma once

#define CHBI(b, i) (b >> i) & 1
#define PABI(b, sz) for (int i = sz-1; i >= 0; i--) printf(i == 0 ? "%d\n" : "%d ", CHBI(b, i));
#define SBI(b, i) b | 1 << i
#define CLBI(b, i) b & ~(1 << i)
#define TBI(b, i) b ^ (1 << i)
