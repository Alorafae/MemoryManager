
#include "PerfTestFunctions.h"
#include "MockObj.h"
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

void MMAllocTest(MemManager &mm, unsigned nObjs)
{
  PERF;

  std::vector<MMHandle> mmHandles;

  for (unsigned i = 0; i < nObjs; ++i)
  {
    mmHandles.push_back(mm.Alloc("MockModel", sizeof(MockModel)));
  }

  for (auto iter = mmHandles.begin(); iter != mmHandles.end(); ++iter)
  {
     mm.Dealloc(*iter);
  }
}

// exact same function as MMAllocTest2, but always runs after original one
// for performance testing subsequent allocations (after memory is allocated)
void MMAllocTest2(MemManager &mm, unsigned nObjs)
{
  PERF;

  std::vector<MMHandle> mmHandles;

  for (unsigned i = 0; i < nObjs; ++i)
  {
    mmHandles.push_back(mm.Alloc("MockModel", sizeof(MockModel)));
  }

  for (auto iter = mmHandles.begin(); iter != mmHandles.end(); ++iter)
  {
    mm.Dealloc(*iter);
  }
}

void SingleNewTest(void)
{
  PERF

  MockModel* model = new MockModel;

  delete model;
}

void SingleMMAllocTest(MemManager &mm)
{
  PERF

  MMHandle model = mm.Alloc("MockModel", sizeof(MockModel));

  mm.Dealloc(model);
}
