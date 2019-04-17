#include "heap_file_iterator.h"
#include "database.h"

namespace emerald {
HeapFileIterator::HeapFileIterator(TransactionId & tid, HeapFile * file) {
  this->current_tuple = nullptr;
  this->page_index = -1;
  this->tid = tid;
  this->file = file;
}

void HeapFileIterator::Open() {
  page_index = 0;
  current_tuple = nullptr;
}

bool HeapFileIterator::HasNext() {
  // Implementation incomplete: difficulties with file IO in C++
  return false;
}

Tuple * HeapFileIterator::Next() {
  // Implementation incomplete: difficulties with file IO in C++
}

void HeapFileIterator::Rewind() {
  page_index = 0;
  current_tuple = nullptr;
}

void HeapFileIterator::Close() {
  page_index = -1;
  current_tuple = nullptr;
}
}
