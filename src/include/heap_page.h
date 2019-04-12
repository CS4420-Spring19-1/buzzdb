#pragma once

#include "heap_page_id.h"
#include "page.h"
#include "transaction_id.h"
#include "tuple.h"

namespace emerald {
/**
 * This class stores pages of HeapFiles and implements the Page interface that
 * is used by the BufferPool class.
 * 
 * Some functions are not available because they use std::byte, which is only
 * available in C++ 17. Currently working on a different way to represent pages
 */
class HeapPage : public Page {
 public:
  HeapPage();

  // HeapPage(HeapPageId id, std::byte data[]);

  HeapPageId * get_id();

  TransactionId * GetIdOfLastDirtyTransaction() override;

  void MarkDirty(bool dirty, TransactionId & tid) override;

  HeapPage * GetBeforeImage();

  void SetBeforeImage() override;

  int get_num_tuples();

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
  TupleDesc * td;
  // std::byte * header;
  Tuple * tuples;
  int numSlots;
  // std::byte * old_data;

  // byte oldDataLock = new byte(0);
  int read_index;
};
}
