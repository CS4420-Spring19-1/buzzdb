#include "record_id.h"
#include <stdexcept>

namespace buzzdb {
RecordId::RecordId(PageId & pid, int tuple_number)
    : pid(pid), tuple_number(tuple_number) {
  if (tuple_number < 0) {
    throw std::invalid_argument("Tuple number cannot be negative.");
  }
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
