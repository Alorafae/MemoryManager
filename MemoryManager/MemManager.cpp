
#include "MemManager.h"
#include "Profiler.h"

MemManager::MemManager()
{
}

MemManager::~MemManager()
{
}

// only place new should be called
MMHandle MemManager::Alloc(std::string type, size_t objSize)
{
  PERF

  // no pages exist for this type yet
  if (objectPageMap_.find(type) == objectPageMap_.end())
  {
    PageList* PL = new PageList;

    PL->CreatePage(objSize);

    objectPageMap_[type] = PL;

    return MMHandle(type, PL->GetFreeBlock(), objSize);
  }
  else // pages already exist for this object type
  {
    auto iter = objectPageMap_[type];

    return MMHandle(type, iter->GetFreeBlock(), objSize);
  }

  return MMHandle();
}

void MemManager::Dealloc(MMHandle handle)
{
  void* p = handle.GetRaw();
  std::string type = handle.GetType();
  size_t size = handle.GetSize();
  
  auto iter = objectPageMap_[type];

  iter->DelBlock(p, size);
}

PageList::PageList()
{
  //freeList_.resize(DEFAULT_OBJECTS_PER_PAGE);
}

PageList::~PageList()
{
}

// only place malloc should be called
void PageList::CreatePage(size_t size, unsigned ObjPerPage)
{
  PERF
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

void * PageList::DelBlock(void * p, size_t size)
{
  memset(p, 0, size);

  freeList_.push_back(p);

  return nullptr;
}

MMHandle::MMHandle() : type_("NO_TYPE"), data_(nullptr)
{
}

MMHandle::MMHandle(std::string type, void * bptr, size_t size)
{
  type_ = type;
  data_ = bptr;
  size_ = size;
}

MMHandle::~MMHandle()
{
}

void * MMHandle::GetRaw()
{
  return data_;
}

std::string MMHandle::GetType()
{
  return type_;
}

size_t MMHandle::GetSize()
{
  return size_;
}
