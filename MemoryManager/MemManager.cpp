
#include "MemManager.h"
#include "Profiler.h"

MemManager::MemManager()
{
}

MemManager::~MemManager()
{
}

// only place new should be called
MMHandle MemManager::Alloc(const char* type, size_t objSize)
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

bool MemManager::Dealloc(MMHandle handle)
{
  PERF

  void* p = handle.GetRaw();
  const char* type = handle.GetType();
  size_t size = handle.GetSize();
  
  auto iter = objectPageMap_[type];

  return iter->DelBlock(p, size);
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

  unsigned pSize = sizeof(void*);
  unsigned totalSize = (size + sizeof(void*)) * ObjPerPage;
  // create the raw page
  void* page = malloc(size * ObjPerPage);
  memset(page, 0, size * ObjPerPage);


  // raw page with extra ptr space
  // (size + sizeof(void*)) * objperpage

  PageFile pf;
  pf.page = page;

  // put the page file into our pagefiles list
  pageFiles_.push_back(pf);

  unsigned char* block = static_cast<unsigned char*>(page);
  for (unsigned i = 0; i < ObjPerPage; ++i)
  {
    freeList_.push_back(block + (i * size));
    
  }

  
  unsigned char* n_block = static_cast<unsigned char*>(page);
  free_.next = static_cast<MBlock*>(page);

  for (unsigned i = 0; i < ObjPerPage; ++i)
  {
    //MBlock* mb = dynamic_cast<MBlock*>(block + (i * (size + sizeof(void*))) );
  }
}

void* PageList::GetFreeBlock()
{
  PERF

  if (freeList_.empty())
    return nullptr;

  void* block = freeList_.back();
  freeList_.pop_back();

  return block;
}

bool PageList::DelBlock(void * p, size_t size)
{
  PERF

  memset(p, 0, size);

  freeList_.push_back(p);

#if DEBUG_PRINT_OUTS
  printf("block deleted\n");
#endif

  return true;
}

MMHandle::MMHandle() : type_("NO_TYPE"), data_(nullptr)
{
}

MMHandle::MMHandle(const char* type, void * bptr, size_t size)
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

const char* MMHandle::GetType()
{
  return type_;
}

size_t MMHandle::GetSize()
{
  return size_;
}
