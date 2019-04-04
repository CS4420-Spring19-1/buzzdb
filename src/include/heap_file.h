#pragma once

#include "db_file.h"
#include "db_file_iterator.h"
#include "page.h"
#include "tuple.h"

namespace emerald {
/**
 * HeapFile is an implementation of a DbFile that stores a collection of tuples
 * in no particular order. Tuples are stored on pages, each of which is a fixed
 * size, and the file is simply a collection of those pages. HeapFile works
 * closely with HeapPage. The format of HeapPages is described in the HeapPage
 * constructor.
 */
class HeapFile : public DbFile {
 public:
  HeapFile(FILE *file, TupleDesc td);

  virtual ~HeapFile();

  FILE * get_file();

  uint32_t get_id();

  TupleDesc get_tuple_desc();

  Page * ReadPage(PageId * pid);

  void WritePage(Page * page);

  int get_num_pages();

  std::vector<Page> AddTuple(TransactionId tid, Tuple t);

  Page * DeleteTuple(TransactionId tid, Tuple t);

  DbFileIterator Iterator(TransactionId tid);

 private:
  FILE * file;
  TupleDesc td;
};
}