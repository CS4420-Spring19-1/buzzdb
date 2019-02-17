// SETUP DB TEST

#include <gtest/gtest.h>

#include "utility.h"
#include "database.h"
#include "row_store.h"
#include "predicate.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


std::string file_name;
std::string data_dir;

namespace emerald {

TEST(SetupDBTestSuite, ShouldCreateTable) {
    Database* db = new Database();

    std::vector<std::string> column_names;
    column_names.push_back("TEST_COL_1");
    column_names.push_back("TEST_COL_2");
    column_names.push_back("TEST_COL_3");

    std::vector<std::string> column_types;
    column_types.push_back("INTEGER");
    column_types.push_back("INTEGER");
    column_types.push_back("INTEGER");

    db->createTable("Test", column_names, column_types, Table::ROW_STORE);

    //check if table gets proper id
    EXPECT_EQ(db->getTableId("Test"), 0);
    
    TableDescriptor* table_desc = db->getTableRef("Test")->getTableDescriptor();
    //check if all columns are included
    EXPECT_EQ(table_desc->get_columns().size(), 3);

    //check if all columns have proper values
    std::vector<ColumnDescriptor*> columns = table_desc->get_columns();
    for(size_t i=0; i< columns.size(); i++)
    {
        EXPECT_EQ(columns[i]->get_column_id(), i);
        ASSERT_EQ(columns[i]->get_column_name(), column_names[i]);
        EXPECT_EQ(columns[i]->get_table_id(), 0);
        if(column_types[i].compare("INTEGER")==0){
            EXPECT_EQ(columns[i]->get_column_type(), field_type::INTEGER);
        } else if(column_types[i].compare("STRING")==0){
            EXPECT_EQ(columns[i]->get_column_type(), field_type::STRING);
        } else {
            EXPECT_EQ(columns[i]->get_column_type(), field_type::DATE);
        }
        
    }
    delete db;
}

TEST(SetupDBTestSuite, ShouldCreateTables){
    Database* db = new Database();
    createTables(db, file_name);

    EXPECT_EQ(db->getTableIds().size(), 3);

    std::ifstream catalog;
    catalog.open(file_name, std::ifstream::in);

    // open the catalog file and read the table schemas
    if(catalog.is_open()){
        std::string line;
        int id = 0;
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
            
            //check whether the schema values match 
            std::vector<ColumnDescriptor*> columns = db->getTableRef(tableName)->getTableDescriptor()->get_columns();
            for(size_t i=0; i< columns.size(); i++)
            {
                EXPECT_EQ(columns[i]->get_column_id(), i);
                ASSERT_EQ(columns[i]->get_column_name(), column_names[i]);
                EXPECT_EQ(columns[i]->get_table_id(), id);
                if(column_types[i].compare("INTEGER")==0){
                    EXPECT_EQ(columns[i]->get_column_type(), field_type::INTEGER);
                } else if(column_types[i].compare("STRING")==0){
                    EXPECT_EQ(columns[i]->get_column_type(), field_type::STRING);
                } else if(column_types[i].compare("DATE")==0) {
                    EXPECT_EQ(columns[i]->get_column_type(), field_type::DATE);
                } else if(column_types[i].compare("DOUBLE")==0){
                    EXPECT_EQ(columns[i]->get_column_type(), field_type::DOUBLE);
                }
                
            }
            id++;
        }
        catalog.close();
    }

    delete db;
}

TEST(SetupDBTestSuite, ShouldLoadData){

    Database* db = new Database();
    createTables(db, file_name);
    loadData(db, data_dir);

    //load the data from the data directory and check whether they match
    for(auto &x : db->getTableIds()){
        std::string table_name = x.first;
        //data files need to the same name as the tables
        std::ifstream file;
        file.open(data_dir+"/"+table_name+".csv");
    
        std::vector<Tuple*> tuples = static_cast<RowStore*>(db->getTable(x.second))->getTuples();
        std::vector<ColumnDescriptor*> columns = db->getTable(x.second)->getTableDescriptor()->get_columns();

        if(file.is_open()){
            std::string line;
            int tuple_id=0;
            while(getline(file, line)){
                std::istringstream ss(line);
                std::vector<Field*> fields;
                std::string field_value;
                int index = 0;
                while(getline(ss, field_value, ',')){
                        EXPECT_GE(tuples[tuple_id]->getField(index)->
                                    filter(Predicate::opType::EQ, 
                                       constructField(field_value, columns[index]->get_column_type())), 0);
                        index++;
                }
                tuple_id++;
            }
            
        }
        file.close();
    }
}

}  // End emerald namespace

int main(int argc, char **argv) {

  // Initialize Google's logging library.
    ::testing::InitGoogleTest(&argc, argv);
 
    assert(argc == 3); 

    file_name = argv[1];

    data_dir = argv[2];

    int result = RUN_ALL_TESTS();

    return result;
}