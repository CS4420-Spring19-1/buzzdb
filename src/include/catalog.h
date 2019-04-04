#pragma once

#include <vector>
#include <string>
#include "db_file.h"
#include "tuple_desc.h"

namespace emerald {
class Catalog {
 private:
  std::vector<Table*> TableList;
 public:
  Catalog();

  void AddTable(DbFile * file, std::string name, std::string p_key_field);

  int get_table_id(std::string name);

  std::string get_table_name(int table_id);

  TupleDesc * get_tuple_desc(int table_id);

  DbFile * get_db_file(int table_id);

  std::string GetPrimaryKey(int tableid);

  Iterator<Integer> TableIdIterator();

  void Clear();

  void LoadSchema();
};
}
