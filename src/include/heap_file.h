#pragma once

#include <unordered_map>

namespace emerald {
/**
 * HeapFile is an implementation of a DbFile that stores a collection of tuples
 * in no particular order. Tuples are stored on pages, each of which is a fixed
 * size, and the file is simply a collection of those pages. HeapFile works
 * closely with HeapPage. The format of HeapPages is described in the HeapPage
 * constructor.
 */
class heap_file : public db_file {
 public:
  heap_file(FILE *file, tuple_desc td);

  virtual ~heap_file();

  File * get_file();

  uint32_t get_id();

  tuple_desc get_tuple_desc();

  page read_page(page_id pid);

  void write_page(page page);

  int num_pages();

  std::vector<page> add_tuple(transaction_id tid, tuple t);

  page delete_tuple(transaction_id tid, tuple t);

  db_file_iterator iterator(transaction_id tid);

 private:
  FILE * file;
  tuple_desc td;
};
}