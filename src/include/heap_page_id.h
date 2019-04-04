#pragma once

#include "page_id.h"

namespace emerald {
class HeapPageId : public PageId {
 public:
  HeapPageId();

  HeapPageId(int table_id, int page_number);

  int get_table_id();

  int get_page_number();

  virtual void Serialize(int rep[]);

  bool operator==(HeapPageId other);

 private:
  int table_id;
  int page_number;
};
}