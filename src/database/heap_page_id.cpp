#include "heap_page_id.h"

namespace buzzdb {
HeapPageId::HeapPageId(int table_id, int page_number)
    : table_id(table_id), page_number(page_number) {
}

HeapPageId::HeapPageId(const HeapPageId & original)
    : table_id(original.table_id), page_number(original.page_number) {
}

int HeapPageId::get_table_id() const {
  return table_id;
}

int HeapPageId::get_page_number() const {
  return page_number;
}

std::array<int, 2> HeapPageId::Serialize() {
  std::array<int, 2> serialized_representation = {table_id, page_number};
  return serialized_representation;
}

bool HeapPageId::operator==(const PageId & other) {
  try {
    PageId & non_const_other = const_cast<PageId &>(other);
    HeapPageId & casted_other = dynamic_cast<HeapPageId &>(non_const_other);
    return table_id == casted_other.table_id && page_number == casted_other.page_number;
  } catch (const std::bad_cast & e) {
    return false;
  }
}

bool HeapPageId::operator!=(const PageId & other) {
  return !(*this == other);
}
}
