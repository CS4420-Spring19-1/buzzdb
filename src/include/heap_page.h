#pragma once

#include "heap_page_id.h"
#include "page.h"
#include "transaction_id.h"
#include "tuple.h"

namespace emerald {
/**
 * This class stores pages of HeapFiles and implements the Page interface that
 * is used by the BufferPool class/
 */
class heap_page : public page {
 public:
  heap_page();

  heap_page(heap_page_id id, std::byte data[]);

  heap_page_id get_id();

  transaction_id get_id_of_last_dirty_transaction() override;

  void mark_dirty(bool dirty, transaction_id tid) override;

  heap_page get_before_image();

  void set_before_image() override;

  int get_num_tuples();

  int get_header_size();

  /* Not implemented
  Tuple ReadNextTuple(DataInputStream dis, int slotId)();
  */

  void get_page_data(std::byte rep[]);

  static void create_empty_pageData(std::byte rep[]);

  void delete_tuple(tuple t);

  void insert_tuple(tuple t);

  void add_tuple(tuple t);

  int get_num_emptySlots();

  bool is_slot_used(int i);

  void set_slot(int i, bool value);

  /* Not implemented
  Iterator<tuple> iterator();
  */

 private:
  HeapPageId pid;
  TupleDesc td;
  std::byte * header;
  Tuple * tuples;
  int numSlots;
  std::byte * old_data;

  // byte oldDataLock = new byte(0);
  int read_index;
};
}
