
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
  

  // no pages exist for this type yet
  if (objectPageMap_.find(type) == objectPageMap_.end())
  {
    PageList* PL = new PageList;

    PL->CreatePage(objSize);

    objectPageMap_[type] = PL;

    return MMHandle(type, PL->GetFreeBlock());
  }
  else // pages already exist for this object type
  {
    auto iter = objectPageMap_[type];

    return MMHandle(type, iter->GetFreeBlock());
  }

  return MMHandle();
}

PageList::PageList()
{
}

PageList::~PageList()
{
}

// only place malloc should be called
void PageList::CreatePage(size_t size, unsigned ObjPerPage)
{
  // create the raw page
  void* page = malloc(size * ObjPerPage);
  memset(page, 0, size * ObjPerPage);

  PageFile pf;
  pf.page = page;

  // put the page file into our pagefiles list
  pageFiles_.push_back(pf);

  unsigned char* block = static_cast<unsigned char*>(page);
  for (unsigned i = 0; i < ObjPerPage; ++i)
  {
    freeList_.push_back(block + (i * size));
  }

}

void* PageList::GetFreeBlock()
{
  if (freeList_.empty())
    return nullptr;

  void* block = freeList_.back();
  freeList_.pop_back();

  return block;
}

MMHandle::MMHandle() : type_("NO_TYPE"), data_(nullptr)
{
}

MMHandle::MMHandle(std::string type, void * bptr)
{
  type_ = type;
  data_ = bptr;
}

MMHandle::~MMHandle()
{
}
