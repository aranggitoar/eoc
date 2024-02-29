#include "vector.h"

static void join_v8b_to_i64(V8B v, int64_t i)
{
  i = ((uint64_t)v[0] << 56) | ((uint64_t)v[1] << 48) | ((uint64_t)v[2]
      << 40) | ((uint64_t)v[3] << 32) | ((uint64_t)v[4] << 24) |
    ((uint64_t)v[5] << 16) | ((uint64_t)v[6] << 8) | v[7];
}

static void split_i64_to_v8b(int64_t i, V8B v)
{
  v = (V8B){(int8_t)((i >> 56) & 0xFF), (int8_t)((i >> 48) & 0xFF),
    (int8_t)((i >> 40) & 0xFF), (int8_t)((i >> 32) & 0xFF), (int8_t)((i >>
          24) & 0xFF), (int8_t)((i >> 16) & 0xFF), (int8_t)((i >> 8) &
          0xFF), (int8_t)(i & 0xFF)};
}
