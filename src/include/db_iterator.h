#pragma once

#include "tuple.h"

namespace buzzdb {
/**
 * The DbIterator interface class is an iterator interface for BuzzDb
 * operators.
 * - If the iterator is not open, none of the methods should work, and an
 *   IllegalStateException should be thrown. 
 * - In addition to any resource allocation / deallocation, an open method
 *   should call any child iterator open methods, and in a close method, an
 *   iterator should call its children's close methods.
 */
class DbIterator {
 public:
  /**
   * Destructor.
   * It is necessary for an interface class to have a virtual destructor to
   * ensure correct polymorphic deletion.
   */
  virtual ~DbIterator();

  /**
   * Opens the iterator.
   * This must be called before any of the other methods are used.
   * 
   * Throws:
   * - DBException: When there are problems opening / closing the database.
   */
  virtual void Open() = 0;

  /**
   * Returns true if the iterator has more tuples.
   * 
   * Throws:
   * - IllegalStateException: If the iterator is not open.
   */
  virtual bool HasNext() = 0;

  /**
   * Returns the next tuple from the operator.
   * 
   * Throws:
   * - IllegalStateException: If the iterator is not open.
   * - NoSuchElementException: If there are no more tuples.
   */
  virtual Tuple & Next() = 0;

  /**
   * Resets the iterator to the start.
   * 
   * Throws:
   * - IllegalStateException: If the iterator is not open.
   * - DbException: When rewind is unsupported.
   */
  virtual void Rewind() = 0;

  /**
   * Returns the TupleDesc associated with the current tuple.
   */
  virtual const TupleDesc & get_tuple_desc() const = 0;

  /**
   * Closes the iterator.
   * 
   * When the iterator is closed, calling Next(), HasNext() or Rewind() should
   * fail by throwing an IllegalStateException.
   */
  virtual void Close() = 0;
};
}