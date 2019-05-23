#pragma once

#include <map>
#include <string>

#include <list>
#include <vector>

/*
pagesize will be objects/page
64 byte align everything
maybe add threading
*/

#define DEFAULT_OBJECTS_PER_PAGE 1024
#define DEBUG_PRINT_OUTS false

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

    void CreatePage(size_t size, unsigned ObjPerPage = DEFAULT_OBJECTS_PER_PAGE);
    void DeletePage();

    void* GetFreeBlock();
    bool DelBlock(void* p, size_t size);

  private:
    std::vector<PageFile> pageFiles_;

    // need a free list
    std::vector<void*> freeList_;
    // might as well do a in use list too
    std::vector<void*> usedList_;

    //void* pageFiles_;
    unsigned pages_;
};


class MMHandle
{
  public:
    MMHandle();
    MMHandle(std::string type, void* bptr, size_t size);
    ~MMHandle();
    
    template <typename T>
    T Data();

    void* GetRaw();
    std::string GetType();
    size_t GetSize();
  private:
    void* data_;
    std::string type_;
    size_t size_;
};

class MemManager
{
  public:
    MemManager();
    ~MemManager();

    // maybe instead pass alloc a handle template and instantiate then and there?
    //void Alloc(MMHandle &handle, size_t objSize);
    MMHandle Alloc(std::string type, size_t objSize);
    bool Dealloc(MMHandle handle);

    bool AddObjType();

  private:
    // strings will be our keys
    std::map<std::string, PageList*> objectPageMap_;
    //unsigned ObjsPerPage = DEFAULT_OBJECTS_PER_PAGE;
};

class ObjManager
{
  public:
    ObjManager();
    ~ObjManager();

  private:

};

template<typename T>
inline T MMHandle::Data()
{
  return T();
}
