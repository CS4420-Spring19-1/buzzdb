#pragma once

#include "heap_file.h"
#include "transaction_id.h"

namespace emerald {
/**
 * This class describes an iterator that is designed to iterate through the
 * tuples in a table, which is stored in a HeapFile object.
 */
class HeapFileIterator : public DbFileIterator {
 public:
  HeapFileIterator();

  HeapFileIterator(TransactionId & tid, HeapFile * file);

  ~HeapFileIterator();

  void Open() override;

  bool HasNext() override;

  Tuple * Next() override;

  void Rewind() override;

  void Close() override;

 private:
  Tuple * current_tuple;
  int page_index;
  TransactionId tid;
  HeapFile * file;
};
}