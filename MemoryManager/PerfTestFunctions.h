
#pragma once

#include "Profiler.h"
#include "MemManager.h"

void NewTest(unsigned nObjs);
void MMAllocTest(MemManager &mm, unsigned nObjs);
void MMAllocTest2(MemManager &mm, unsigned nObjs);
void SingleNewTest(void);
void SingleMMAllocTest(MemManager &mm);


