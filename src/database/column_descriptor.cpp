#include "column_descriptor.h"

namespace emerald
{
    ColumnDescriptor::ColumnDescriptor(Database* db, std::string table_name, std::string column_name){
        //get the table id
        table_id_ = db->getTableId(table_name);

        //get the table descriptor
        TableDescriptor* table_desc = db->getTable(table_id_)->getTableDescriptor();

        //get the column id using table descriptor
        column_id_ = table_desc->getColumnId(column_name);

        //get the column type using column_id
        type_ = table_desc->getColumnType(column_id_);
    }
    
} // emerald
