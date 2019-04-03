#include <vector>
#include "table.h"
#include <string>

namespace emerald {
    class Catalog {
        private:
          std::vector<Table*> TableList;
        public:
          Catalog();
          void AddTable(DbFile* file, std::string name, std::string pkeyField);
          void AddTable(DbFile* file, std::string name);
          void AddTable(DbFile* file);
          int get_table_id(std::string name);
          TupleDesc* GetTupleDesc(int tableid);
          std::vector<Table*> get_tables();
          std::string GetPrimaryKey(int tableid);
          Iterator<Integer> TableIdIterator();
          std::string GetTableName(int id);
          void Clear();
          void LoadSchema()
    }
}

