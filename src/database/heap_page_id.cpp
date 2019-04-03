#include "heap_page_id.h"

namespace emerald {
heap_page_id::heap_page_id() {
}

heap_page_id::heap_page_id(int table_id, int page_number) {
  this->table_id = table_id;
  this->page_number = page_number;
}

int heap_page_id::get_table_id() {
  return table_id;
}

int heap_page_id::get_page_number() {
  return page_number;
}

bool heap_page_id::operator==(heap_page_id other) {
  return table_id == other.table_id && page_number == other.page_number;
}

void heap_page_id::Serialize(int rep[]) {
  rep[0] = this->table_id;
  rep[1] = this->page_number;
}
}
