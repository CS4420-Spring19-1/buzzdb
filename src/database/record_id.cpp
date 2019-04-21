#include "record_id.h"
#include "heap_page_id.h"

namespace buzzdb {
RecordId::RecordId(PageId & pid, int tuple_number)
    : pid(pid), tuple_number(tuple_number) {
}

int RecordId::get_tuple_number() const {
  return tuple_number;
}

const PageId & RecordId::get_page_id() const {
  return pid;
}

bool RecordId::operator==(const RecordId & other) {
  return pid == other.pid && tuple_number == other.tuple_number;
}

bool RecordId::operator!=(const RecordId & other) {
  return (*this == other);
}
}
