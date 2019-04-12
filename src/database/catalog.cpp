#include "catalog.h"

namespace emerald {
Catalog::Catalog() {
  names = new std::unordered_map<int, std::string>();
  db_fields = new std::unordered_map<int, DbFile*>();
  p_fields = new std::unordered_map<int, std::string>();
}

  // throw new NoSuchElementException();
}

std::string Catalog::get_table_name(int table_id) {
  if (names.count(table_id)) {
    return names[table_id];
  }
  // throw new NoSuchElementException();
}



std::unordered_map<int, DbFile*>::iterator Catalog::TableIdIterator() {
  std::unordered_map<int, DbFile*>::iter = db_fields.begin();
  return iter;
}

void Catalog::Clear() {
}

void Catalog::LoadSchema() {
  // complicated!!!
}
}