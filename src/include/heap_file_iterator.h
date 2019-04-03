#pragma once

#include <unordered_map>

namespace emerald {
class heap_file_iterator : public db_file_iterator {
 public:
  heap_file_iterator();

  heap_file_iterator(transaction_id tid, heap_file f);

  virtual ~heap_file_iterator();

  void open();

  bool hasNext();

  tuple next();

  void restart();

  void close();

 private:
  iterator<tuple> iterator;
  int page_index;
  transaction_id tid;
  heap_file file;
};
}