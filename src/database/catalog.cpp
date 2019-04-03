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

  void Catalog::AddTable(DbFile* file, std::string name) {
    AddTable(file, name, "");
  }

  void Catalog::AddTable(DbFile* file) {
    // addTable(file, (UUID.randomUUID()).toString());
  }

  int Catalog::get_table_id(std::string name) {
    for (int i=0; i<TableList.size(); i++) {
      if (TableList[i].name == name) {
        return TableList[i].file->get_id();
      }
    }
    // throw new NoSuchElementException();
  }

  TupleDesc* Catalog::GetTupleDesc(int tableid) {
    for (int i=0; i<TableList.size(); i++) {
      if (TableList[i].file->get_id() == tableid) {
        return TableList[i].file->getTupleDesc();
      }
    }
    // throw new NoSuchElementException();
  }

  std::string Catalog::GetPrimaryKey(int tableid) {
    for (int i=0; i<TableList.size(); i++) {
      if (TableList[i].file->get_id() == tableid) {
        return TableList[i].file->pkeyField;
      }
    }
    // throw new NoSuchElementException();
  }
  
  Iterator<Integer> Catalog::TableIdIterator() {
    std::vector<int> lst;
    for (Table* tab: TableList) {
      lst.push_back(tab.file->get_id());
    }

    // Iterator<Integer> it = lst.iterator();
    // return it
  }

  std::string Catalog::GetTableName(int id) {
    for (int i=0; i<TableList.size(); i++) {
      if (TableList[i].file->get_id() == id) {
        return TableList[i].name;
      }
    }

    // throw new NoSuchElementException();
  }

  void Catalog::Clear() {
    TableList.clear();
  }

  void Catalog::LoadSchema() {
    // fucking complicated!!!
  }
}