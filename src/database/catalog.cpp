#include "catalog.h"

namespace emerald {
Catalog::Catalog() {
  names = new std::unordered_map<int, std::string>();
  db_fields = new std::unordered_map<int, DbFile*>();
  p_fields = new std::unordered_map<int, std::string>();
}

Catalog::~Catalog() {
  delete names;
  names = nullptr;
  delete db_fields;
  db_fields = nullptr;
  delete p_fields;
  p_fields = nullptr;
}

void Catalog::AddTable(DbFile* file, std::string name, std::string pkeyField) {
  int table_id = file->get_id();

  // follow devinz's code 
  // many be we can just use iter.find() here
  for (auto const& elem: names) {
    int id = elem.first;
    if (names[id] == name) {
      if (id != table_id) {
        names.erase(id);
        db_fields.erase(id);
        p_fields.erase(id);
      }
      break;
    }
  }
  names[table_id] = name;
  db_fields[table_id] = file;
  p_fields[table_id] = pkeyField;
}

void Catalog::AddTable(DbFile* file, std::string name) {
  AddTable(file, name, "");
}

void Catalog::AddTable(DbFile* file) {
  // addTable(file, (UUID.randomUUID()).toString());
}

int Catalog::get_table_id(std::string name) {
  for (auto const& elem: names) {
    int id = elem.first;
    if (name[id] == name) {
      return id;
    }
  }
  // throw new NoSuchElementException();
}
TupleDesc * Catalog::get_tuple_desc(int table_id) {
  if (db_fields.count(table_id)) {
    return db_fields[table_id]->get_tuple_desc();
  }
  // throw new NoSuchElementException();
}

std::string Catalog::get_table_name(int table_id) {
  if (names.count(table_id)) {
    return names[table_id];
  }
  // throw new NoSuchElementException();
}

DbFile * get_db_file(int table_id) {
  if (db_fields.count(table_id)) {
    return db_fields[table_id];
  }
  for (auto const& elem: db_fields) {
    int id = elem.first;
    std::cout << "has:\t " << id << " " << names[id] << std::endl;
  }
  std::cout << table_id << std::endl;
  // throw new NoSuchElementException();
}

std::string Catalog::GetPrimaryKey(int table_id) {
  if (p_fields.count(table_id)) {
    return p_fields[table_id];
  }
  // throw new NoSuchElementException();
}

std::unordered_map<int, DbFile*>::iterator Catalog::TableIdIterator() {
  std::unordered_map<int, DbFile*>::iter = db_fields.begin();
  return iter;
}

void Catalog::Clear() {
  names.clear();
  db_fields.clear();
  p_fields.clear();
}

void Catalog::LoadSchema() {
  // complicated!!!
}
}