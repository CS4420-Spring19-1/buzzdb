#include "database.h"
#include "heap_page.h"
#include "no_such_element_exception.h"

namespace buzzdb {
/**
 * Implementation is possibly wrong:
 * - Interactions between sstreams and unsigned chars need to be tested
 */
HeapPage::HeapPage(HeapPageId & pid, unsigned char data[])
  : pid(pid),
    table_schema(Database::get_catalog()->get_tuple_desc(pid.get_table_id())),
    number_of_slots(get_number_of_tuples()),
    header(new unsigned char[get_header_size()]),
    tuples(0),
    old_data(nullptr) {
  std::stringstream byte_stream;
  byte_stream << data;

  char input_char = 0;
  for (int i = 0; i < get_header_size(); i++) {
    // TODO: handle IO exception
    byte_stream.get(input_char);
    header[i] = input_char;
  }

  try {
    for (int i = 0; i < number_of_slots; i++) {
      tuples.push_back(ReadInNextTuple(&byte_stream, i));
    }
  } catch (NoSuchElementException e) {
    // print stack trace
  }

  SetBeforeImage();
}

const PageId & HeapPage::get_id() const {
  return pid;
}

const TransactionId * HeapPage::get_id_of_last_dirty_transaction() const {
  return id_of_transaction_that_dirtied_page;
}

void HeapPage::MarkDirty(bool dirty, TransactionId * tid) {
  id_of_transaction_that_dirtied_page = dirty ? tid : nullptr;
}

// uses dynamic memory allocatiom: BEWARE
// update documentation to reflect this
// ensure that memory is released after use
Page * HeapPage::GetBeforeImage() {
  try {
    return new HeapPage(pid, old_data);
  } catch (std::exception io_exception) {
    // implement properly
  }
  return nullptr;
}

void HeapPage::SetBeforeImage() {
  delete[] old_data;
  CreatePageDataRepresentation(old_data);
}

int HeapPage::get_number_of_tuples() {
  // bitwise shift left 3 bits to convert from bytes to bits
  int page_size_in_bits = Database::get_buffer_pool()->PAGE_SIZE << 3;
  int tuple_size_in_bits = table_schema.get_size() << 3;
  int padding_bit = 1;

  return page_size_in_bits / (tuple_size_in_bits + padding_bit);
}

int HeapPage::get_header_size() {
  return (number_of_slots + 7) >> 3;
}

Tuple HeapPage::ReadInNextTuple(std::stringstream * byte_stream_pointer,
                                int slot_index) {
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

void HeapPage::CreatePageDataRepresentation(unsigned char * rep) {
}

  /* flush byte stream: necessary?
  int len = BufferPool.getPageSize();
  return new byte[len];
void HeapPage::CreateEmptyPageDataRepresentation(unsigned char * rep) {
void HeapPage::DeleteTuple(Tuple * t) {
}

void HeapPage::InsertTuple(Tuple * t) {
}

  for (int slot_index = 0; slot_index < number_of_slots; slot_index++) {
}

  throw DbException("This page is full.");
}

int HeapPage::GetNumEmptySlots() {
  int count = 0;
  for (int i = 0; i < sizeof(tuples) / sizeof(tuples[0]); ++i) {
    if (!IsSlotUsed(i))
      count++;
  }
  return count;
}

bool HeapPage::IsSlotUsed(int index) {
  // why?
  return (header[index >> 3] & (1 << (index & 7))) != 0;
}

void HeapPage::SetSlot(int index, bool updated_status_of_slot) {
  // why?
  if (updated_status_of_slot) {
    header[index >> 3] |= (1 << (index & 7));
  } else {
    header[index >> 3] &= ~(1 << (index & 7));
  }
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
Field * HeapPage::ParseIntoField(Field::Type field_type,
                                 std::stringstream * byte_stream_pointer) {
}
}
