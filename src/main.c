#include "FreeRTOS.h"
#include "task.h"

int main(void)
{
  // start FreeRTOS scheduler
  vTaskStartScheduler();

  return 0;
}
