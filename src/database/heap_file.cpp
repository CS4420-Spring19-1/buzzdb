#include <cmath>
#include "buffer_pool.h"
#include "heap_file.h"
#include "heap_file_iterator.h"

namespace buzzdb {
HeapFile::HeapFile(FILE * file, TupleDesc td) {
  this->file = file;
  this->td = td;
}

FILE * HeapFile::get_file() {
  return file;
}

int HeapFile::get_id() const {
  /** not working, to be fixed
  return reinterpret_cast<uint32_t>(file);
  */
  return 0;
}

TupleDesc HeapFile::get_tuple_desc() const {
  return td;
}

int HeapFile::get_num_pages() {
  return (int) ceil(ftell(file) / BufferPool::get_page_size());
}

Page * HeapFile::ReadPage(PageId * pid) {
  // Implementation incomplete: difficulties with file IO in C++
  return nullptr;
}

void HeapFile::WritePage(Page * page) {
  // Implementation incomplete: difficulties with file IO in C++
}

std::vector<Page *> HeapFile::AddTuple(TransactionId & tid, Tuple & t) {
  // Implementation incomplete: difficulties with file IO in C++
  return std::vector<Page *>(0);
}

Page * HeapFile::DeleteTuple(TransactionId & tid, Tuple & t) {
  // Implementation incomplete: difficulties with file IO in C++
  return nullptr;
}

DbFileIterator * HeapFile::Iterator(TransactionId & tid) {
  // potential memory leak, should address somewhere
  DbFileIterator * iterator = new HeapFileIterator(tid, this);
  return iterator;
}
}
