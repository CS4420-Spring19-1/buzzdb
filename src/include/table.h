#pragma once

#include "table_descriptor.h"
#include "tuple.h"
#include <unordered_map>

namespace emerald{
    class Table {
        public:
            enum storageType {
                ROW_STORE,
                COLUMN_STORE
            };
            Table();
            Table(storageType type);
            void setTableDesc(std::vector<std::string> column_names, std::vector<std::string> column_types);
            void printTableDesc();
            virtual void printTable(){};
            void insertTuple(Tuple* tuple);
            TableDescriptor* getTableDescriptor();
            Table::storageType getStorageType();
        private:
            TableDescriptor* tableDesc;
            storageType type;        
    };
};