#include "bufferpool.h"

void BufferPool::BufferPool(int numPages){
    MaxSize = numPages;
}

const int BufferPool::getPageSize(){
    return PAGE_SIZE;
}

Page* BufferPool::getPage(TransactionId* tid, PageId* pid, Permissions* perm){
    
    for(Page* page: PageList){
        if (page->getId()->equals(pid)){
            return page;
        }
    }

    if (PageList.size() == MaxSize){
        // throw new DbException("PageList is full!");
    }

    // get_catalog not implemented && 4.3
    for (Table* tab: Database->getCatalog()->getTables()){
        if (tab.file->getId() == pid->get_table_id()){
            Page* page = tab.file->ReadPage(pid);
            PageList.push_back(page);
            return page;
        }
    }

    return null;
}

void BufferPool::releasePage(TransactionId* tid, PageId* pid){

}

void BufferPool::transactionComplete(TransactionId* tid){

}

bool BufferPool::holdslock(TransactionId* tid, PageId* p){
    return false;
}

void BufferPool::transactionComplete(TransactionId* tid, bool commit){

}

void BufferPool::insertTuple(TransactionId* tid, int tableId, Tuple* t){

}

void BufferPool::deleteTuple(TransactionId* tid, Tuple* t){

}

void BufferPool::flushAllPages(){

}

void BufferPool::discardPage(PageId* pid){

}

void BufferPool::flushPage(PageId* pid){

}

void BufferPool::flushPages(TransactionId* tid){

}

void BufferPool::evictPage() {

}
