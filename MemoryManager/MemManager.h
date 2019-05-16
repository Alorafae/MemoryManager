#pragma once

#include <map>
#include <string>

#include <vector>

/*
pagesize will be objects/page
64 byte align everything
maybe add threading
*/

struct PageFile
{
  void* page = NULL;
  unsigned inUse = 0;
};

class PageList
{
  public:
    PageList();
    ~PageList();

    void CreatePage(size_t size);
    void DeletePage();

  private:
    std::vector<PageFile> pageFiles_;

    //void* pageFiles_;
    unsigned pages_;
};

class MMHandle
{
  public:
    MMHandle();
    ~MMHandle();


  private:
    void* data_;
};

class MemManager
{
  public:
    MemManager();
    ~MemManager();

    MMHandle Alloc(std::string type, size_t objSize);
    bool Dealloc(MMHandle handle);

    bool AddObjType();

  private:
    // strings will be our keys
    std::map<std::string, PageList*> objectPageMap_;
    unsigned ObjsPerPage = 128;
};

class ObjManager
{
  public:
    ObjManager();
    ~ObjManager();

  private:

};
