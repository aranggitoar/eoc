/* #include <stdlib.h> */
#include "register.h"
#include "simd.h"

#define FILL_GPREG(NAME, TYPE) \
static void NAME(A64Register *r, int8_t n, TYPE v) \
{ r->GP[n] = (uint64_t)v; }

#define FILL_SIMDREG(NAME, TYPE) \
static void NAME(A64Register *r, int8_t n, TYPE v) \
{ r->SIMD[0][n] = (uint64_t)v, r->SIMD[1][n] = 0x0000000000000000; }

FILL_GPREG(fill_w_gpreg, uint32_t)
FILL_GPREG(fill_x_gpreg, uint64_t)
FILL_SIMDREG(fill_b_simdreg, uint8_t)
FILL_SIMDREG(fill_h_simdreg, uint16_t)
FILL_SIMDREG(fill_s_simdreg, uint32_t)
FILL_SIMDREG(fill_d_simdreg, uint64_t)

static void fill_q_simdreg(A64Register *r, int8_t n, uint64_t v[2])
{
  r->SIMD[0][n] = (uint64_t)v[0];
  r->SIMD[1][n] = (uint64_t)v[1];
}

static void fill_v8b_simdreg(A64Register *r, int8_t n, V8B v)
{}

/* #define FILL_REGISTER(NAME, TYPE) \ */
/* static void fill_##NAME(A64Register *r, TYPE n) \ */
/* {                                                   \ */
/*   uint64_t value = 0x123456789ABCDEF0; // Example value */
/*   r->GP[0] = value; // Assigning to X0 register */

/*   uint32_t lower_value = 0x12345678; // Example 32-bit value */
/*   r->GP[0] &= 0xFFFFFFFF00000000; // Clear lower 32 bits */
/*   r->GP[0] |= (uint64_t)lower_value; // Set lower 32 bits */
/* } */

/* void LDR(Register *r, register_info src, register_info dest) */
/* { */
/*   r[src.n] = r[dest.n]; */
/* } */
