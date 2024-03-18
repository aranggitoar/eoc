// Exokernel, duplication of Aegis (Engler et al. 1995).
#ifndef KERNEL_H_INCLUDED
#define KERNEL_H_INCLUDED

#include <std.h>
#include <shared/os/scheduler.h>

// Shouldn't be hardcoded, this represents the available program
// memory/ROM either internal or external.
#define BLOCK_SIZE_1K 1024
#define BLOCK_SIZE_2K 2048
#define BLOCK_SIZE_4K 4096
#define BLOCK_SIZE_65K 65536

typedef struct partition_t {
  uint16_t block_start;
  uint16_t block_end;
  uint8_t block_id;
} partition_t;

void yield(uint16_t pid);
void scall(uint16_t pid);
void acall(uint16_t pid);
void alloc(uint16_t pid);
void dealloc(uint16_t pid);

#endif /* KERNEL_H_INCLUDED */
