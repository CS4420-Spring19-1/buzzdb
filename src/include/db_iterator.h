#pragma once

#include "tuple.h"

namespace buzzdb {
/**
 * DbIterator is the iterator interface that all BuzzDB operators should
 * implement. If the iterator is not open, none of the methods should work,
 * and an IllegalStateException should be thrown. In addition to any resource
 * allocation / deallocation, an open method should call any child iterator
 * open methods, and in a close method, an iterator should call its children's
 * close methods.
 */
class DbIterator {
 public:
  /**
   * Opens the iterator. This must be called before any of the other methods.
   * 
   * Throws DBException when there are problems opening / closing the database.
   */
  virtual void Open() = 0;

  /**
   * Returns true if the iterator has more tuples.
   * Throws IllegalStateException if the iterator has not been opened.
   */
  virtual bool HasNext() = 0;

  /**
   * Returns the next tuple from the operator.
   * (typically implemented by reading from a child operator or an access
   * method.)
   * 
   * Throws NoSuchElementException if there are no more tuples.
   * Throws IllegalStateException if the iterator has not been opened.
   */
  virtual Tuple Next() = 0;

  /**
   * Resets the iterator to the start.
   * 
   * Throws DbException when rewind is unsupported.
   * Throws IllegalStateException if the iterator has not been opened.
   */
  virtual void Rewind() = 0;

  /**
   * Returns the TupleDesc associated with the DbIterator.
   */
  virtual TupleDesc get_tuple_desc() const = 0;

  /**
   * Closes the DbIterator.
   * 
   * When the iterator is closed, calling Next(), HasNext() or Rewind() should
   * fail by throwing an IllegalStateException.
   */
  virtual void Close() = 0;
};
}