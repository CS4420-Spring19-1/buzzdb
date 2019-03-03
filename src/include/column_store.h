#pragma once
#include "table.h"
#include "column.h"

namespace emerald
{
    class ColumnStore : public Table {
        private:
            std::vector<Column*> columns_; 
        public:
            ColumnStore(int table_id);
            void print() const;
            size_t size() const;
            void insert_tuple(std::vector<Field*> fields);
            std::vector<Column*> get_columns() const;
            Column* get_column(int index) const;
    };
} // emerald
