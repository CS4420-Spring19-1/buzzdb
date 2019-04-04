#include "seqscan.h"

namespace emerald {
SeqScan::SeqScan(TransactionId* tid, int table_id, std::string table_alias) {
  this->tid = tid;
  this->table_id = table_id;
  this->table_alias = table_alias;
}

SeqScan::SeqScan(TransactionId* tid, int table_id) {
  // this(tid, tableid, Database.getCatalog().getTableName(tableid));
}

std::string SeqScan::get_table_name {
  // return Database.getCatalog().getTableName(tableid);
}

std::string SeqScan::get_alias {
  return table_alias;
}

void SeqScan::Reset(int table_id, ) {
  this->table_id = table_id;
  this->table_alias = table_alias;
}

void SeqScan::Open() {
  iterator = Database.getCatalog().getDatabaseFile(tableid).iterator(tid);
  iterator->open();
}

TupleDesc* SeqScan::get_tuple_desc() {
  // return Database.getCatalog().getTupleDesc(tableid);
}

bool SeqScan::HasNext() {
  if (iterator == NULL) return false;
  return iterator->hasNext();
}

Tuple* SeqScan::Next() {
  if (iterator == NULL) {
    // throw new NoSuchElementException();
  }
  Tuple* t = iterator->Next();

  if (t == NULL) {
    // throw new NoSuchElementException();
  }

  return t;
}

void SeqScan::Close() {
  iterator = NULL;
}

void SeqScan::Rewind() {
  Close();
  Open();
}
}

