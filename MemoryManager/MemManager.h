#pragma once

/*
pagesize will be objects/page
64 byte align everything
maybe add threading
*/

typedef class MemManager
{
  public:
    MemManager();
    ~MemManager();

    bool Alloc();
    bool Dealloc();

    bool AddObjType();

  private:


};

typedef class ObjManager
{
  public:
    ObjManager();
    ~ObjManager();

  private:

};
