#include "record_id.h"

namespace emerald {
RecordId::RecordId(PageId * pid, int tuple_number) {
  this->pid = pid;
  this->tuple_number = tuple_number;
}

int RecordId::get_tuple_number() const {
  return tuple_number;
}

PageId & RecordId::get_page_id() const {
  return *pid;
}

bool RecordId::operator==(RecordId other) {
  return *(this->pid) == other.get_page_id()
      && this->tuple_number == other.get_tuple_number();
}
}
