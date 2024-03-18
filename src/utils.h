#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <std.h>

// Mostly used for reference as it's shorter to type as is.
// Written as #define so it accepts any number type.
#define CHECK_BIT(b, i) (b >> i) & 1 // i == 0 is little endian LSB
#define PRINT_ALL_BITS(b, sz) for (int i = sz-1; i >= 0; i--) printf(i == 0 ? "%d\n" : "%d ", CHECK_BIT(b, i));
#define SET_BIT(b, i) b | 1 << i // i == 0 is little endian MSB
#define CLEAR_BIT(b, i) b & ~(1 << i) // endianness same as SBI
#define TOGGLE_BIT(b, i) b ^ (1 << i) // endianness same as SBI

#endif /* UTILS_H_INCLUDED */
