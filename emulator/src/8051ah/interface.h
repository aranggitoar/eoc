#include "../utils.h"

#pragma once

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
  bool P10;
  bool P11;
  bool P12;
  bool P13;
  bool P14;
  bool P15;
  bool P16;
  bool P17;
  bool VPD;
  bool P30;
  bool P31;
  bool P32;
  bool P33;
  bool P34;
  bool P35;
  bool P36;
  bool P37;
  bool XTAL2;
  bool XTAL1;
  bool VSS;
  bool P20;
  bool P21;
  bool P22;
  bool P23;
  bool P24;
  bool P25;
  bool P26;
  bool P27;
  bool PSEN;
  bool PROG;
  bool VDD;
  bool P00;
  bool P01;
  bool P02;
  bool P03;
  bool P04;
  bool P05;
  bool P06;
  bool P07;
  bool VCC;
} pin_state_t;
