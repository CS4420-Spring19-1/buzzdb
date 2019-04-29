#pragma once

#include "page_id.h"
#include "transaction_id.h"

namespace buzzdb {
/**
 * The Page interface class is an interface for page representations.
 * - This interface is largely utilized by the BufferPool.
 * - A page contains tuples, which contain fields.
 * - A page is contained in a table, which is typically implemented as a
 *   DbFile.
 * - A page may be "dirty", meaning that it has been modified since it was last
 *   written out to disk.
 */
class Page {
 public:
  /**
   * Destructor.
   * It is necessary for an interface class to have a virtual destructor to
   * ensure correct polymorphic deletion.
   */
  virtual ~Page() = 0;

  /**
   * Returns the id of the page.
   */
  virtual const PageId & get_id() const = 0;

  /**
   * Returns the transaction id of the last transaction that dirtied the page.
   * Returns null if the page is not dirty.
   */
  virtual const TransactionId * get_id_of_last_dirty_transaction() const = 0;

  /**
   * Sets the dirty state of the page as dirtied by a particular transaction.
   */
  virtual void MarkDirty(bool dirty, TransactionId * tid) = 0;
 
  /* Need to use another input parameter type besides byte
  virtual void GetPageData(std::byte content_rep[]) = 0;
  */

  /**
   * Returns a representation of the Page before any modifications were made to
   * it. Used by recovery.
   */
  virtual Page * GetBeforeImage() = 0;

  /**
   * A transaction that wrote this Page just committed it. Copy current content
   * to the before image.
   */
  virtual void SetBeforeImage() = 0;
};
}
