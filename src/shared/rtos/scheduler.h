#ifndef SCHEDULER_H_INCLUDED
#define SCHEDULER_H_INCLUDED

#include <std.h>

typedef enum task_state_t {
  SUSPENDED               = 0,
  READY                   = 1,
  RUNNING                 = 2,
} task_state_t;

// Basically a "thread" in a general purpose OS.
typedef struct task_control_block_t {
  uint16_t                pid;
  uint8_t                 priority;
  task_state_t            state;
  uint16_t                register_save; // Where data is stored on suspension.
  time_t                  activation_time;
} task_control_block_t;

typedef struct tcb_node_t {
  task_control_block_t    *tcb;
  struct tcb_node_t      *next;
} tcb_node_t;

void tcb_init(tcb_node_t *tcb_node, uint8_t priority, uint16_t register_save);

#endif /* SCHEDULER_H_INCLUDED */
