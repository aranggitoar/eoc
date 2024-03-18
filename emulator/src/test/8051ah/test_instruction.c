#include <8051ah/instruction.h>
#include <8051ah/8051ah.h>
#include <test/test_utils.h>

device_8051ah_t device;

void set_up(uint8_t a, uint8_t b, uint8_t c)
{
  rom_t rom = {[0] = a, [1] = b, [2] = c, [3 ... 4095] = 0x00};
  init_device_8051ah(&device, &rom);
  device.cpu.pc = 0;
}

void tear_down()
{
  device = (device_8051ah_t){0};
}

void test_AJMP()
{
  set_up(0b11100001, 0b00000001, 0x00);
  AJMP(device.cpu.rom[device.cpu.pc], &device.cpu); 
  assert_equal_uint16(0b0000011100000001, device.cpu.pc, __func__);
  tear_down();
}

void test_LJMP()
{
  set_up(0b00000010, 0b00001111, 0b11111111);
  LJMP(&device.cpu); 
  assert_equal_uint8(0b11111111, device.cpu.pc, __func__);
  tear_down();
}

void test_RR()
{
  set_up(0b00000011, 0x00, 0x00);
  device.cpu.iram.separated.SFR.A = 0b11010100;
  RR(&device.cpu); 
  assert_equal_uint8(0b01101010, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_INC_a()
{
  set_up(0b00000100, 0x00, 0x00);
  INC_a(&device.cpu);
  assert_equal_uint8(0x01, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_INC_db()
{
  set_up(0b00000101, 0x04, 0x00);
  INC_db(&device.cpu);
  assert_equal_uint8(0x01, device.cpu.iram.compact[0x04], __func__);
  tear_down();
}

void test_INC_ir()
{
  set_up(0b00000111, 0x00, 0x00);
  INC_ir(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(0x01, device.cpu.iram.separated.R[0][1], __func__);
  tear_down();
}

void test_INC_r()
{
  set_up(0b00001111, 0x00, 0x00);
  INC_r(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(0x01, device.cpu.iram.separated.R[0][7], __func__);
  tear_down();
}

void test_JBC()
{
  set_up(0b00010000, 0b11000000, 0b00101010);
  device.cpu.pc = device.cpu.pc + 1;
  balt_single_t addr = device.iram_balt[device.cpu.rom[device.cpu.pc]];
  *addr.ptr |= 1 << addr.idx;
  JBC(addr, &device.cpu, 1);
  assert_equal_uint8(0b00101101, device.cpu.pc, "test_JBC (PC)");
  assert_equal_uint8(0b00000000, *addr.ptr, "test_JBC (bit state)");
  tear_down();
}

void test_ACALL()
{
  set_up(0x00, 0x00, 0x00);
  device.cpu.pc = 0b0000100000000000;
  device.cpu.rom[device.cpu.pc] = 0b11110001;
  device.cpu.rom[device.cpu.pc + 1] = 0b00000001;
  ACALL(device.cpu.rom[device.cpu.pc], &device.cpu); 
  assert_equal_uint16(0b0000111100000001, device.cpu.pc, "test_ACALL (PC)");
  assert_equal_uint8(0b00001000,
      device.cpu.iram.compact[device.cpu.iram.separated.SFR.SP],
      "test_ACALL (pointed stack content)");
  tear_down();
}

void test_LCALL()
{
  set_up(0x00, 0x00, 0x00);
  device.cpu.pc = 0b0000100000000000;
  device.cpu.rom[device.cpu.pc + 1] = 0b00001110;
  device.cpu.rom[device.cpu.pc + 2] = 0b10101000;
  LCALL(&device.cpu); 
  assert_equal_uint16(0b0000111010101000, device.cpu.pc, "test_LCALL (PC)");
  assert_equal_uint8(0b00001000,
      device.cpu.iram.compact[device.cpu.iram.separated.SFR.SP],
      "test_LCALL (pointed stack content)");
  tear_down();
}

void test_RRC()
{
  set_up(0b00010011, 0x00, 0x00);
  device.cpu.iram.separated.SFR.A = 0b11010100;
  device.cpu.iram.separated.SFR.PSW = 0b10000000;
  RRC(&device.cpu); 
  assert_equal_uint8(0b11101010, device.cpu.iram.separated.SFR.A, "test_RRC (A)");
  assert_equal_uint8(0b00000000, device.cpu.iram.separated.SFR.PSW, "test_RRC (carry)");
  tear_down();
}

void test_DEC_a()
{
  set_up(0b00000100, 0x00, 0x00);
  device.cpu.iram.separated.SFR.A = 0x02;
  DEC_a(&device.cpu);
  assert_equal_uint8(0x01, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_DEC_db()
{
  set_up(0b00000101, 0x04, 0x00);
  device.cpu.iram.compact[0x04] = 0x02;
  DEC_db(&device.cpu);
  assert_equal_uint8(0x01, device.cpu.iram.compact[0x04], __func__);
  tear_down();
}

void test_DEC_ir()
{
  set_up(0b00000111, 0x00, 0x00);
  device.cpu.iram.separated.R[0][1] = 0x02;
  DEC_ir(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(0x01, device.cpu.iram.separated.R[0][1], __func__);
  tear_down();
}

void test_DEC_r()
{
  set_up(0b00001111, 0x00, 0x00);
  device.cpu.iram.separated.R[0][7] = 0x02;
  DEC_r(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(0x01, device.cpu.iram.separated.R[0][7], __func__);
  tear_down();
}

void test_JB()
{
  set_up(0b00100000, 0b11000000, 0b00101010);
  device.cpu.pc = device.cpu.pc + 1;
  balt_single_t addr = device.iram_balt[device.cpu.rom[device.cpu.pc]];
  *addr.ptr |= 1 << addr.idx;
  JBC(addr, &device.cpu, 1);
  assert_equal_uint8(0b00101101, device.cpu.pc, __func__);
  tear_down();
}

void test_RET()
{
  set_up(0b00100010, 0x00, 0x00);
  device.cpu.iram.separated.SFR.SP = device.cpu.iram.separated.SFR.SP + 2;
  device.cpu.iram.compact[device.cpu.iram.separated.SFR.SP] = 0b00101101;
  device.cpu.iram.compact[device.cpu.iram.separated.SFR.SP-1] = 0b00010000;
  RET(&device.cpu);
  assert_equal_uint16(0b0001000000101101, device.cpu.pc, __func__);
  tear_down();
}

void test_RL()
{
  set_up(0b00100011, 0x00, 0x00);
  device.cpu.iram.separated.SFR.A = 0b11010100;
  RL(&device.cpu); 
  assert_equal_uint8(0b10101001, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_ADD_id()
{
  set_up(0b00100100, 0x01, 0b00010100);
  device.cpu.iram.separated.SFR.A = 0b11111100;
  ADD_id(&device.cpu);
  assert_equal_uint8(0b11111101, device.cpu.iram.separated.SFR.A, "test_ADD_id (result)");
  ADD_id(&device.cpu);
  assert_equal_uint8(0b00000100, device.cpu.iram.separated.SFR.PSW & 0b00000100, "test_ADD_id (OV)");
  assert_equal_uint8(0b01000000, device.cpu.iram.separated.SFR.PSW & 0b01000000, "test_ADD_id (auxiliary carry)");
  assert_equal_uint8(0b10000000, device.cpu.iram.separated.SFR.PSW & 0b10000000, "test_ADD_id (carry)");
}

void test_ADD_db()
{
  set_up(0b00100101, 0x03, 0x03);
  device.cpu.iram.separated.SFR.A = 0b11111100;
  device.cpu.iram.separated.R[0][3] = 0b00000001;
  ADD_db(&device.cpu);
  assert_equal_uint8(0b11111101, device.cpu.iram.separated.SFR.A, "test_ADD_db (result)");
  device.cpu.iram.separated.R[0][3] = 0b00010100;
  ADD_db(&device.cpu);
  assert_equal_uint8(0b00000100, device.cpu.iram.separated.SFR.PSW & 0b00000100, "test_ADD_db (OV)");
  assert_equal_uint8(0b01000000, device.cpu.iram.separated.SFR.PSW & 0b01000000, "test_ADD_db (auxiliary carry)");
  assert_equal_uint8(0b10000000, device.cpu.iram.separated.SFR.PSW & 0b10000000, "test_ADD_db (carry)");
}

void test_ADD_ir()
{
  set_up(0b00100111, 0b00100111, 0x00);
  device.cpu.iram.separated.SFR.A = 0b11111100;
  device.cpu.iram.separated.R[0][1] = 0b00000001;
  ADD_ir(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(0b11111101, device.cpu.iram.separated.SFR.A, "test_ADD_ir (result)");
  device.cpu.iram.separated.R[0][1] = 0b00010100;
  ADD_ir(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(0b00000100, device.cpu.iram.separated.SFR.PSW & 0b00000100, "test_ADD_ir (OV)");
  assert_equal_uint8(0b01000000, device.cpu.iram.separated.SFR.PSW & 0b01000000, "test_ADD_ir (auxiliary carry)");
  assert_equal_uint8(0b10000000, device.cpu.iram.separated.SFR.PSW & 0b10000000, "test_ADD_ir (carry)");
}

void test_ADD_r()
{
}

void test_RLC()
{
  set_up(0b00110011, 0x00, 0x00);
  device.cpu.iram.separated.SFR.A = 0b11010101;
  device.cpu.iram.separated.SFR.PSW = 0b00000000;
  RLC(&device.cpu); 
  assert_equal_uint8(0b10101010, device.cpu.iram.separated.SFR.A, "test_RLC (A)");
  assert_equal_uint8(0b10000000, device.cpu.iram.separated.SFR.PSW, "test_RLC (carry)");
  tear_down();
}

void test_ORL_a_to_db()
{
  set_up(0b01000010, 0x04, 0x00);
  device.cpu.iram.separated.SFR.A = 0b11110000;
  device.cpu.iram.separated.R[0][4] = 0b10101010;
  ORL_a_to_db(&device.cpu);
  assert_equal_uint8(0b11111010, device.cpu.iram.separated.R[0][4], __func__);
  tear_down();
}

void test_ORL_id_to_db()
{
  set_up(0b01000011, 0x04, 0b11110000);
  device.cpu.iram.separated.R[0][4] = 0b10101010;
  ORL_id_to_db(&device.cpu);
  assert_equal_uint8(0b11111010, device.cpu.iram.separated.R[0][4], __func__);
  tear_down();
}

void test_ORL_id_to_a()
{
  set_up(0b01000100, 0b11110000, 0x00);
  device.cpu.iram.separated.SFR.A = 0b10101010;
  ORL_id_to_a(&device.cpu);
  assert_equal_uint8(0b11111010, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_ORL_db_to_a()
{
  set_up(0b01000101, 0x04, 0x00);
  device.cpu.iram.separated.R[0][4] = 0b11110000;
  device.cpu.iram.separated.SFR.A = 0b10101010;
  ORL_db_to_a(&device.cpu);
  assert_equal_uint8(0b11111010, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_ORL_ir_to_a()
{
  set_up(0b01000111, 0x00, 0x00);
  device.cpu.iram.separated.R[0][1] = 0b11110000;
  device.cpu.iram.separated.SFR.A = 0b10101010;
  ORL_ir_to_a(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(0b11111010, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_ORL_r_to_a()
{
  set_up(0b01001111, 0x00, 0x00);
  device.cpu.iram.separated.R[0][7] = 0b11110000;
  device.cpu.iram.separated.SFR.A = 0b10101010;
  ORL_r_to_a(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(0b11111010, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_ANL_a_to_db()
{
  set_up(0b01010010, 0x04, 0x00);
  device.cpu.iram.separated.SFR.A = 0b11110000;
  device.cpu.iram.separated.R[0][4] = 0b10101010;
  ANL_a_to_db(&device.cpu);
  assert_equal_uint8(0b10100000, device.cpu.iram.separated.R[0][4], __func__);
  tear_down();
}

void test_ANL_id_to_db()
{
  set_up(0b01010011, 0x04, 0b11110000);
  device.cpu.iram.separated.R[0][4] = 0b10101010;
  ANL_id_to_db(&device.cpu);
  assert_equal_uint8(0b10100000, device.cpu.iram.separated.R[0][4], __func__);
  tear_down();
}

void test_ANL_id_to_a()
{
  set_up(0b01010100, 0b11110000, 0x00);
  device.cpu.iram.separated.SFR.A = 0b10101010;
  ANL_id_to_a(&device.cpu);
  assert_equal_uint8(0b10100000, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_ANL_db_to_a()
{
  set_up(0b01010101, 0x04, 0x00);
  device.cpu.iram.separated.R[0][4] = 0b11110000;
  device.cpu.iram.separated.SFR.A = 0b10101010;
  ANL_db_to_a(&device.cpu);
  assert_equal_uint8(0b10100000, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_ANL_ir_to_a()
{
  set_up(0b01010111, 0x00, 0x00);
  device.cpu.iram.separated.R[0][1] = 0b11110000;
  device.cpu.iram.separated.SFR.A = 0b10101010;
  ANL_ir_to_a(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(0b10100000, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_ANL_r_to_a()
{
  set_up(0b01011111, 0x00, 0x00);
  device.cpu.iram.separated.R[0][7] = 0b11110000;
  device.cpu.iram.separated.SFR.A = 0b10101010;
  ANL_r_to_a(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(0b10100000, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_XRL_a_to_db()
{
  set_up(0b01100010, 0x04, 0x00);
  device.cpu.iram.separated.SFR.A = 0b11110000;
  device.cpu.iram.separated.R[0][4] = 0b10101010;
  XRL_a_to_db(&device.cpu);
  assert_equal_uint8(0b01011010, device.cpu.iram.separated.R[0][4], __func__);
  tear_down();
}

void test_XRL_id_to_db()
{
  set_up(0b01100011, 0x04, 0b11110000);
  device.cpu.iram.separated.R[0][4] = 0b10101010;
  XRL_id_to_db(&device.cpu);
  assert_equal_uint8(0b01011010, device.cpu.iram.separated.R[0][4], __func__);
  tear_down();
}

void test_XRL_id_to_a()
{
  set_up(0b01100100, 0b11110000, 0x00);
  device.cpu.iram.separated.SFR.A = 0b10101010;
  XRL_id_to_a(&device.cpu);
  assert_equal_uint8(0b01011010, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_XRL_db_to_a()
{
  set_up(0b01100101, 0x04, 0x00);
  device.cpu.iram.separated.R[0][4] = 0b11110000;
  device.cpu.iram.separated.SFR.A = 0b10101010;
  XRL_db_to_a(&device.cpu);
  assert_equal_uint8(0b01011010, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_XRL_ir_to_a()
{
  set_up(0b01100111, 0x00, 0x00);
  device.cpu.iram.separated.R[0][1] = 0b11110000;
  device.cpu.iram.separated.SFR.A = 0b10101010;
  XRL_ir_to_a(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(0b01011010, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_XRL_r_to_a()
{
  set_up(0b01101111, 0x00, 0x00);
  device.cpu.iram.separated.R[0][7] = 0b11110000;
  device.cpu.iram.separated.SFR.A = 0b10101010;
  XRL_r_to_a(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(0b01011010, device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_MOV_id_to_a()
{
  set_up(0b01110100, 0b00110000, 0x00);
  MOV_id_to_a(&device.cpu);
  assert_equal_uint8(device.cpu.rom[device.cpu.pc], device.cpu.iram.separated.SFR.A, __func__);
  tear_down();
}

void test_MOV_id_to_ir()
{
  set_up(0b01110111, 0b00101010, 0x00);
  MOV_id_to_ir(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(device.cpu.rom[device.cpu.pc], device.cpu.iram.separated.R[0][1], __func__);
  tear_down();
}

void test_MOV_id_to_r()
{
  set_up(0b01111111, 0b00101010, 0x00);
  MOV_id_to_r(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(device.cpu.rom[device.cpu.pc], device.cpu.iram.separated.R[0][7], __func__);
  tear_down();
}

void test_MOV_c_to_dbi()
{
  set_up(0b10010010, 0b00000000, 0x00);
  device.cpu.iram.separated.SFR.PSW = 0b10000000;
  device.cpu.pc = device.cpu.pc + 1;
  MOV_c_to_dbi(device.iram_balt[device.cpu.rom[device.cpu.pc]], &device.cpu);
  assert_equal_uint8(0b00000001, device.cpu.iram.separated.BaS[0], __func__);
  tear_down();
}

void test_MOV_dbi_to_c()
{
  set_up(0b10100010, 0b00000000, 0x00);
  device.cpu.iram.separated.BaS[0] = 0b00000001;
  device.cpu.pc = device.cpu.pc + 1;
  MOV_dbi_to_c(device.iram_balt[device.cpu.rom[device.cpu.pc]], &device.cpu);
  assert_equal_uint8(0b10000000, device.cpu.iram.separated.SFR.PSW, __func__);
  tear_down();
}

void test_CLR_dbi()
{
  set_up(0b11000010, 0x00, 0x00);
  device.cpu.iram.separated.BaS[0] = 0b00000001;
  device.cpu.pc = device.cpu.pc + 1;
  CLR_dbi(device.iram_balt[device.cpu.rom[device.cpu.pc]]);
  assert_equal_uint8(0b00000000, device.cpu.iram.separated.BaS[0], __func__);
  tear_down();
}

void test_CLR_c()
{
  set_up(0b11000011, 0x00, 0x00);
  device.cpu.iram.separated.SFR.PSW = 0b10000000;
  CLR_c(&device.cpu);
  assert_equal_uint8(0b00000000, device.cpu.iram.separated.SFR.PSW, __func__);
  tear_down();
}

void test_SETB_dbi()
{
  set_up(0b11010010, 0x00, 0x00);
  device.cpu.pc = device.cpu.pc + 1;
  SETB_dbi(device.iram_balt[device.cpu.rom[device.cpu.pc]]);
  assert_equal_uint8(0b00000001, device.cpu.iram.separated.BaS[0], __func__);
  tear_down();
}

void test_SETB_c()
{
  set_up(0b11010011, 0x00, 0x00);
  SETB_c(&device.cpu);
  assert_equal_uint8(0b10000000, device.cpu.iram.separated.SFR.PSW, __func__);
  tear_down();
}

int main()
{
  char test_name[23] = "8051AH INSTRUCTION TEST";
  /* printf_header(__FILE__, strlen(__FILE__), 1); */
  printf_header(test_name, strlen(test_name), 1);
  test_AJMP();
  test_LJMP();
  test_RR();
  test_INC_a();
  test_INC_db();
  test_INC_ir();
  test_INC_r();
  test_JBC();
  test_ACALL();
  test_LCALL();
  test_RRC();
  test_DEC_a();
  test_DEC_db();
  test_DEC_ir();
  test_DEC_r();
  test_JB();
  test_RET();
  test_RL();
  test_ADD_id();
  test_ADD_db();
  test_ADD_ir();
  test_ADD_r();

  test_RLC();
  /* test_ORL_a_to_db(); */
  /* test_ORL_id_to_db(); */
  /* test_ORL_id_to_a(); */
  /* test_ORL_db_to_a(); */
  /* test_ORL_ir_to_a(); */
  /* test_ORL_r_to_a(); */
  /* test_ANL_a_to_db(); */
  /* test_ANL_id_to_db(); */
  /* test_ANL_id_to_a(); */
  /* test_ANL_db_to_a(); */
  /* test_ANL_ir_to_a(); */
  /* test_ANL_r_to_a(); */
  /* test_XRL_a_to_db(); */
  /* test_XRL_id_to_db(); */
  /* test_XRL_id_to_a(); */
  /* test_XRL_db_to_a(); */
  /* test_XRL_ir_to_a(); */
  /* test_XRL_r_to_a(); */
  /* test_MOV_id_to_a(); */
  /* test_MOV_id_to_ir(); */
  /* test_MOV_id_to_r(); */
  /* test_MOV_c_to_dbi(); */
  /* test_MOV_dbi_to_c(); */
  /* test_CLR_dbi(); */
  /* test_CLR_c(); */
  /* test_SETB_dbi(); */
  /* test_SETB_c(); */
  printf_header(test_name, strlen(test_name), 0);
  return 0;
}
