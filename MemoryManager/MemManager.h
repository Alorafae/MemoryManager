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
  public:


  private:
    void* pageFiles_;
};

typedef class MMHandle
{
  public:
    MMHandle();
    ~MMHandle();


  private:
    void* data_;
};

typedef class MemManager
{
  public:
    MemManager();
    ~MemManager();

    MMHandle Alloc(std::string type, size_t objSize);
    bool Dealloc(MMHandle handle);

    bool AddObjType();

  private:
    // strings will be our keys
    std::map<std::string, PageList> objectPageMap_;

};

typedef class ObjManager
{
  public:
    ObjManager();
    ~ObjManager();

  private:

};
