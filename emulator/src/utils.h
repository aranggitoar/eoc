#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>

#pragma once

#define CHBI(b, i) (b >> i) & 1
#define PABI(b) for (int i = 7; i >= 0; i--) printf("%d ", CHBI(b, i));
#define SBI(b, i) b | 1 << i
#define CLBI(b, i) b & ~(1 << i)
#define TBI(b, i) b ^ (1 << i)
