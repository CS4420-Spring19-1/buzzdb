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
            void printTableDesc() const;
            virtual void print() const{};
            TableDescriptor* getTableDescriptor() const;
            Table::storageType getStorageType() const;
            void copyTableDesc(TableDescriptor* table_desc);
            void merge_table_desc(TableDescriptor* table_desc);
            virtual int size() const;
            virtual void copy_tuples(Table* table);
        private:
            TableDescriptor* tableDesc;
            storageType type;        
    };
};