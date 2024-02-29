#include <stdint.h>
#include <stdlib.h>

typedef struct {
  uint8_t *memory;
  size_t size;
} memory_t;

typedef char l1_cache_8kb_t[64][125];
typedef char l1_cache_16kb_t[64][250];
typedef char l1_cache_32kb_t[64][500];
typedef char l1_cache_64kb_t[64][1000];

typedef char l2_cache_128kb_t[64][2000];
typedef char l2_cache_256kb_t[64][4000];
typedef char l2_cache_512kb_t[64][8000];
typedef char l2_cache_1mb_t[64][16000];
typedef char l2_cache_2mb_t[64][32000];
