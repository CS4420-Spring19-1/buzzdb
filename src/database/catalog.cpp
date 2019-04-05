#include "catalog.h"

namespace emerald {
Catalog::Catalog() {}

void Catalog::AddTable(DbFile* file, std::string name, std::string pkeyField) {
}

int Catalog::get_table_id(std::string name) {
  // throw new NoSuchElementException();
}

std::string Catalog::get_table_name(int table_id) {
  // throw new NoSuchElementException();
}

TupleDesc * Catalog::get_tuple_desc(int table_id) {
  // throw new NoSuchElementException();
}

DbFile * get_db_file(int table_id) {
}

std::string Catalog::GetPrimaryKey(int tableid) {
  // throw new NoSuchElementException();
}

Iterator Catalog::TableIdIterator() {
  std::vector<int> lst;

  // Iterator<Integer> it = lst.iterator();
  // return it
}

void Catalog::Clear() {
}

void Catalog::LoadSchema() {
  // complicated!!!
}
}