#pragma once

#include "field_type.h"
#include "database.h"

namespace emerald
{
    class ColumnDescriptor{
        private:
            int table_id_;
            int column_id_;
            field_type type_;
        public:
            ColumnDescriptor();

            ColumnDescriptor(Database* db, std::string table_name, std::string column_name);
    };
} // emerald