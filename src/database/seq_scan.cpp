#include "seq_scan.h"
#include "database.h"
#include "no_such_element_exception.h"

namespace buzzdb {
SeqScan::SeqScan(TransactionId & tid, int table_id, std::string table_alias) {
  this->db_file = Database::get_catalog()->get_db_file(table_id);
  this->iterator = this->db_file->Iterator(tid);
  this->table_alias = table_alias;
}

void SeqScan::Open() {
  this->iterator->Open();
}

bool SeqScan::HasNext() {
  if (iterator == nullptr) {
    return false;
  }
  return iterator->HasNext();
}

Tuple & SeqScan::Next() {
  if (iterator == nullptr) {
    throw NoSuchElementException("Iterator has no more tuples to read.");
  }

  Tuple * t = iterator->Next();
  if (t == nullptr) {
    throw NoSuchElementException("THe tuple retrieved by next is null.");
  }

  return *t;
}

void SeqScan::Close() {
  iterator = nullptr;
}

const TupleDesc & SeqScan::get_tuple_desc() const {
  return this->db_file->get_tuple_desc();
}

void SeqScan::Rewind() {
  iterator->Rewind();
}
}
