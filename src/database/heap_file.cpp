#include <cmath>
#include "buffer_pool.h"
#include "heap_file.h"
#include "heap_file_iterator.h"

namespace emerald {
HeapFile::HeapFile(FILE * file, TupleDesc td) {
  this->file = file;
  this->td = td;
}

FILE * HeapFile::get_file() {
  return file;
}

int HeapFile::get_id() const {
  return reinterpret_cast<uint32_t>(file);
}

TupleDesc & HeapFile::get_tuple_desc() const {
  return td;
}

int HeapFile::get_num_pages() {
  return (int) ceil(ftell(file) / BufferPool::get_page_size());
}

Page * HeapFile::ReadPage(PageId * pid) {
}

void HeapFile::WritePage(Page * page) {
}

std::vector<Page> HeapFile::AddTuple(TransactionId & tid, Tuple & t) {
}

Page * HeapFile::DeleteTuple(TransactionId & tid, Tuple & t) {
}

DbFileIterator * HeapFile::Iterator(TransactionId & tid) {
  // potential memory leak, should address somewhere
  DbFileIterator * iterator = new HeapFileIterator(tid, this);
  return iterator;
}
}
