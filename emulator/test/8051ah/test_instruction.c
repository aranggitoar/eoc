#include "../../src/8051ah/instruction.h"
#include "../../src/8051ah/8051ah.h"
#include "../test_utils.h"

device_t device;

void set_up(uint8_t a, uint8_t b, uint8_t c)
{
  rom_t rom = {[0] = a, [1] = b, [2] = c, [3 ... 4095] = 0x00};
  init_device(&device, &rom);
}

void tear_down()
{
}

void test_MOV_id_to_r()
{
  set_up(0b01111111, 0b00101010, 0x00);
  MOV_id_to_r(device.cpu.rom[device.cpu.pc], &device.cpu);
  assert_equal_uint8(device.cpu.rom[device.cpu.pc], device.cpu.iram.separated.R[0][7], __func__);
}

void test_CLR_c()
{
  set_up(0x00, 0x00, 0x00);
  device.cpu.iram.separated.SFR.PSW = 0b10000000;
  CLR_c(&device.cpu);
  assert_equal_uint8(0b00000000, device.cpu.iram.separated.SFR.PSW, __func__);
}

void test_CLR_dbi()
{
  set_up(0b11000010, 0x00, 0x00);
  device.cpu.iram.separated.BaS[0] = 0b00000001;
  device.cpu.pc = device.cpu.pc + 1;
  CLR_dbi(device.iram_balt[device.cpu.rom[device.cpu.pc]], &device.cpu);
  assert_equal_uint8(0b00000000, device.cpu.iram.separated.BaS[0], __func__);
}

/* SETB_c(&device->cpu); */

/* SETB_dbi(device->iram_balt[device->cpu.rom[device->cpu.pc]], &device->cpu); */

/* MOV_dbi_to_c(device->iram_balt[device->cpu.rom[device->cpu.pc]], &device->cpu); */

/* MOV_c_to_dbi(device->iram_balt[device->cpu.rom[device->cpu.pc]], &device->cpu); */

/* LJMP(&device->cpu); */

int main()
{
  printf_header(__FILE__, strlen(__FILE__), 1);
  test_MOV_id_to_r();
  test_CLR_c();
  test_CLR_dbi();
  printf_header(__FILE__, strlen(__FILE__), 0);
  return 0;
}
