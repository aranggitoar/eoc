#include "8051ah/8051ah.h"

int main()
{
  device_t *device = malloc(sizeof(device_t));
  if (device == NULL) printf("Failed to allocate memory.\n");
  else {
    init_device(device, NULL);
    run_device(device);
    free(device);
  }
  return 0;
}
