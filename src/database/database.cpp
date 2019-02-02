#include "database.h"
#include "table.h"
#include "row_store.h"

namespace emerald
{
    Database::Database(){

    }
    void Database::createTable(std::string table_name, std::vector<std::string> column_names, std::vector<std::string> column_types, Table::storageType type){
        this->tableIds.insert(std::pair<std::string, int>(table_name, tableIds.size()));
        //schema contains column name mapped to column's data type
        if(type == Table::ROW_STORE){
            RowStore* rowStoreTable = new RowStore();
            rowStoreTable->setTableDesc(column_names, column_types);
            this->tables.push_back(rowStoreTable);
        }
    }
    Table* Database::getTable(int index){
        return this->tables[index];
    }
    std::vector<Table*> Database::getTables(){
        return this->tables;
    }
    std::unordered_map<std::string, int> Database::getTableIds(){
        return this->tableIds;
    }
} // emerald
