/* – task synchronization (primitive operations, such as */
/* semaphores, and queues) */
/* – inter-task communication (signals and mailboxes) */
/* – memory management */
/* – Modules: device drivers, file system support, */
/* networking, protocols */

#include <shared/os/scheduler.h>

void tcb_init(tcb_node_t *tcb_node, uint8_t priority, uint16_t register_save) {
  tcb_node_t *top = malloc(sizeof(tcb_node_t));
  uint16_t pid = 0;
  if (tcb_node->next == NULL) {
    tcb_node = top; // TODO: Check if in implementation it needs to be
                       // malloc'd before initialization.
  } else {
    for (tcb_node_t *i = tcb_node; i->next != NULL; i = i->next) pid++;
    top->next = malloc(sizeof(tcb_node_t));
    memcpy(top->next, tcb_node, sizeof(tcb_node_t));
    memcpy(tcb_node, top, sizeof(tcb_node_t));
    tcb_node = top; // TODO: Check if this means the previous
                       // tcb_node has to be freed in this function.
  }
  tcb_node->tcb->pid = pid;
  tcb_node->tcb->priority = priority;
  tcb_node->tcb->state = READY;
  tcb_node->tcb->register_save = register_save;
  tcb_node->tcb->activation_time = 0;
}
