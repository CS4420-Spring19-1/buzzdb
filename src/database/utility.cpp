#include "database.h"
#include "table.h"
#include "field.h"
#include "integer_field.h"
#include "string_field.h"
#include "double_field.h"
#include "date_field.h"
#include "row_store.h"
#include "tuple.h"
#include "utility.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "summary_list.h"

namespace emerald
{
    Table::storageType toStorageType(std::string type){
        if(type.compare("ROW_STORE")==0){
            return Table::ROW_STORE;
        } else {
            return Table::COLUMN_STORE;
        }
    }

    void createTables(Database* db, std::string catalogFile){

        std::ifstream catalog;
        catalog.open(catalogFile, std::ifstream::in);

        if(catalog.is_open()){
            std::string line;
            while(getline(catalog, line)){
                std::istringstream ss(line);
                std::string tableName, storageType, column_name, column_type;
                getline(ss, tableName, ',');
                getline(ss, storageType, ',');
                
                std::vector<std::string> column_names, column_types;
                while(getline(ss, column_name, ',')){
                    column_names.push_back(column_name);
                    getline(ss, column_type, ',');
                    column_types.push_back(column_type);
                }
                db->createTable(tableName, column_names, column_types, toStorageType(storageType));
            }
            catalog.close();
        }
    }

    Field* constructField(std::string field_value, field_type type){
        Field* field = nullptr;

        if(type==field_type::INTEGER){   
            field = new IntegerField(atoi(field_value.c_str()));
        } else if(type==field_type::STRING){
            field = new StringField(field_value); 
        } else if(type==field_type::DOUBLE){
            field = new DoubleField(stod(field_value));
        } else if(type==field_type::DATE){
            field = new DateField(field_value);
        } else {
            //need to fill it for boolean type
        }
        return field;
    }

    void loadData(Database* db, std::string data_dir){

        for(auto &x : db->getTableIds()){

            std::string table_name = x.first;
            //data files need to the same name as the tables
            std::ifstream file;
            file.open(data_dir+"/"+table_name+".csv");

            Table* table = db->getTable(x.second);
            std::vector<ColumnDescriptor*> columns = table->getTableDescriptor()->get_columns();
            if(file.is_open()){
                
                std::string line;
                while(getline(file, line)){
                    std::istringstream ss(line);
                    std::vector<Field*> fields;
                    std::string field_value;
                    int index = 0;
                    while(getline(ss, field_value, ',')){
                         fields.push_back(constructField(field_value, columns[index]->get_column_type()));
                         index++;
                    }
                    Tuple* tuple = new Tuple(fields);
                    if(table->getStorageType() == Table::ROW_STORE){
                        static_cast<RowStore*>(table)->insertTuple(tuple);
                    } else {
                        // need to fill this for column store
                    }
                }
                
            }
            file.close();
        }
    }

    void printSummaryTable(std::map<Dimension,Summary*> groups){
        for(auto &entry : groups)
        {
            std::cout << "Dimension :" ;
            for(auto &field : entry.first.get_fields())
            {
                field->print();
            }

            std::cout << "\n Summary :";
            for(auto &tuple_set : static_cast<SummaryList*>(entry.second)->get_tuples())
            {
                for(auto &tuple_desc : tuple_set->get_tuple_descs())
                {
                    std::cout << "(" << tuple_desc->get_table_id() << ", " << tuple_desc->get_tuple_id() << "\n";
                }
                
            }
                
        }
        
    }
} // emerald
