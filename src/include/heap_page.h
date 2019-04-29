#pragma once

#include "heap_page_id.h"
#include "page.h"
#include "transaction_id.h"
#include "tuple.h"

namespace buzzdb {
/**
 * The HeapPage class represents a page in a table implemented as a HeapFile.
 * - This class implements the Page interface.
 * 
 * Some functions are not available because they use std::byte, which is only
 * available in C++ 17. Currently working on a different way to represent pages
 */
class HeapPage : public Page {
 public:
  /**
   * Default constructor.
   */
  HeapPage();

  /**
   * Constructor.
  HeapPage(HeapPageId id, std::byte data[]);
   */

  /**
   * Returns the id of the page.
   */
  const PageId & get_id() const override;

  /**
   * Returns the transaction id of the last transaction that dirtied the page.
   * Returns null if the page is not dirty.
   */
  const TransactionId * get_id_of_last_dirty_transaction() const override;

  /**
   * Sets the dirty state of the page as dirtied by a particular transaction.
   */
  void MarkDirty(bool dirty, TransactionId & tid) override;

  /**
   * Returns a representation of the Page before any modifications were made to
   * it. Used by recovery.
   */
  Page * GetBeforeImage() override;

  /**
   * A transaction that wrote this Page just committed it. Copy current content
   * to the before image.
   */
  void SetBeforeImage() override;

  /**
   * Returns the number of tuples in the heap page.
   */
  int get_num_tuples();

  /**
   * Returns the size of the heap page's header.
   */
  int get_header_size();

  /* Not implemented
  Tuple ReadNextTuple(DataInputStream dis, int slotId)();
  */

  // void GetPageData(std::byte rep[]);

  // static void CreateEmptyPageData(std::byte rep[]);

  void DeleteTuple(Tuple t);

  void InsertTuple(Tuple t);

  void AddTuple(Tuple t);

  int GetNumEmptySlots();

  bool IsSlotUsed(int i);

  void SetSlot(int i, bool value);

  /* Not implemented
  Iterator<tuple> iterator();
  */

 private:
  HeapPageId pid;
  TupleDesc table_schema;
  std::vector<Tuple *> tuples;
  unsigned char * header;
  unsigned char * old_data;
  TransactionId * id_of_transaction_that_dirtied_page;
  int number_of_slots;

  // byte oldDataLock = new byte(0);
  int read_index;
};
}
