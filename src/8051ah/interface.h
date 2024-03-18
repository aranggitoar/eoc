#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <utils.h>

// User's manual pg. 114.
typedef struct port_t {
  bool latch;
  bool output_driver;
  bool input_buffer;
} port_t;

typedef enum pin_1d_1st_t {
  P10       = 1,
  P11       = 2,
  P12       = 3,
  P13       = 4,
  P14       = 5,
  P15       = 6,
  P16       = 7,
  P17       = 8,
  VPD       = 9,
  P30       = 10,
  P31       = 11,
  P32       = 12,
  P33       = 13,
  P34       = 14,
  P35       = 15,
  P36       = 16,
  P37       = 17,
  XTAL2     = 18,
  XTAL1     = 19,
  VSS       = 20,
  P20       = 21,
  P21       = 22,
  P22       = 23,
  P23       = 24,
  P24       = 25,
  P25       = 26,
  P26       = 27,
  P27       = 28,
  PSEN      = 29,
  PROG      = 30,
  VDD       = 31,
  P00       = 32,
  P01       = 33,
  P02       = 34,
  P03       = 35,
  P04       = 36,
  P05       = 37,
  P06       = 38,
  P07       = 39,
  VCC       = 40,
} pin_id_1st_t;

typedef enum pin_id_2nd_t {
  RXD       = 10,
  TXD       = 11,
  INT0      = 12,
  INT1      = 13,
  WR        = 16,
  RD        = 17,
  ALE       = 30,
  EA        = 31,
} pin_id_2nd_t;

typedef union pin_id_t {
  pin_id_1st_t pin_1st;
  pin_id_2nd_t pin_2nd;
} pin_id_t;

typedef struct pin_state_t {
  bool n[40];
} pin_state_t;

// Pin related functions.
void connect_external_memory();

#endif /* INTERFACE_H_INCLUDED */
