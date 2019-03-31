#pragma once

#include <iostream>
#include <vector>
#include "page.h"
#include "pageId.h"
#include "table.h"
#include "database.h"

/*
remaining question
1. Page structure
2. 
*/


/**
 * BufferPool manages the reading and writing of pages into memory from
 * disk. Access methods call into it to retrieve pages, and it fetches
 * pages from the appropriate location.
 * <p>
 * The BufferPool is also responsible for locking;  when a transaction fetches
 * a page, BufferPool checks that the transaction has the appropriate
 * locks to read/write the page.
 * 
 * @Threadsafe, all fields are final
 */

namespace emerald{
    class BufferPool{
        private:
            /** Bytes per page, including header. */
            static const int PAGE_SIZE = 4096;          
			std::vector<Page> buffer;
            int evictIdx = 0;
  
        public:
            /** Default number of pages passed to the constructor. This is used by
            other classes. BufferPool should use the numPages argument to the
            constructor instead. */
            static const int DEFAULT_PAGES = 50;
            std::vector<Page> PageList;
            int MaxSize = DEFAULT_PAGES;
			
            // final LockManager lock
            BufferPool(int numPages);
            static int getPageSize();

            /**
             * Retrieve the specified page with the associated permissions.
             * Will acquire a lock and may block if that lock is held by another
             * transaction.
             * <p>
             * The retrieved page should be looked up in the buffer pool.  If it
             * is present, it should be returned.  If it is not present, it should
             * be added to the buffer pool and returned.  If there is insufficient
             * space in the buffer pool, an page should be evicted and the new page
             * should be added in its place.
             *
             * @param tid the ID of the transaction requesting the page
             * @param pid the ID of the requested page
             * @param perm the requested permissions on the page
             */
            Page getPage(TransactionId tid, PageId pid, Permissions perm);

    }
}

void BufferPool::BufferPool(int numPages){
    MaxSize = numPages;
}

const int BufferPool::getPageSize(){
    return PAGE_SIZE;
}

BufferPool::getPage(TransactionId tid, PageId pid, Permissions perm){
    
    for(Page page: PageList){
        if (page.getId().equals(pid)){
            return page;
        }
    }

    if (PageList.size() == MaxSize){
        // throw new DbException("PageList is full!");
    }

    for (Table tab: Database.getCatalog().getTables()){
        
    }
}