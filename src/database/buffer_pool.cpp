#include "buffer_pool.h"

namespace emerald {
BufferPool::BufferPool(int num_pages) {
  buffer = new std::vector<Page*>(num_pages);
  // test
  // lock = new LockManager(num_pages);
}

int BufferPool::get_page_size() const {
  return PAGE_SIZE;
}

Page * BufferPool::GetPage(TransactionId * tid, PageId * pid, Permissions * perm) {
  int idx = -1;
  for (size_t i = 0; i < buffer.size(); i++) {
    if (buffer[i] == NULL) {
      idx = i;
    } else if (pid == buffer[i]->get_id()) {
      // try {
      //   lock.acquire(tid, i, perm);
      // } catch (InterruptedException e) {
      //   throw new TransactionAbortedException();
      // }
      return buffer[i];
    }
  }
  if (idx < 0) {
    EvictPage();
    return GetPage(tid, pid, perm);
  } else {
    // try {
    //   lock.acquire(tid, idx, perm);
    // } catch (InterruptedException e) {
    //   throw new TransactionAbortedException();
    // }
    //return buffer[idx] = Database.getCatalog().getDatabaseFile(pid.getTableId()).readPage(pid);
  }

  return nullptr;
}

void BufferPool::ReleasePage(TransactionId * tid, PageId * pid) {
  for (int i=0; i<buffer.size(); i++) {
    if (buffer[i] != NULL && buffer[i]->get_id() == pid) {
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
    if (buffer[i] != NULL && buffer[i]->get_id() == pid) {
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
      if (!commit && buffer[i] != NULL && tid == buffer[i]->GetIdOfLastDirtyTransaction()) {
        buffer[i] = NULL;
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
    if (buffer[i] != NULL) {
      FlushPage(buffer[i]->get_id());
    }
  }
}

void BufferPool::DiscardPage(PageId * pid) {
  for (int i = 0; i < buffer.size(); i++) {
    if (buffer[i] != NULL && pid == buffer[i]->get_id()) {
      buffer[i] = NULL;
      break;
    }
  }
}

void BufferPool::FlushPage(PageId * pid) {
  for (int i = 0; i < buffer.size(); i++) {
    if (buffer[i] != NULL && pid == buffer[i]->get_id()) {
      TransactionId* dirtier = buffer[i]->GetIdOfLastDirtyTransaction();
      if (dirtier != NULL) {
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
    if (buffer[i] != NULL && lock.isHolding(tid, i)) {
      FlushPage(buffer[i]->get_id());
      buffer[i]->SetBeforeImage();
    }
  }
}

void BufferPool::EvictPage() {
  for (int init = evictIdx; buffer[evictIdx] != NULL 
    && buffer[evictIdx]->GetIdOfLastDirtyTransaction() != NULL; ) {
      evictIdx = (evictIdx + 1) % buffer.size();
      if (init == evictIdx) {
        // throw new DbException("no non-dirty page to evict");
      }
    }
  if (buffer[evictIdx] != NULL) {
    try {
      FlushPage(buffer[evictIdx]->get_id());
      buffer[evictIdx] = NULL;
      evictIdx = (evictIdx + 1) % buffer.size(); }
    // } catch (IOException e) {
    //   // throw new DbException(e.getMessage());
    // }
    
  }
}
}
