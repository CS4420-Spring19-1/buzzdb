#pragma once

#include "heap_file.h"
#include "transaction_id.h"


namespace emerald {
class HeapFileIterator : public DbFileIterator {
 public:
  HeapFileIterator();

  HeapFileIterator(TransactionId tid, HeapFile f);

  virtual ~HeapFileIterator();

  void Open();

  bool HasNext();

  Tuple Next();

  void Restart();

  void Close();

 private:
  Iterator<Tuple> iterator;
  int page_index;
  TransactionId tid;
  HeapFile file;
};
}