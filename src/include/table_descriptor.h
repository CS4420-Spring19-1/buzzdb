#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "column_descriptor.h"

namespace emerald
{
   class TableDescriptor
   {
    private:
       std::vector<ColumnDescriptor*> columns_; 
    public:
        TableDescriptor();
        TableDescriptor(const TableDescriptor &tableDesc);
        TableDescriptor(int table_id, std::vector<std::string> column_names, std::vector<std::string> column_types);  
        void print() const;    
        int getColumnId(std::string column_name) const;
        field_type getColumnType(int index) const;
        void AppendColumns(std::vector<ColumnDescriptor*> columns);
        std::vector<ColumnDescriptor*> get_columns() const;
        ColumnDescriptor* get_column(std::string name) const; 
        ColumnDescriptor* get_column(int index) const;
   };
}; // emerald
