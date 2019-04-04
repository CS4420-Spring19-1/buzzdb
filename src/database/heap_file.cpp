#include <cmath>
#include "bufferpool.h"
#include "heap_file.h"

namespace emerald {
HeapFile::HeapFile(FILE * file, TupleDesc td) {
  this->file = file;
  this->td = td;
}

FILE * HeapFile::get_file() {
  return file;
}

uint32_t HeapFile::get_id() {
  return reinterpret_cast<uint32_t>(file);
}

TupleDesc HeapFile::get_tuple_desc() {
  return td;
}

Page * HeapFile::ReadPage(PageId * pid) {
}

void HeapFile::WritePage(Page * page) {
}

int HeapFile::get_num_pages() {
  return (int) ceil(ftell(file) / BufferPool.getPageSize());
}

std::vector<Page> HeapFile::AddTuple(TransactionId tid, Tuple t) {
}

Page * HeapFile::DeleteTuple(TransactionId tid, Tuple t) {
}

DbFileIterator HeapFile::Iterator(TransactionId tid) {
  DbFileIterator iterator = new HeapFileIterator(tid, this);
  return iterator;
}
}
