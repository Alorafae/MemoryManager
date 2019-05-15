
#include "PerfTestFunctions.h"
#include <vector>

void NewTest(unsigned nObjs)
{
  PERF

  std::vector<MockModel*> mmPtrs;

  for (unsigned i = 0; i < nObjs; ++i)
  {
    mmPtrs.push_back(new MockModel);
  }

  for (auto iter = mmPtrs.begin(); iter != mmPtrs.end(); ++iter)
  {
    delete *iter;
  }
}