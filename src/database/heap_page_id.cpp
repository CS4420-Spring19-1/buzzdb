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

bool HeapPageId::operator==(const HeapPageId & other) {
  return table_id == other.table_id && page_number == other.page_number;
}

bool HeapPageId::operator!=(const HeapPageId & other) {
  return !(*this == other);
}

std::array<int, 2> HeapPageId::Serialize() {
  std::array<int, 2> serialized_representation = {table_id, page_number};
  return serialized_representation;
}
}
