#include "database.h"
#include "table.h"
#include "scan.h"
#include "predicate.h"
#include "utility.h"
#include "emerald_db.h"
#include "configuration.h"
#include "column_descriptor.h"
#include "data_cube.h"
#include "join_condition.h"


namespace emerald
{
    configuration state;
    Database* setupDB(){
        Database* db = new Database();
        createTables(db, state.file_name);
        loadData(db, state.data_dir);
        return db;
    }

    void RunDB(){
        Database* db = setupDB();
        db->printTable("Orders");
        std::cout << "----------------------------------------------------------";
        //Predicate* predicate = new Predicate("O_ORDERSTATUS", "=", "F");
        //Table* tableWithPredApplied = seqScan(db->getTableRef("Orders"), predicate);
        //tableWithPredApplied->print();
        std::vector<int> table_ids;
        table_ids.push_back(db->getTableId("Orders"));
        table_ids.push_back(db->getTableId("Customer"));
        //tables.push_back(db->getTableRef("Lineitem"));
        
        std::vector<std::string> group_by_columns;
        group_by_columns.push_back("O_ORDERDATE");
        group_by_columns.push_back("O_SHIPPRIORITY");
       
        std::vector<ColumnDescriptor*> predicate_columns;
        predicate_columns.push_back(new ColumnDescriptor(db, "Customer", "C_MKTSEGMENT"));
        predicate_columns.push_back(new ColumnDescriptor(db, "Orders", "O_ORDERDATE"));

        std::vector<JoinCondition*> join_conditions;
        join_conditions.push_back(new JoinCondition(db->getTableRef("Orders"), 
                                                    db->getTableRef("Customer"), 
                                                    new Predicate("O_CUSTKEY", "=", "C_CUSTKEY")));

        DataCube* datacube = new DataCube(db, table_ids, group_by_columns, predicate_columns, join_conditions);
        if(datacube!=nullptr){
            std::cout << "Yay";
        }
    }
    
} // emerald
