#pragma once

#include <vector>
#include "db_file_iterator.h"
#include "page.h"
#include "tuple.h"

namespace buzzdb {
/**
 * The DbFile interface class is an interface for table representations.
 * - Each table in BuzzDB is represented by a DbFile, which contains pages.
 * - Pages contain tuples, which contain fields, which contain data values.
 * - Each DbFile has a unique id, which is used to store metadata about the
 *   table in the Catalog.
 * - DbFiles are generally accessed through the buffer pool, rather than
 *   directly by operators.
 */
class DbFile {
 public:
  /**
   * Destructor.
   * It is necessary for an interface class to have a virtual destructor to
   * ensure correct polymorphic deletion.
   */
  virtual ~DbFile() = 0;

  /**
   * Returns the unique id of the DbFile.
   * This id can be used to identify this DbFile in the Catalog using the
   * methods Catalog.get_db_file() and Catalog.get_tuple_desc().
   * 
   * Implementation note: This id will have to be generated somewhere.
   * Ensure that each HeapFile has a "unique" id and that the same value is
   * always returned for a particular HeapFile.
   */
  virtual int get_id() const = 0;

  /**
   * Returns the schema of the table stored in the DbFile.
   */
  virtual TupleDesc get_tuple_desc() const = 0;

  /**
   * Reads the specified page from disk.
   */
  virtual Page * ReadPage(PageId * id) = 0;

  /**
   * Writes the specified page back to disk.
   */
  virtual void WritePage(Page * p) = 0;

  /**
   * Adds the specified tuple to the DbFile on behalf of a transaction.
   * This method will acquire a lock on the affected pages of the file, and may
   * block until the lock can be acquired.
   */
  virtual std::vector<Page *> AddTuple(TransactionId & tid, Tuple & t) = 0;

  /**
   * Removes the specified tuple from the DbFile on behalf of a transaction.
   * This method will acquire a lock on the affected pages of the file, and may
   * block until the lock can be acquired.
   */
  virtual Page * DeleteTuple(TransactionId & tid, Tuple & t) = 0;

  /**
   * Returns an iterator over all tuples stored in this DbFile.
   * The iterator must use BufferPool.getPage() to iterate through.
   */
  virtual DbFileIterator * Iterator(TransactionId & tid) = 0;
};
}
