#include "table.h"
#include <string>

namespace emerald
{
    Table::Table(Table::storageType storage_type){
        type = storage_type;
    };

    void Table::setTableDesc(std::vector<std::string> column_names, std::vector<std::string> column_types){
        tableDesc = new TableDescriptor(column_names, column_types);
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
        tableDesc->AppendColumnNames(table_desc->getColumnNames());
        tableDesc->AppendColumnTypes(table_desc->getColumnTypes());
    };
} // emerald
