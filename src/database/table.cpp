#include "table.h"
#include <string>
#include <iostream>

namespace emerald
{
    Table::Table(int table_id, storageType storage_type){
        type = storage_type;
        table_id_ = table_id;
        tableDesc = new TableDescriptor();
    };

    void Table::setTableDesc(int table_id, std::vector<std::string> column_names, std::vector<std::string> column_types){
        tableDesc = new TableDescriptor(table_id, column_names, column_types);
    };

    void Table::printTableDesc() const{
        tableDesc->print();
    };

    TableDescriptor* Table::getTableDescriptor() const{
        return tableDesc;
    };

    Table::storageType Table::getStorageType() const{
        return type;
    };

    void Table::copyTableDesc(TableDescriptor* table_desc){
        tableDesc = table_desc;
    };

    void Table::merge_table_desc(TableDescriptor* table_desc){
        tableDesc->AppendColumns(table_desc->get_columns());
    };

    int Table::get_table_id() const {
        return table_id_;
    }

    Table::~Table(){
        delete tableDesc;
    }
} // emerald
