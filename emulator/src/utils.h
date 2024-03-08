#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#pragma once

// Check a bit, print all bits, set a bit, clear a bit, toggle a bit.
// Mostly used for reference as it's shorter to type as is.
#define CHBI(b, i) (b >> i) & 1 // i == 0 is little endian LSB
#define PABI(b, sz) for (int i = sz-1; i >= 0; i--) printf(i == 0 ? "%d\n" : "%d ", CHBI(b, i));
#define SBI(b, i) b | 1 << i // i == 0 is little endian MSB
#define CLBI(b, i) b & ~(1 << i) // endianness same as SBI
#define TBI(b, i) b ^ (1 << i) // endianness same as SBI
