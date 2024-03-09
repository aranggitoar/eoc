#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <std.h>

// CHeck BIt, Print All BIts, Set BIt, CLear BIt, Toggle BIt.
// Mostly used for reference as it's shorter to type as is.
#define CHBI(b, i) (b >> i) & 1 // i == 0 is little endian LSB
#define PABI(b, sz) for (int i = sz-1; i >= 0; i--) printf(i == 0 ? "%d\n" : "%d ", CHBI(b, i));
#define SBI(b, i) b | 1 << i // i == 0 is little endian MSB
#define CLBI(b, i) b & ~(1 << i) // endianness same as SBI
#define TBI(b, i) b ^ (1 << i) // endianness same as SBI

#endif /* UTILS_H_INCLUDED */
