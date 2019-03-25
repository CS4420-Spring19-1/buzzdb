#pragma once

#include <unordered_map>
#include <vector>
#include "field.h"
#include "table.h"

namespace emerald {
    class Database {
        private:
            std::unordered_map<std::string, int> tableIds;
            std::vector<Table*> tables;
        public:
            Database();

            void createTable(std::string table_name, std::vector<std::string> column_names, std::vector<std::string> column_types, Table::storageType type);

            Table* getTable(int index);

            std::vector<Table*> getTables();

            std::unordered_map<std::string, int> getTableIds();

            void printTable(std::string table_name);

            Table* getTableRef(std::string table_name);

            int getTableId(std::string table_name);

            Field* get_field(int table_id, int tuple_id, int column_id);
    };
};
