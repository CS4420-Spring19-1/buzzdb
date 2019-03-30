#pragma once

#include "table_descriptor.h"
#include "tuple.h"
#include <unordered_map>

namespace emerald {
class HeapPageId : public PageId {
 public:

  HeapPageId(int table_id, int page_number);

  virtual ~HeapPageId();

  int get_table_id();

  int get_page_number();

  int getHashCode();

  bool operator==(HeapPageId other);

  std::vector<int> serialize();

 private:
  int table_id;
  int page_number;
};
}