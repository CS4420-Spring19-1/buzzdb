#include "heap_page_id.h"

namespace emerald {
HeapPageId::HeapPageId(int table_id, int page_number) {
  this->table_id = table_id;
  this->pageNo = page_number;
}

int HeapPageId::get_table_id() {
  return table_id;
}

int HeapPageId::get_page_number() {
  return pageNo;
}

int HeapPageId::getHashCode() {
  return table_id * pageNo;
}

bool operator==(HeapPageId other) {
  if (table_id == other.table_id && page_number == other.page_number) {
    return true;
  }
  else {
    return false;
  }
}

std::vector<int> HeapPageId::serialize() {
  int data[] = new int[2];
  data[0] = get_table_id();
  data[1] = get_page_number();

  return data;
}
}
