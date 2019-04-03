#include <cmath>
#include <iostream>
#include "heap_page.h"

namespace emerald {
heap_page::heap_page(heap_page_id id, std::byte data[]) {
  this->pid = id;
  this->td = database::get_catalog().get_tuple_desc(id.get_table_id());
  this->numSlots = get_num_tuples();
  //DataInputStream dis = new DataInputStream(new ByteArrayInputStream(data));
  this->read_index = 0;

  this->header = new std::byte[get_header_size()];
  for (int i = 0; i < sizeof(header) / sizeof(header[0]); i++) {
    header[i] = data[read_index];
    read_index++;
  }

  this->tuples = new tuple[numSlots];
  try {
    // allocate and read the actual records of this page
    for (int i = 0; i < sizeof(tuples) / sizeof(tuples[0]); i++) {
      /* ReadNextTuple is not declared
      tuples[i] = ReadNextTuple(data, i);
      */
    }
  } catch (std::exception e) {
    std::cout << "Exception occurred";
  }

  set_before_image();
}

heap_page_id::heap_page_id heap_page::get_id() {
  return pid;
}

transaction_id heap_page::get_id_of_last_dirty_transaction() {
  // some code goes here
  // return null;
}

void heap_page::mark_dirty(bool dirty, transaction_id tid) {
}

heap_page::heap_page heap_page::get_before_image() {
  try {
    std::byte * old_data_ref = nullptr;
    old_data_ref = old_data;
    return new heap_page(pid, old_data_ref);
  } catch (std::exception e) {
    /*
    System.exit(1);
    */
  }
}

void heap_page::set_before_image() {
}

int heap_page::get_num_tuples() {
  double page_size = (double) database.get_buffer_pool().get_page_size() * 8;
  double tuple_size = (double) (td.get_size() * 8 + 1);
  double res = page_size / tuple_size;
  return (int) floor(res);
}

int heap_page::get_header_size() {
  double res = (double) numSlots / (double) 8;
  return (int) ceil(res);
}

/*
Tuple HeapPage::ReadNextTuple(byte[] data, int slotId) {
  if (!isSlotUsed(slotId)) {
    for (int i = 0; i < td.getSize(); i++) {
      try {
        readIndex++;
      } catch (IOException e) {
        throw new NoSuchElementException("error reading empty tuple");
      }
    }
    return null;
  }

  // read fields in the tuple
  tuple t = new tuple(td);
  RecordId rid = new RecordId(pid, slotId);
  t.setRecordId(rid);
  try {
    for (int j = 0; j < td.numFields(); j++) {
      field f = td.getFieldType(j).parse(dis);
      t.setField(j, f);
    }
  } catch (Exception e) {
    throw new NoSuchElementException("parsing error!");
  }
  return t;
}
*/

void heap_page::get_page_data(std::byte rep[]) {
}

void heap_page::create_empty_pageData(std::byte rep[]) {
  /*
  int len = BufferPool.getPageSize();
  return new byte[len];
  */
}

void heap_page::DeleteTuple(tuple t) {
}

void heap_page::insert_tuple(tuple t) {
}

void heap_page::add_tuple(tuple t) {
}

int heap_page::get_num_emptySlots() {
  int count = 0;
  for (int i = 0; i < sizeof(tuples) / sizeof(tuples[0]); ++i) {
    if (!IsSlotUsed(i))
      count++;
  }
  return count;
}

bool heap_page::is_slot_used(int i) {
  int x = i / 8;
  int y = i % 8;

  /* Error here
  return ((header[x] >> y) & 1) == 1;
  */
}

void heap_page::set_slot(int i, bool value) {
}

/* Not implemented
Iterator<tuple> HeapPage::iterator() {
  std::vector<tuple> arr = new std::vector<tuple>();
  for (tuple t : tuples) {
    if (t != null)
      arr.push_back(t);
  }
  return arr.iterator();
}
*/
}
