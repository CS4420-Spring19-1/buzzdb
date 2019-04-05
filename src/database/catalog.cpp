#include "catalog.h"

namespace emerald {
Catalog::Catalog() {}

std::vector<Table*> Catalog::get_tables() {
  return TableList;
}

void Catalog::AddTable(DbFile* file, std::string name, std::string pkeyField) {
  Table* tab = new Table(file, name, pkeyField);
  TableList.push_back(file);
}

int Catalog::get_table_id(std::string name) {
  for (int i=0; i<TableList.size(); i++) {
    if (TableList[i].name == name) {
      return TableList[i].file->get_id();
    }
  }
  // throw new NoSuchElementException();
}

std::string Catalog::get_table_name(int table_id) {
  for (int i=0; i<TableList.size(); i++) {
    if (TableList[i].file->get_id() == table_id) {
      return TableList[i].name;
    }
  }

  // throw new NoSuchElementException();
}

TupleDesc * Catalog::get_tuple_desc(int table_id) {
  for (int i = 0; i < TableList.size(); i++) {
    if (TableList[i].file->get_id() == table_id) {
      return TableList[i].file->getTupleDesc();
    }
  }
  // throw new NoSuchElementException();
}

DbFile * get_db_file(int table_id) {
}

std::string Catalog::GetPrimaryKey(int tableid) {
  for (int i=0; i<TableList.size(); i++) {
    if (TableList[i].file->get_id() == tableid) {
      return TableList[i].file->pkeyField;
    }
  }
  // throw new NoSuchElementException();
}

Iterator Catalog::TableIdIterator() {
  std::vector<int> lst;
  for (Table* tab: TableList) {
    lst.push_back(tab.file->get_id());
  }

  // Iterator<Integer> it = lst.iterator();
  // return it
}

void Catalog::Clear() {
  TableList.clear();
}

void Catalog::LoadSchema() {
  // complicated!!!
}
}