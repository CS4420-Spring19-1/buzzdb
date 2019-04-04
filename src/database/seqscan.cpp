#include "seqscan.h"
#include "database.h"

namespace emerald {
SeqScan::SeqScan(TransactionId & tid, int table_id, std::string table_alias) {
  this->db_file = Database::get_catalog()->get_db_file(table_id);
  this->iterator = this->db_file->Iterator(tid);
  this->table_alias = table_alias;
}

void SeqScan::Open() {
  this->iterator->Open();
}

TupleDesc & SeqScan::get_tuple_desc() {
  return this->db_file->get_tuple_desc();
}

bool SeqScan::HasNext() {
  if (iterator == nullptr) return false;
  return iterator->HasNext();
}

Tuple * SeqScan::Next() {
  if (iterator == nullptr) {
    // throw new NoSuchElementException();
  }
  Tuple * t = iterator->Next();

  if (t == nullptr) {
    // throw new NoSuchElementException();
  }

  return t;
}

void SeqScan::Close() {
  iterator = nullptr;
}

void SeqScan::Rewind() {
  iterator->Rewind();
}
}
