#include "database.h"
#include "table.h"
#include "row_store.h"

namespace emerald
{
    Database::Database(){

    }

    void Database::createTable(std::string table_name, std::vector<std::string> column_names, std::vector<std::string> column_types, Table::storageType type){
        tableIds.insert(std::pair<std::string, int>(table_name, tableIds.size()));
        //schema contains column name mapped to column's data type
        if(type == Table::ROW_STORE){
            RowStore* rowStoreTable = new RowStore(tableIds.size()-1);
            rowStoreTable->setTableDesc(rowStoreTable->get_table_id(), column_names, column_types);
            tables.push_back(rowStoreTable);
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

    void Database::printTable(std::string table_name){
        this->tables[this->tableIds[table_name]]->print();
    }

    Table* Database::getTableRef(std::string table_name){
        return this->tables[this->tableIds[table_name]];
    }

    int Database::getTableId(std::string table_name){
        return tableIds[table_name];
    }

    Field* Database::get_field(int table_id, int tuple_id, int column_id){
        Table* table = tables[table_id];
        if (table->getStorageType()==Table::ROW_STORE) {
            return static_cast<RowStore*>(table)->get_tuple(tuple_id)->getField(column_id);
        }
        return nullptr;
    }
} // emerald
