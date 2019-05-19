
#include "PerfTestFunctions.h"
#include <stdio.h>

int main(void)
{
  PERF_FRAME_START

  // add for this to take some parameters for max memory
  // max pages, page size, etc
  // maybe preallocating pages if you know ahead of time per object
  // like if you know you'll only ever have X number of Y, make all the pages at the start for speed
  MemManager MemMan;

  NewTest(1024);
  MMAllocTest(MemMan, 1024);

  PERF_FRAME_END
  PERF_PRINT

  return 0;
}
