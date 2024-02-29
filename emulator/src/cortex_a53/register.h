#include <stdint.h>
#include <stdbool.h>

typedef struct {
  /** Stack pointer register. **/
  // For both WSP of 32 bits and SP of 64 bits.
  // WSP are simply the bottom 32 bits.
  uint64_t SP;
  /** General purpose (GP) registers. **/
  // Wn registers are simply the bottom 32 bits and Xn are all 64 bits.
  // The last registers are WZR/XZR, zero registers.
  uint64_t GP[32];
  /** SIMD floating-point scalar and vector registers. **/
  // Scalar register Bn, Hn, Sn, and Dn are simply the bottom 8, 16, 32,
  // and 64 bits respectively, then Qn are the whole 128 bits.
  // Vector registers Vn.8B, Vn.16B, Vn.4H, Vn.8H, Vn.2S, Vn.4S, Vn.1D,
  // Vn.2D is of shape 8x8, 8x16, 16x4, 16x8, 32x2, 32x4, 64x1, 64x2 bits
  // and lanes respectively.
  // Vector registers with element index would be Vn.B[i], Vn.H[i],
  // Vn.S[i], and Vn.D[i] of size 8, 16, 32, and 64 bits respectively.
  uint64_t SIMD[2][31];
} a64_register_t;

typedef struct {
  bool isW;
  bool isX;
  int8_t n;
} a64_gp_reginfo;

typedef struct {
  bool isB;
  bool isH;
  bool isS;
  bool isD;
  int8_t n;
} a64_simd_reginfo;

/* void LDR(Register *r, register_info src, register_info dest); */
