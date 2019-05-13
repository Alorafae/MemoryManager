#pragma once

#include <map>
#include <string>

/*
pagesize will be objects/page
64 byte align everything
maybe add threading
*/

typedef class PageList
{

};

typedef class MemManager
{
  public:
    MemManager();
    ~MemManager();

    bool Alloc();
    bool Dealloc();

    bool AddObjType();

  private:
    // strings will be our keys
    // the void* will point to the actual page files
    std::map<std::string, void*> objectPageMap_;

};

typedef class ObjManager
{
  public:
    ObjManager();
    ~ObjManager();

  private:

};
