#pragma once

#include <string>
#include "db_file.h"
#include "db_file_iterator.h"
#include "db_iterator.h"
#include "transaction_id.h"

namespace buzzdb {
/**
 * The SeqSca class is an implementation of a sequential scan access method
 * of a table.
 * - The table is represented by a DbFile and each tuple in the DbFile is read.
 * - There is no constraint on the order tuples are to be read.
 */
class SeqScan : DbIterator {
 public:
  /**
   * Constructor.
   * Creates a sequential scan over the specified table as part of the
   * specified transaction.
   * 
   * Parameters:
   * - tid: The transaction the scan is running as a part of.
   * - tableid: The table to scan.
   * - tableAlias: The alias of the table.
   */
  SeqScan(TransactionId & tid, int table_id, std::string table_alias);

  /**
   * Destructor.
   */
  ~SeqScan() = default;

  /**
   * Opens the iterator.
   * This must be called before any of the other methods are used.
   * 
   * Throws:
   * - DBException: When there are problems opening / closing the database.
   */
  void Open() override;

  /**
   * Returns true if the iterator has more tuples.
   * 
   * Throws:
   * - IllegalStateException: If the iterator is not open.
   */
  bool HasNext() override;

  /**
   * Returns the next tuple from the operator.
   * 
   * Throws:
   * - IllegalStateException: If the iterator is not open.
   * - NoSuchElementException: If there are no more tuples.
   */
  Tuple & Next() override;

  /**
   * Resets the iterator to the start.
   * 
   * Throws:
   * - IllegalStateException: If the iterator is not open.
   * - DbException: When rewind is unsupported.
   */
  void Rewind() override;

  /**
   * Returns the TupleDesc associated with the current tuple.
   * 
   * // Not done
   * Returns the TupleDesc with field names from the underlying HeapFile,
   * prefixed with the tableAlias string from the constructor. This prefix
   * becomes useful when joining tables containing a field(s) with the same
   * name.
    */
  const TupleDesc & get_tuple_desc() const override;

  /**
   * Closes the iterator.
   * 
   * When the iterator is closed, calling Next(), HasNext() or Rewind() should
   * fail by throwing an IllegalStateException.
   */
  void Close() override;

 private:
  DbFile * db_file;
  std::string table_alias;
  DbFileIterator * iterator;
};
}
