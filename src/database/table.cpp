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
    void Table::printTableDesc(){
        tableDesc->print();
    };
    TableDescriptor* Table::getTableDescriptor(){
        return tableDesc;
    };
    Table::storageType Table::getStorageType(){
        return type;
    }
    void Table::copyTableDesc(TableDescriptor* tableDesc){
        this->tableDesc = tableDesc;
    }
} // emerald
