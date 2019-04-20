#pragma once

#include "tuple.h"

namespace buzzdb {
/**
 * DbFileIterator is the iterator interface that all BuzzDB DBFiles should
 * implement.
 */
class DbFileIterator {
 public:
  /**
   * Destructor.
   * It is necessary for an interface class to have a virtual destructor to
   * ensure correct polymorphic deletion.
   */
  virtual ~DbFileIterator();

  /**
   * Opens the iterator.
   * 
   * Throws DbException when there are problems opening / accessing the
   * database.
   * Throws TransactionAbortedException.
   */
  virtual void Open() = 0;

  /**
   * Returns true if the iterator has more tuples.
   * 
   * Throws DbException, TransactionAbortedException.
   */
  virtual bool HasNext() = 0;

  /**
   * Gets the next tuple from the operator.
   * (typically implemented by reading from a child operator or an access
   * method.)
   * 
   * Throws NoSuchElementException if there are no more tuples.
   * Throws TransactionAbortedException, DbException.
   */
  virtual Tuple * Next() = 0;

  /**
   * Resets the iterator to the start.
   * 
   * Throws DbException when rewind is unsupported.
   * Throws TransactionAbortedException.
   */
  virtual void Rewind() = 0;

  /**
   * Closes the iterator.
   */
  virtual void Close() = 0;  
};
}
