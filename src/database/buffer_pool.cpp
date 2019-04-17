#include "buffer_pool.h"

namespace buzzdb {
BufferPool::BufferPool(int num_pages, Catalog * catalog) {
  buffer_pool = new std::vector<Page*>(num_pages);
  this->catalog = catalog;
  // lock = new LockManager(num_pages);
}
BufferPool::~BufferPool() {
  delete buffer_pool;
  buffer_pool = nullptr;
}

int BufferPool::get_page_size() {
  return PAGE_SIZE;
}

Page * BufferPool::get_page(TransactionId * tid, 
                            PageId * pid, 
                            Permissions * perm) {
  int idx = -1;

  /**
   * To reduce pointer chasing, the buffer_pool pointer is dereferenced and
   * assigned to a local variable at the start of the function. 
   */
  std::vector<Page *> buffer_pool_object = (*buffer_pool);
  
  for (int i = 0; i < buffer_pool_object.size(); i++) {
    if (buffer_pool_object[i] == nullptr) {
      idx = i;
    /**
     * This might be an incorrect implementation: equality of the objects
     * should be checked instead of equality of their pointers.
     * 
     * Then again, if implemented that way, there must be some way to check
     * equality of two objects pointed to by abstract class type pointers.
     */
    } else if (pid == buffer_pool_object[i]->get_id()) {
      return buffer_pool_object[i];
    }
  }

  /**
   * If the buffer pool is full, use the eviction protocol to remove a page.
   * Otherwise, replace the page in the ith slot with the replacement page
   * pointed to by pid.
   */
  if (idx < 0) {
    EvictPage();
    return get_page(tid, pid, perm);
  } else {
    /**
     * Might be good to abstract this code block into a function.
     */
    // gets the DbFile that can be used to read the contents of the table.
    DbFile * db_file = catalog->get_db_file(pid->get_table_id());

    // gets a pointer to the replacement page from the DbFile object.
    Page * replacement_page = db_file->ReadPage(pid);

    // utilizing commutativity of the assignment operator here.
    return buffer_pool_object[idx] = replacement_page;
  }
}

void BufferPool::ReleasePage(TransactionId * tid, PageId * pid) {
  /* Incomplete work but not required for Lab 1 or 2.
  // see explaination in get_page()
  std::vector<Page *> buffer_pool_object = (*buffer_pool);
  
  for (int i = 0; i < buffer_pool_object.size(); i++) {
    if (buffer_pool_object[i] != nullptr
        && buffer_pool_object[i]->get_id() == pid) {
       if (lock.isHolding(tid, i)) {
         lock.release(tid, i);
         return;
       }
    }
  }
  */
}

void BufferPool::TransactionComplete(TransactionId * tid) {
  /* Incomplete work but not required for Lab 1 or 2
  TransactionComplete(tid, true);
  */
}

bool BufferPool::HoldsLock(TransactionId * tid, PageId * pid) {
  /* Incomplete work but not required for Lab 1 or 2.
  // see explaination in get_page()
  std::vector<Page *> buffer_pool_object = (*buffer_pool);

  for (int i = 0; i < buffer_pool_object.size(); i++) {
    if (buffer_pool_object[i] != nullptr && buffer_pool_object[i]->get_id() == pid) {
      // return lock.isHolding(tid, i);
    }
  }
  */
  return false;
}

void BufferPool::TransactionComplete(TransactionId * tid, bool commit) {
  /* Incomplete work but not required for Lab 1 or 2.
  if (commit) {
    FlushPages(tid);
  }

  // see explaination in get_page()
  std::vector<Page *> buffer_pool_object = (*buffer_pool);
  
  for (int i = 0; i < buffer_pool_object.size(); i++) {
    if (lock.isholding(tid, i)) {
      if (!commit && buffer_pool_object[i] != nullptr && tid == buffer_pool_object[i]->GetIdOfLastDirtyTransaction()) {
        buffer_pool_object[i] = nullptr;
      }
      lock.release(tid, i);
    }
  }
  */
}

void BufferPool::InsertTuple(TransactionId * tid, int table_id, Tuple * t) {
  // Implementation: Lab 5 version
  std::vector<Page*> page_vector =
      catalog->get_db_file(table_id)->AddTuple(*tid, *t);
  for (Page * page: page_vector) {
    page->MarkDirty(true, *tid);
  }
}

void BufferPool::DeleteTuple(TransactionId * tid, Tuple * t) {
  // Implementation: Lab 5 version
  int table_id = t->get_record_id()->get_page_id()->get_table_id();

  DbFile * db_file = catalog->get_db_file(table_id);

  db_file->DeleteTuple(*tid, *t)->MarkDirty(true, *tid);
}

void BufferPool::FlushAllPages() {
  // Implementation: Lab 1 version
  // see explaination in get_page()
  std::vector<Page *> buffer_pool_object = (*buffer_pool);
  
  for (int i = 0; i < buffer_pool_object.size(); i++) {
    if (buffer_pool_object[i] != nullptr
        && buffer_pool_object[i]->GetIdOfLastDirtyTransaction() != nullptr ) {
      FlushPage(buffer_pool_object[i]->get_id());
    }
  }
}

void BufferPool::DiscardPage(PageId * pid) {
  /* Incomplete but only required for Lab 5
  // see explaination in get_page()
  std::vector<Page *> buffer_pool_object = (*buffer_pool);
  
  for (int i = 0; i < buffer_pool_object.size(); i++) {
    if (buffer_pool_object[i] != nullptr && pid == buffer_pool_object[i]->get_id()) {
      buffer_pool_object[i] = nullptr;
      break;
    }
  }
  */
}


void BufferPool::FlushPages(TransactionId * tid) {
  /* Incomplete but not required for Lab 1, 2, 3
  // see explaination in get_page()
  std::vector<Page *> buffer_pool_object = (*buffer_pool);
  
  for (int i = 0; i < buffer_pool_object.size(); i++) {
    if (buffer_pool_object[i] != nullptr && lock.isHolding(tid, i)) {
      FlushPage(buffer_pool_object[i]->get_id());
      buffer_pool_object[i]->SetBeforeImage();
    }
  }
  */
}

void BufferPool::FlushPage(PageId * pid) {
  /* Incomplete but not required for Lab 1
  // see explaination in get_page()
  std::vector<Page *> buffer_pool_object = (*buffer_pool);
  
  for (int i = 0; i < buffer_pool_object.size(); i++) {
    if (buffer_pool_object[i] != nullptr && pid == buffer_pool_object[i]->get_id()) {
      TransactionId* dirtier = buffer_pool_object[i]->GetIdOfLastDirtyTransaction();
      if (dirtier != nullptr) {
         Database.getLogFile().logWrite(dirtier, buffer_pool_object[i].getBeforeImage(), buffer_pool_object[i]);
         Database.getLogFile().force();
         Database.getCatalog().getDatabaseFile(pid.getTableId()).writePage(buffer_pool_object[i]);
         buffer_pool_object[i].markDirty(false, buffer_pool_object[i].isDirty());
      }
      break;
    }
  }
  */
}

void BufferPool::EvictPage() {
  /* Incomplete but not required for Lab 1
  // see explaination in get_page()
  std::vector<Page *> buffer_pool_object = (*buffer_pool);
  
  for (int init = evictIdx; buffer_pool_object[evictIdx] != nullptr 
    && buffer_pool_object[evictIdx]->GetIdOfLastDirtyTransaction() != nullptr; ) {
      evictIdx = (evictIdx + 1) % buffer_pool_object.size();
      if (init == evictIdx) {
        // throw new DbException("no non-dirty page to evict");
      }
    }
  if (buffer_pool_object[evictIdx] != nullptr) {
    try {
      FlushPage(buffer_pool_object[evictIdx]->get_id());
      buffer_pool_object[evictIdx] = nullptr;
      evictIdx = (evictIdx + 1) % buffer_pool_object.size(); }
    // } catch (IOException e) {
    //   // throw new DbException(e.getMessage());
    // }
  }
  */
}
}
