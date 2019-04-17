#include "record_id.h"
#include "heap_page_id.h"

namespace buzzdb {
RecordId::RecordId(HeapPageId * pid, int tuple_number) {
  this->pid = pid;
  this->tuple_number = tuple_number;
}

int RecordId::get_tuple_number() const {
  return tuple_number;
}

HeapPageId* RecordId::get_page_id() const {
  return pid;
}

// bool RecordId::operator==(RecordId other) {
//   return this->pid->get_page_number() == other->get_page_id()->get_page_number()
//       && this->tuple_number == other.get_tuple_number();
// }

bool RecordId::Equal(RecordId* other) {
  return this->pid->get_page_number() == other->get_page_id()->get_page_number()
      && this->tuple_number == other->get_tuple_number() 
      && this->pid->get_table_id() == other->get_page_id()->get_table_id();
}

}
