#include "buffer_pool.h"

namespace emerald {
BufferPool::BufferPool(int num_pages) {
  buffer = new std::vector<Page*>(num_pages);
  // lock = new LockManager(num_pages);
}
BufferPool::~BufferPool() {
  delete buffer;
  buffer = nullptr;
}

int BufferPool::get_page_size() const {
  return PAGE_SIZE;
}

Page * BufferPool::GetPage(TransactionId * tid, PageId * pid, Permissions * perm) {
  return nullptr;
}

void BufferPool::ReleasePage(TransactionId * tid, PageId * pid) {
  for (int i=0; i<buffer.size(); i++) {
    if (buffer[i] != nullptr && buffer[i]->get_id() == pid) {
      /*
       if (lock.isHolding(tid, i)) {
         lock.release(tid, i);
         return;
       }
       */
    }
  }
}

void BufferPool::TransactionComplete(TransactionId * tid) {
  TransactionComplete(tid, true);
}

bool BufferPool::HoldsLock(TransactionId * tid, PageId * pid) {
  for (int i = 0; i < buffer.size(); i++) {
    if (buffer[i] != nullptr && buffer[i]->get_id() == pid) {
      // return lock.isHolding(tid, i);
    }
  }
  return false;
}

void BufferPool::TransactionComplete(TransactionId * tid, bool commit) {
  if (commit) {
    FlushPages(tid);
  }
  for (int i = 0; i < buffer.size(); i++) {
    if (lock.isholding(tid, i)) {
      if (!commit && buffer[i] != nullptr && tid == buffer[i]->GetIdOfLastDirtyTransaction()) {
        buffer[i] = nullptr;
      }
      lock.release(tid, i);
    }
  }
}

void BufferPool::InsertTuple(TransactionId * tid, int tableId, Tuple * t) {
  std::vector<Page*> list;
  // list = Database.getCatalog().getDatabaseFile(tableId).insertTuple(tid, t);
  for (Page* page: list) {
    page->MarkDirty(true, tid);
  }
}

void BufferPool::DeleteTuple(TransactionId * tid, Tuple * t) {
  /*
  Database.getCatalog().getDatabaseFile
    		(t.getRecordId().getPageId().getTableId()).deleteTuple(tid, t).markDirty(true, tid);
  */
}

void BufferPool::FlushAllPages() {
  for (int i = 0; i < buffer.size(); i++) {
    if (buffer[i] != nullptr) {
      FlushPage(buffer[i]->get_id());
    }
  }
}

void BufferPool::DiscardPage(PageId * pid) {
  for (int i = 0; i < buffer.size(); i++) {
    if (buffer[i] != nullptr && pid == buffer[i]->get_id()) {
      buffer[i] = nullptr;
      break;
    }
  }
}

void BufferPool::FlushPage(PageId * pid) {
  for (int i = 0; i < buffer.size(); i++) {
    if (buffer[i] != nullptr && pid == buffer[i]->get_id()) {
      TransactionId* dirtier = buffer[i]->GetIdOfLastDirtyTransaction();
      if (dirtier != nullptr) {
        /*
         Database.getLogFile().logWrite(dirtier, buffer[i].getBeforeImage(), buffer[i]);
         Database.getLogFile().force();
         Database.getCatalog().getDatabaseFile(pid.getTableId()).writePage(buffer[i]);
         buffer[i].markDirty(false, buffer[i].isDirty());
         */
      }
      break;
    }
  }
}

void BufferPool::FlushPages(TransactionId * tid) {
  for (int i = 0; i < buffer.size(); i++) {
    if (buffer[i] != nullptr && lock.isHolding(tid, i)) {
      FlushPage(buffer[i]->get_id());
      buffer[i]->SetBeforeImage();
    }
  }
}

void BufferPool::EvictPage() {
  for (int init = evictIdx; buffer[evictIdx] != nullptr 
    && buffer[evictIdx]->GetIdOfLastDirtyTransaction() != nullptr; ) {
      evictIdx = (evictIdx + 1) % buffer.size();
      if (init == evictIdx) {
        // throw new DbException("no non-dirty page to evict");
      }
    }
  if (buffer[evictIdx] != nullptr) {
    try {
      FlushPage(buffer[evictIdx]->get_id());
      buffer[evictIdx] = nullptr;
      evictIdx = (evictIdx + 1) % buffer.size(); }
    // } catch (IOException e) {
    //   // throw new DbException(e.getMessage());
    // }
    
  }
}
}
