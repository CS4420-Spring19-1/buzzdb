#include "heap_page_id.h"

namespace emerald {
HeapPageId::HeapPageId() {
}

HeapPageId::HeapPageId(int table_id, int page_number) {
  this->table_id = table_id;
  this->page_number = page_number;
}

int HeapPageId::get_table_id() {
  return table_id;
}

int HeapPageId::get_page_number() {
  return page_number;
}

bool HeapPageId::operator==(HeapPageId other) {
  return table_id == other.table_id && page_number == other.page_number;
}

void HeapPageId::Serialize(int rep[]) {
  rep[0] = this->table_id;
  rep[1] = this->page_number;
}
}
