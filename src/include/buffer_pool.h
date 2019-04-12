#pragma once

#include <vector>
#include "catalog.h"
#include "page.h"
#include "page_id.h"
#include "permissions.h"
#include "tuple.h"

/**
 * BufferPool manages the reading and writing of pages into memory from
 * disk. Access methods call into it to retrieve pages, and it fetches
 * pages from the appropriate location.
 * 
 * The BufferPool is also responsible for locking;  when a transaction fetches
 * a page, BufferPool checks that the transaction has the appropriate
 * locks to read/write the page.
 * 
 * @Threadsafe, all fields are final
 */
namespace emerald {
class BufferPool {
 public:
  /**
   * Default number of pages passed to the constructor. This is used by
   * other classes. The BufferPool class should use the num_pages argument
   * supplied to the constructor instead.
   */
  static const int DEFAULT_PAGES = 50;

  std::vector<Page *> PageList;

  BufferPool(int num_pages, Catalog * catalog);

  ~BufferPool();

  static int get_page_size();

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
  Page * get_page(TransactionId * tid, PageId * pid, Permissions * perm);

  /**
   * Releases the lock on a page.
   * Calling this is very risky, and may result in wrong behavior. Think hard
   * about who needs to call this and why, and why they can run the risk of
   * calling it.
   *
   * @param tid the ID of the transaction requesting the unlock
   * @param pid the ID of the page to unlock
   */
  void ReleasePage(TransactionId * tid, PageId * pid);

  /**
    * Release all locks associated with a given transaction.
    *
    * @param tid the ID of the transaction requesting the unlock
    */
  void TransactionComplete(TransactionId * tid); // throws IOexception

  /**
   * Return true if the specified transaction has a lock on the specified page
   */
  bool HoldsLock(TransactionId * tid, PageId * p);

  /**
    * Commit or abort a given transaction; release all locks associated to
    * the transaction.
    *
    * @param tid the ID of the transaction requesting the unlock
    * @param commit a flag indicating whether we should commit or abort
    */
  void TransactionComplete(TransactionId * tid, bool commit); //IO exception

  /**
    * Add a tuple to the specified table behalf of transaction tid.  Will
    * acquire a write lock on the page the tuple is added to(Lock 
    * acquisition is not needed for lab2). May block if the lock cannot 
    * be acquired.
    * 
    * Marks any pages that were dirtied by the operation as dirty by calling
    * their markDirty bit, and updates cached versions of any pages that have 
    * been dirtied so that future requests see up-to-date pages. 
    *
    * @param tid the transaction adding the tuple
    * @param tableId the table to add the tuple to
    * @param t the tuple to add
    */
  void InsertTuple(TransactionId * tid, int tableId, Tuple * t); // throws DbException, IOException, TransactionAbortedException

  /**
    * Remove the specified tuple from the buffer pool.
    * Will acquire a write lock on the page the tuple is removed from. May block if
    * the lock cannot be acquired.
    *
    * Marks any pages that were dirtied by the operation as dirty by calling
    * their markDirty bit.  Does not need to update cached versions of any pages that have 
    * been dirtied, as it is not possible that a new page was created during the deletion
    * (note difference from addTuple).
    *
    * @param tid the transaction deleting the tuple.
    * @param t the tuple to delete
    */
  void DeleteTuple(TransactionId * tid, Tuple * t);

  /**
    * Flush all dirty pages to disk.
    * NB: Be careful using this routine -- it writes dirty data to disk so will
    *     break simpledb if running in NO STEAL mode.
    */
  void FlushAllPages();

  /** 
   * Remove the specific page id from the buffer pool.
   * Needed by the recovery manager to ensure that the buffer pool doesn't keep
   * a rolled back page in its cache.
   */
  void DiscardPage(PageId * pid);

  /**
   * Write all pages of the specified transaction to disk.
   */
  void FlushPages(TransactionId * tid);

 private:
  /**
    * Bytes per page, including header.
    */
  static const int PAGE_SIZE = 4096;

  std::vector<Page *> * buffer_pool;

  Catalog * catalog = 0;

  int evictIdx = 0;

  /**
    * Flushes a certain page to disk
    * @param pid an ID indicating the page to flush
    */
  void FlushPage(PageId * pid);

  /**
    * Discards a page from the buffer pool.
    * Flushes the page to disk to ensure dirty pages are updated on disk.
    */
  void EvictPage();
};
}
