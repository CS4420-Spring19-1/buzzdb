#pragma once

#include "page_id.h"

namespace emerald {
class heap_page_id : public page_id {
 public:
  heap_page_id();

  heap_page_id(int table_id, int page_number);

  int get_table_id();

  int get_page_number();

  virtual void Serialize(int rep[]);

  bool operator==(heap_page_id other);

 private:
  int table_id;
  int page_number;
};
}