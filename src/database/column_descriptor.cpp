#include "column_descriptor.h"
#include <iostream>

namespace emerald
{
    ColumnDescriptor::ColumnDescriptor(int table_id, int column_id, std::string column_name, field_type type){
        table_id_ = table_id;
        column_id_ = column_id;
        column_name_ = column_name;
        type_ = type;
    }
    
    std::string ColumnDescriptor::get_column_name() const{
        return column_name_;
    }

    field_type ColumnDescriptor::get_column_type() const {
        return type_;
    }

    int ColumnDescriptor::get_column_id() const {
        return column_id_;
    }

    int ColumnDescriptor::get_table_id() const{
        return table_id_;
    }

    ColumnDescriptor::ColumnDescriptor(const ColumnDescriptor &column_desc){
        table_id_ = column_desc.get_table_id();
        column_id_ = column_desc.get_column_id();
        column_name_ = column_desc.get_column_name();
        type_ = column_desc.get_column_type();
    }
} // emerald
