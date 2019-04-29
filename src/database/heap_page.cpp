#include <cstring>
#include "database.h"
#include "heap_page.h"
#include "db_exception.h"
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
      tuples.push_back(ParseNextTuple(&byte_stream, i));
    }
  } catch (NoSuchElementException e) {
    // print stack trace
  }

  SetBeforeImage();
}

HeapPage::~HeapPage() {
  for (int slot_index = 0; slot_index < number_of_slots; slot_index++) {
    delete tuples.at(slot_index);
  }

  delete[] header;
  delete[] old_data;
  delete id_of_transaction_that_dirtied_page;
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

void HeapPage::CreatePageDataRepresentation(unsigned char * rep) {
  std::stringstream byte_stream;

  // write header to stream
  // might not be correct to read whole array into stream
  // how about the ending characters in an array?
  try {
    // correctness needs to be checked
    byte_stream << *header;
  } catch (std::exception io_exception) {
    // change catch type
    // print stack trace
  }

  // write tuples to stream
  for (int slot_index = 0; slot_index < number_of_slots; slot_index++) {
    // slot has no tuple in it; add empty tuple to stream
    if (!IsSlotUsed(slot_index)) {
      for (int i = 0; i < table_schema.get_size(); i++) {
        try {
          byte_stream << '0';
        } catch (std::exception io_exception) {
          // change catch type
          // print stack trace
        }
      }
      continue;
    }

    // slot has a tuple; add it to stream
    Tuple * tuple_at_slot_index = tuples.at(slot_index);
    for (int field_index = 0;
         field_index < table_schema.get_number_fields();
         field_index) {
      Field * field = tuple_at_slot_index->get_field(field_index);
      try {
        field->Serialize(&byte_stream);
      } catch (std::exception io_exception) {
        // change catch type
        // print stack trace
      }
    }
  }

  // add padding to stream: fill the remaining space with zeroes
  // the number of elements in the byte array should = BufferPool::PAGE_SIZE.
  int padding_length = BufferPool::PAGE_SIZE
                     - (get_header_size()
                     + table_schema.get_size() * number_of_slots);
  unsigned char padding[padding_length] = {0};

  try {
    byte_stream << padding;
  } catch (std::exception io_exception) {
    // change catch type
    // print stack trace
  }

  /* flush byte stream: necessary?
  try {
    // flush byte stream
  } catch (std::exception io_exception) {
    // change catch type
    // print stack trace
  }
  */

  // extracting the byte_stream contents into an unsigned char array 
  std::string bs_string_rep = byte_stream.str();
  char * bs_char_array_rep = new char[BufferPool::PAGE_SIZE];
  strncpy(bs_char_array_rep, bs_string_rep.c_str(), BufferPool::PAGE_SIZE);

  rep = (unsigned char *) bs_char_array_rep;
}

void HeapPage::CreateEmptyPageDataRepresentation(unsigned char * rep) {
  rep = new unsigned char[BufferPool::PAGE_SIZE];
}

void HeapPage::DeleteTuple(Tuple * t) {
  if (pid == t->get_record_id()->get_page_id()) {
    int tuple_number = t->get_record_id()->get_tuple_number();

    if (tuple_number >= 0
        && tuple_number < number_of_slots
        && IsSlotUsed(tuple_number)) {
      SetSlot(tuple_number, false);
      // update tuple's record id
      delete t->get_record_id();
      t->set_record_id(nullptr);
    }
  }

  throw DbException("Tuple not found on page");
}

void HeapPage::InsertTuple(Tuple * t) {
  if (table_schema != t->get_tuple_desc()) {
    throw DbException("Schema mismatch: Table and tuple");
  }
  if (t->get_record_id() != nullptr) {
    if (pid == t->get_record_id()->get_page_id()) {
      throw DbException("Tuple already resides on this page.");
    }
    throw DbException("Tuple already resides on another page.");
  }

  for (int slot_index = 0; slot_index < number_of_slots; slot_index++) {
    if (!IsSlotUsed(slot_index)) {
      tuples.at(slot_index) = t;
      t->set_record_id(new RecordId(pid, slot_index));
      SetSlot(slot_index, true);
      return;
    }
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

// uses dynamic memory allocatiom: BEWARE
// update documentation to reflect this
// ensure that memory is released after use
Tuple * HeapPage::ParseNextTuple(std::stringstream * byte_stream_pointer,
                                  int slot_index) {
  // if the slot is not set to be used, move internal stream pointer forward
  // to next tuple, and return nullptr
  char input_char = 0;
  if (!IsSlotUsed(slot_index)) {
    for (int i = 0; i < table_schema.get_size(); i++) {
      try {
        byte_stream_pointer->get(input_char);
      } catch (std::exception io_exception) {
        // change catch type
        throw NoSuchElementException("Error parsing empty tuple.");
      }
    }
    return nullptr;
  }

  // otherwise, parse the tuple.
  Tuple * next_tuple = new Tuple(table_schema);
  RecordId * rid = new RecordId(pid, slot_index);
  next_tuple->set_record_id(rid);
  
  try {
    for (int field_index = 0;
         field_index < table_schema.get_number_fields();
         field_index++) {
      Field::Type field_type = table_schema.get_field_type(field_index);
      Field * parsed_field = ParseIntoField(byte_stream_pointer, field_type);
      // bad design; introduces coupling with Field class and its subclasses
      next_tuple->set_field(field_index, parsed_field);
    }
  } catch (std::exception e) {
    // change catch type
    throw NoSuchElementException("Error parsing tuple.");
  }

  return next_tuple;
}

Field * HeapPage::ParseIntoField(std::stringstream * byte_stream_pointer,
                                 Field::Type field_type) {
}
}
