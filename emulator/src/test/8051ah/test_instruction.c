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

void test_LJMP()
{
  set_up(0b00000010, 0b00001111, 0b11111111);
  LJMP(&device.cpu); 
  assert_equal_uint8(0b11111111, device.cpu.pc, __func__);
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
  printf_header(__FILE__, strlen(__FILE__), 1);
  test_LJMP();
  test_ORL_a_to_db();
  test_ORL_id_to_db();
  test_ORL_id_to_a();
  test_ORL_db_to_a();
  test_ORL_ir_to_a();
  test_ORL_r_to_a();
  test_ANL_a_to_db();
  test_ANL_id_to_db();
  test_ANL_id_to_a();
  test_ANL_db_to_a();
  test_ANL_ir_to_a();
  test_ANL_r_to_a();
  test_XRL_a_to_db();
  test_XRL_id_to_db();
  test_XRL_id_to_a();
  test_XRL_db_to_a();
  test_XRL_ir_to_a();
  test_XRL_r_to_a();
  test_MOV_id_to_a();
  test_MOV_id_to_ir();
  test_MOV_id_to_r();
  test_MOV_c_to_dbi();
  test_MOV_dbi_to_c();
  test_CLR_dbi();
  test_CLR_c();
  test_SETB_dbi();
  test_SETB_c();
  printf_header(__FILE__, strlen(__FILE__), 0);
  return 0;
}
