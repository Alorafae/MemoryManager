
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

  //MMHandle handle;

  //handle = mm.Alloc(std::string("MockModel"), sizeof(MockModel));

  for (unsigned i = 0; i < nObjs; ++i)
  {
    mmHandles.push_back(mm.Alloc(std::string("MockModel"), sizeof(MockModel)));
  }

  for (auto iter = mmHandles.begin(); iter != mmHandles.end(); ++iter)
  {
     mm.Dealloc(*iter);
  }

  //handle.Data<MockModel>().Update(1.0f);
}

// exact same function as MMAllocTest2, but always runs after original one
// for performance testing
void MMAllocTest2(MemManager &mm, unsigned nObjs)
{
  PERF;

  std::vector<MMHandle> mmHandles;

  for (unsigned i = 0; i < nObjs; ++i)
  {
    mmHandles.push_back(mm.Alloc(std::string("MockModel"), sizeof(MockModel)));
  }

  for (auto iter = mmHandles.begin(); iter != mmHandles.end(); ++iter)
  {
    mm.Dealloc(*iter);
  }
}
