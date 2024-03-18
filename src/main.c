#include <device.h>

int main()
{
  device_8051ah_t device;
  init_device_8051ah(&device, NULL);
  run_device_8051ah(&device);
  return 0;
}
