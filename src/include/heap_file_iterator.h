#pragma once

#include "table_descriptor.h"
#include "tuple.h"
#include <unordered_map>

namespace emerald {
class HeapFileIterator : public DbFileIterator {
 public:
  HeapFileIterator();

  HeapFileIterator(TransactionId tid, HeapFile f);

  virtual ~HeapFileIterator();

  void open();

  bool hasNext();

  tuple next();

  void restart();

  void close();

 private:
  Iterator<tuple> iterator;
  int pageIndex;
  TransactionId tid;
  HeapFile file;
};
}