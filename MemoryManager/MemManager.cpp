
#include "MemManager.h"

MemManager::MemManager()
{
}

MemManager::~MemManager()
{
}

// only place new should be called
MMHandle MemManager::Alloc(std::string type, size_t objSize)
{
  MMHandle handle(type);

  // no pages exist for this type yet
  if (objectPageMap_.find(type) == objectPageMap_.end())
  {
    PageList* PL = new PageList;

    PL->CreatePage(ObjsPerPage * objSize);

    objectPageMap_[type] = PL;
  }
  else // pages already exist for this object type
  {
    auto iter = objectPageMap_[type];
  }

  return handle;
}

PageList::PageList()
{
}

PageList::~PageList()
{
}

// only place malloc should be called
void PageList::CreatePage(size_t size)
{
  void* page = malloc(size);

  PageFile pf;
  pf.page = page;

  pageFiles_.push_back(pf);
}

MMHandle::MMHandle()
{
}

MMHandle::MMHandle(std::string type)
{
  type_ = type;
}

MMHandle::~MMHandle()
{
}
