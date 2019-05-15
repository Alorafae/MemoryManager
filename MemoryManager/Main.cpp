
#include "MemManager.h"
#include "PerfTestFunctions.h"
#include <stdio.h>

int main(void)
{
  PERF_FRAME_START

  NewTest(100);

  PERF_FRAME_END
  PERF_PRINT

  return 0;
}
