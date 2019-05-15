
#pragma once

#include <vector>
#include <map>
#include <intrin.h>

#include <fstream>
#include <ostream>

#include <windows.h>

#pragma intrinsic(__rdtsc) // clock cycle count intrinsic
#pragma intrinsic(_ReturnAddress)

class FData // Function data
{
public:
  FData();
  ~FData();
  const char* FSig;
  size_t nCalls;
  size_t minTime;
  size_t maxTime;
  size_t tTime;
};

class SData // Stack data
{
public:
  SData();
  ~SData();
  const char* id;

  size_t sTime;
  size_t eTime;
};

class Perf // Main profiler class
{
public:
  Perf();
  ~Perf();
  void Enter(unsigned __int64 start, const char* funcsig);
  void Leave(unsigned __int64 end);
  void End(void);
  void Start(void);
  void Print(void);
private:
  unsigned __int64 tCPUCycles;
  unsigned __int64 tTime;
  std::map<const char*, FData*> data_;
  std::vector<SData> stack_;
};

class FSig // Function signature magic
{
public:
  FSig(const char* ID);
  ~FSig();
};

extern Perf* g_Perf;
#define PERF FSig f( __FUNCSIG__ );
#define PERF_PRINT g_Perf->Print();
#define PERF_FRAME_START g_Perf->Start();
#define PERF_FRAME_END g_Perf->End();
