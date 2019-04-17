#pragma once

#include "page_id.h"
#include "transaction_id.h"

namespace buzzdb {
/**
 * This is an interface used to represent pages that are resident in the
 *  BufferPool. Typically, DbFiles will read and write pages from disk.
 * 
 * Pages may be "dirty", meaning that they have been modified since they
 *  were last written out to disk.
 */
class Page {
 public:
  /*
   * Necessary for an interface class to ensure correct polymorphic deletion.
   */
  virtual ~Page();

  /**
   * Returns the id of the page.
   * The id is a unique identifier that can be used to look up the page on disc
   *  or to determine if the page is resident in the buffer pool.
   */
  virtual PageId * get_id() = 0;

  /**
   * Returns the TransactionId of the last transaction that dirtied the page.
   * Returns null if the page is not dirty.
   */
  virtual TransactionId * GetIdOfLastDirtyTransaction() = 0;

  /**
   * Sets the dirty state of the page as dirtied by a particular transaction.
   */
  virtual void MarkDirty(bool dirty, TransactionId & tid) = 0;
 
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
