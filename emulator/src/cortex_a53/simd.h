#include <stdint.h>
// Vector registers Vn.8B, Vn.16B, Vn.4H, Vn.8H, Vn.2S, Vn.4S, Vn.1D,
// Vn.2D is of shape 8x8, 8x16, 16x4, 16x8, 32x2, 32x4, 64x1, 64x2 bits

#define V8B_LANES 8
#define V16B_LANES 16
#define V4H_LANES 4
#define V8H_LANES 8
#define V2S_LANES 2
#define V4S_LANES 4
#define V1D_LANES 1
#define V2D_LANES 2

typedef uint8_t v8b_t[V8B_LANES];
typedef uint8_t v16b_t[V16B_LANES];
typedef uint16_t v4h_t[V4H_LANES];
typedef uint16_t v8h_t[V8H_LANES];
typedef uint32_t v2s_t[V2S_LANES];
typedef uint32_t v4s_t[V4S_LANES];
typedef uint64_t v1d_t[V1D_LANES];
typedef uint64_t v2d_t[V2D_LANES];
