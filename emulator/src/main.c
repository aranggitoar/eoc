#include "8051ah/8051ah.h"

int main()
{
  device_t device;
  init_device(&device, NULL);
  run_device(&device);
  return 0;
}
