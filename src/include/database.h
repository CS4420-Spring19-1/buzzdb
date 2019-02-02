#pragma once

#include<unordered_map>
#include<vector>
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
    };
};