#include "heap_file.h"

namespace emerald {
heap_file::heap_file(FILE * file, tuple_desc td) {
  this->file = file;
  this->td = td;
}

FILE * heap_file::get_file() {
  return file;
}

uint32_t heap_file::get_id() {
  return reinterpret_cast<uint32_t>(file);
}

tuple_desc heap_file::get_tuple_desc() {
  return td;
}

page heap_file::read_page(page_id pid) {
}

void heap_file::write_page(page page) {
}

int heap_file::num_pages() {
  return (int)ceil(ftell(file) / BufferPool.getPageSize());
}

std::vector<page> heap_file::add_tuple(transaction_id tid, tuple t) {
}

page heap_file::delete_tuple(transaction_id tid, tuple t) {
}

db_file_iterator heap_file::iterator(transaction_id tid) {
  db_file_iterator iterator = new heap_file_iterator(tid, this);
  return iterator;
}
}
