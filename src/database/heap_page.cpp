#include <cmath>
#include <iostream>
#include "database.h"
#include "heap_page.h"

namespace emerald {
HeapPage::HeapPage() {
}

/** Temporarily not available, as std::byte is only available in C++ 17
HeapPage::HeapPage(HeapPageId id, std::byte data[]) {
  this->pid = id;
  this->td = &(Database::get_catalog()->get_tuple_desc(id.get_table_id()));
  this->numSlots = get_num_tuples();
  //DataInputStream dis = new DataInputStream(new ByteArrayInputStream(data));
  this->read_index = 0;

  this->header = new std::byte[get_header_size()];
  for (int i = 0; i < sizeof(header) / sizeof(header[0]); i++) {
    header[i] = data[read_index];
    read_index++;
  }

  this->tuples = new Tuple[numSlots];
  try {
    // allocate and read the actual records of this page
    for (int i = 0; i < sizeof(tuples) / sizeof(tuples[0]); i++) {
      ReadNextTuple is not declared
      tuples[i] = ReadNextTuple(data, i);
    }
  } catch (std::exception e) {
    std::cout << "Exception occurred";
  }

  SetBeforeImage();
}
*/

HeapPageId * HeapPage::get_id() {
  return &pid;
}

TransactionId * HeapPage::GetIdOfLastDirtyTransaction() {
  // some code goes here
  // return null;
}

void HeapPage::MarkDirty(bool dirty, TransactionId & tid) {
}

HeapPage * HeapPage::GetBeforeImage() {
  try {
    std::byte * old_data_ref = nullptr;
    old_data_ref = old_data;
    // return new HeapPage(pid, old_data_ref);
    return new HeapPage();
  } catch (std::exception e) {
    /*
    System.exit(1);
    */
  }
}

void HeapPage::SetBeforeImage() {
}

int HeapPage::get_num_tuples() {
  double pagesize = (double) Database::get_buffer_pool()->get_page_size() * 8;
  double tuplesize = (double) (td->get_size() * 8 + 1);
  double res = pagesize / tuplesize;
  return (int) floor(res);
}

int HeapPage::get_header_size() {
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

void HeapPage::GetPageData(std::byte rep[]) {
}

void HeapPage::CreateEmptyPageData(std::byte rep[]) {
  int len = BufferPool.getPageSize();
  return new byte[len];
}
*/

void HeapPage::DeleteTuple(Tuple t) {
}

void HeapPage::InsertTuple(Tuple t) {
}

void HeapPage::AddTuple(Tuple t) {
}

int HeapPage::GetNumEmptySlots() {
  int count = 0;
  for (int i = 0; i < sizeof(tuples) / sizeof(tuples[0]); ++i) {
    if (!IsSlotUsed(i))
      count++;
  }
  return count;
}

bool HeapPage::IsSlotUsed(int i) {
  int x = i / 8;
  int y = i % 8;

  /* Error here
  return ((header[x] >> y) & 1) == 1;
  */
}

void HeapPage::SetSlot(int i, bool value) {
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
