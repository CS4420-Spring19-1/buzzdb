#pragma once

#include "tuple.h"

namespace buzzdb {
/**
 * The DbFileIterator interface class is an interface interface for
 * BuzzDb DbFiles.
 */
class DbFileIterator {
 public:
  /**
   * Destructor.
   * It is necessary for an interface class to have a virtual destructor to
   * ensure correct polymorphic deletion.
   */
  virtual ~DbFileIterator() = 0;

  /**
   * Opens the iterator.
   * 
   * Throws:
   * - DbException: When there are problems opening / accessing the database.
   * - TransactionAbortedException
   */
  virtual void Open() = 0;

  /**
   * Checks if the iterator has more tuples to iterate through.
   * 
   * Throws:
   * - DbException
   * - TransactionAbortedException
   */
  virtual bool HasNext() = 0;

  /**
   * Gets the next tuple from the operator.
   * (typically implemented by reading from a child operator or an access
   * method.)
   * 
   * Throws:
   * - NoSuchElementException: If there are no more tuples.
   * - TransactionAbortedException
   * - DbException
   */
  virtual Tuple * Next() = 0;

  /**
   * Resets the iterator to the start.
   * 
   * Throws:
   * - DbException: When rewind is unsupported.
   * - TransactionAbortedException
   */
  virtual void Rewind() = 0;

  /**
   * Closes the iterator.
   */
  virtual void Close() = 0;  
};
}
