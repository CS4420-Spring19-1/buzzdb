#pragma once

#include "table_descriptor.h"
#include "tuple.h"
#include <unordered_map>

namespace emerald{
    class Table {
        public:
            enum storageType {
                ROW_STORE,
                COLUMN_STORE,
                JOIN_INDEX
            };
            Table();
            Table(int table_id, storageType type);
            void setTableDesc(int table_id, std::vector<std::string> column_names, std::vector<std::string> column_types);
            void printTableDesc() const;
            virtual void print() const=0;
            TableDescriptor* getTableDescriptor() const;
            Table::storageType getStorageType() const;
            void copyTableDesc(TableDescriptor* table_desc);
            void merge_table_desc(TableDescriptor* table_desc);
            virtual size_t size() const=0;
            int get_table_id() const;
            virtual ~Table();
        private:
            TableDescriptor* tableDesc;
            storageType type;  
            int table_id_;      
    };
};