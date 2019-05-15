
#include "Profiler.h"

Perf* g_Perf = NULL;
static Perf s_Perf; // need a static to exist so it knows what one is

Perf::Perf()
{
  g_Perf = this;
}

Perf::~Perf()
{
}

void Perf::Start(void)
{
  tTime = 0;
  tCPUCycles = 0;
  stack_.clear();
  for (auto iter = data_.begin(); iter != data_.end(); ++iter)
  {
    FData* funcData = (*iter).second;
    funcData->nCalls = 0;
  }
}

FSig::FSig(const char* ID)
{
  g_Perf->Enter(__rdtsc(), ID);
}
FSig::~FSig()
{
  g_Perf->Leave(__rdtsc());
}

void Perf::Enter(unsigned __int64 start, const char* funcsig)
{
  SData stackData;
  stackData.sTime = size_t(start);
  stackData.id = funcsig;
  stackData.eTime = 0;
  stack_.push_back(stackData);
}

void Perf::Leave(unsigned __int64 end)
{
  SData stackData = stack_.back();
  stackData.eTime = size_t(end);
  stack_.pop_back();
  unsigned __int64 time = (stackData.eTime - stackData.sTime);
  size_t time_t = size_t(time);
  tCPUCycles += time;
  auto iter = data_.find(stackData.id);
  if (iter != data_.end())
  {
    FData* fd = (*iter).second;
    fd->nCalls++;
    fd->tTime += time_t;

    if (fd->minTime > time_t)
      fd->minTime = time_t;
    else if (fd->maxTime < time_t)
      fd->maxTime = time_t;
  }
  else
  {
    FData* fd = new FData; // not that slow after the map is saturated
    fd->FSig = stackData.id;
    fd->nCalls = 1;
    fd->minTime = time_t;
    fd->maxTime = time_t;
    fd->tTime = time_t;
    data_.insert(std::pair<const char*, FData*>(stackData.id, fd));
  }
}

void Perf::End(void)
{
}

void Perf::Print(void)
{
  std::ofstream log;
  log.open("Perf.txt");
  if (!log.is_open())
    return;
  LARGE_INTEGER freq;
  QueryPerformanceFrequency(&freq);
  double PCF = double(freq.QuadPart / 1000);
  log.setf(std::ios::fixed, std::ios::floatfield);
  log.precision(10);
  for (auto iter = data_.begin(); iter != data_.end(); ++iter)
  {
    FData* fd = (*iter).second;
    log << "Function:                     " << fd->FSig << std::endl;
    log << "-->Clock Cycles:              " << fd->tTime << std::endl;
    log << "-->Time in USec:              " << fd->tTime / PCF << std::endl;
    log << "-->Min Clock Cycles:          " << fd->minTime << std::endl;
    log << "-->Min Time USec:             " << fd->minTime / PCF << std::endl;
    log << "-->Max Clock Cycles:          " << fd->maxTime << std::endl;
    log << "-->Max Time USec:             " << fd->maxTime / PCF << std::endl;
    log << "-->Number of Calls Per Frame: " << fd->nCalls << std::endl;
    log << std::endl;
  }
  log.close();
}

FData::FData()
{
}

FData::~FData()
{
}

SData::SData()
{
}

SData::~SData()
{
}
