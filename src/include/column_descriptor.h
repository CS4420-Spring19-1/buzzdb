#pragma once

#include "field_type.h"
#include <string>

namespace emerald
{
    class ColumnDescriptor{
        private:
            int table_id_;
            int column_id_; //this is the column index in the original table
            std::string column_name_;
            field_type type_;
        public:
            ColumnDescriptor();

            ColumnDescriptor(int table_id, int column_id, std::string column_name, field_type type);

            std::string get_column_name() const;
            field_type get_column_type() const;
            int get_table_id() const;
            int get_column_id() const;

            ColumnDescriptor(const ColumnDescriptor &column_desc);
    };
} // emerald