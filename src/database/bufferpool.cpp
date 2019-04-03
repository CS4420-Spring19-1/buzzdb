#include "bufferpool.h"

namespace emerald{
  void BufferPool::BufferPool(int num_pages) {
    MaxSize = num_pages;
  }

  const int BufferPool::get_page_size() {
    return PAGE_SIZE;
  }

  Page* BufferPool::GetPage(TransactionId* tid, PageId* pid, Permissions* perm){
      for(Page* page: PageList){
          if (page->getId()->equals(pid)){
              return page;
          }
      }

      if (PageList.size() == MaxSize){
          // throw new DbException("PageList is full!");
      }

      // get_catalog not implemented && 4.3
      for (Table* tab: Database->GetCatalog()->GetTables()){
          if (tab.file->getid() == pid->get_table_id()){
              Page* page = tab.file->ReadPage(pid);
              PageList.push_back(page);
              return page;
          }
      }

      return null;
  }

  void BufferPool::ReleasePage(TransactionId* tid, PageId* pid){

  }

  void BufferPool::TransactionComplete(TransactionId* tid){

  }

  bool BufferPool::HoldsLock(TransactionId* tid, PageId* p){
      return false;
  }

  void BufferPool::TransactionComplete(TransactionId* tid, bool commit){

  }

  void BufferPool::InsertTuple(TransactionId* tid, int tableId, Tuple* t){

  }

  void BufferPool::DeleteTuple(TransactionId* tid, Tuple* t){

  }

  void BufferPool::FlushAllPages(){

  }

  void BufferPool::DiscardPage(PageId* pid){

  }

  void BufferPool::FlushPage(PageId* pid){

  }

  void BufferPool::FlushPages(TransactionId* tid){

  }

  void BufferPool::EvictPage() {

  }
}

