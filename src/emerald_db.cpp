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
        std::cout << "-----------------------SETTING UP DB-----------------------------------\n";
        Database* db = setupDB();
        //db->printTable("Orders");
        
        std::cout << "-----------------------CREATING DATACUBE-----------------------------------\n";
        
        std::vector<std::string> group_by_columns;
        group_by_columns.push_back("O_ORDERDATE");
        group_by_columns.push_back("O_SHIPPRIORITY");

        std::vector<JoinCondition*> join_conditions;
        join_conditions.push_back(new JoinCondition(db->getTableRef("Orders"), 
                                                    db->getTableRef("Customer"), 
                                                    new Predicate("O_CUSTKEY", "=", "C_CUSTKEY")));

        DataCube* datacube = new DataCube(db, group_by_columns, join_conditions);

        std::cout << "-----------------------APPLYING PREDICATES TO DATACUBE-----------------------------------\n";
        std::vector<Predicate*> predicates;
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "BUILDING"));
        predicates.push_back(new Predicate("O_ORDERDATE", "<", "03/15/96"));
        
        DataCube* datacube_filtered = GroupScan(db, datacube, predicates);
        if (datacube_filtered!=nullptr) {
            
        }
        
    }
    
} // emerald
