#include "catalog.h"

namespace emerald {
Catalog::Catalog() {
  names = new std::unordered_map<int, std::string>();
  db_fields = new std::unordered_map<int, DbFile *>();
  p_fields = new std::unordered_map<int, std::string>();
}

Catalog::~Catalog() {
  delete names;
  delete db_fields;
  delete p_fields;
}

void Catalog::AddTable(DbFile * file,
                       std::string name,
                       std::string p_key_field) {
  int table_id = file->get_id();

  // follow devinz's code 
  // maybe we can just use iter.find() here

  /**
   * To reduce pointer chasing, these pointers are derefenced once
   * at the start of the function.
   */
  std::unordered_map<int, std::string> names_object = *names;
  std::unordered_map<int, DbFile *> db_fields_object = *db_fields;
  std::unordered_map<int, std::string> p_fields_object = *p_fields;

  for (auto const & elem: names_object) {
    int id = elem.first;
    if (names_object[id] == name) {
      if (id != table_id) {
        names_object.erase(id);
        db_fields_object.erase(id);
        p_fields_object.erase(id);
      }
      break;
    }
  }
  names_object[table_id] = name;
  db_fields_object[table_id] = file;
  p_fields_object[table_id] = p_key_field;
}

void Catalog::AddTable(DbFile * file, std::string name) {
  AddTable(file, name, "");
}

int Catalog::get_table_id(std::string name) {
  std::unordered_map<int, std::string> names_object = *names;

  for (auto const & elem: names_object) {
    int id = elem.first;
    if (names_object[id] == name) {
      return id;
    }
  }
  // throw new NoSuchElementException();
}

TupleDesc Catalog::get_tuple_desc(int table_id) {
  if (db_fields->count(table_id)) {
    return (*db_fields)[table_id]->get_tuple_desc();
  }
  // throw new NoSuchElementException();
}

std::string Catalog::get_table_name(int table_id) {
  if (names->count(table_id)) {
    return (*names)[table_id];
  }
  // throw new NoSuchElementException();
}

DbFile * Catalog::get_db_file(int table_id) {
  std::unordered_map<int, DbFile *> db_fields_object = *db_fields;

  if (db_fields_object.count(table_id)) {
    return db_fields_object[table_id];
  }

  for (auto const & elem: db_fields_object) {
    int id = elem.first;
    // std::cout << "has:\t " << id << " " << names[id] << std::endl;
  }
  // std::cout << table_id << std::endl;
  // throw new NoSuchElementException();
}

std::string Catalog::get_primary_key(int table_id) {
  if (p_fields->count(table_id)) {
    return (*p_fields)[table_id];
  }
  // throw new NoSuchElementException();
}

std::unordered_map<int, DbFile *>::iterator Catalog::TableIdIterator() {
  std::unordered_map<int, DbFile *>::iterator iter = db_fields->begin();
  return iter;
}

void Catalog::Clear() {
  names->clear(); 
  db_fields->clear(); 
  p_fields->clear();
}

void Catalog::LoadSchema() {
  // complicated!!!
}
}