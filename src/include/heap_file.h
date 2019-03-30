#pragma once

#include "table_descriptor.h"
#include "tuple.h"
#include <unordered_map>

namespace emerald {
/**
 * HeapFile is an implementation of a DbFile that stores a collection of tuples
 * in no particular order. Tuples are stored on pages, each of which is a fixed
 * size, and the file is simply a collection of those pages. HeapFile works
 * closely with HeapPage. The format of HeapPages is described in the HeapPage
 * constructor.
 */
class HeapFile : public DBFile {
 public:
  HeapFile(File *file, TupleDesc td);

  virtual ~HeapFile();

  File * get_file();

  uint32_t get_id();

  TupleDesc get_tuple_desc();

  Page ReadPage(PageId pid);

  void WritePage(Page page);

  int NumPages();

  std::vector<Page> AddTuple(TransactionId tid, Tuple t);

  Page DeleteTuple(TransactionId tid, Tuple t);

  DBFileIterator Iterator(TransactionId tid);

 private:
  File * file;
  TupleDesc td;
};
}