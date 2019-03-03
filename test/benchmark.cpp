#include <gtest/gtest.h>

#include "utility.h"
#include "database.h"
#include "projection.h"
#include "data_cube.h"
#include "projection_expression.h"
#include "join_condition.h"
#include "predicate.h"
#include "row_store.h"
#include "scan.h"
#include "order.h"
#include <chrono>

std::string file_name;
std::string data_dir;
emerald::Database* db = new emerald::Database();
emerald::Table* projected_result = nullptr;

namespace emerald {

    TEST(BenchmarkSuite, Query1DataCube){

        std::vector<std::string> group_by_columns;
        group_by_columns.push_back("O_ORDERDATE");
        group_by_columns.push_back("O_SHIPPRIORITY");

        std::vector<JoinCondition*> join_conditions;
        join_conditions.push_back(new JoinCondition(db->getTableRef("Orders"), 
                                                    db->getTableRef("Customer"), 
                                                    new Predicate("O_CUSTKEY", "=", "C_CUSTKEY")));

        auto start = std::chrono::high_resolution_clock::now();
        DataCube* datacube = new DataCube(db, group_by_columns, join_conditions);
        auto stop = std::chrono::high_resolution_clock::now();
        auto elapsed = stop - start;
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Datacube creation : " << time_milliseconds.count() << " ms \n";

        // APPLY FILTERS
        std::vector<Predicate*> predicates;
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "BUILDING"));
        predicates.push_back(new Predicate("O_ORDERDATE", "<", "08/21/96"));

        DataCube* datacube_filtered = GroupScan(db, datacube, predicates);

        //PROJECT COLUMNS
        std::vector<emerald::ProjectionExpression*> selected_columns;
        selected_columns.push_back(new ProjectionExpression("NONE", "O_ORDERDATE"));
        selected_columns.push_back(new ProjectionExpression("NONE", "O_SHIPPRIORITY"));
        
        start = std::chrono::high_resolution_clock::now();

        projected_result = ProjectFromDataCube(datacube_filtered, selected_columns);
        elapsed +=  std::chrono::high_resolution_clock::now() - start;
        
        //ORDER RESULTS
        std::vector<std::string> order_by_column;
        order_by_column.push_back("O_ORDERDATE");
        std::vector<bool> is_asc(true);

        start = std::chrono::high_resolution_clock::now();
        RowStore* ordered_result = static_cast<RowStore*>(OrderTable(projected_result, order_by_column, is_asc));
        elapsed +=  std::chrono::high_resolution_clock::now() - start;

        time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Query processing : " << time_milliseconds.count() << " ms \n";

        ordered_result->print();

    }
}

int main(int argc, char **argv) {

    // Initialize Google's logging library.
    ::testing::InitGoogleTest(&argc, argv);
 
    assert(argc == 3); 

    file_name = argv[1];

    data_dir = argv[2];

    //setup the database
    
    createTables(db, file_name, emerald::Table::ROW_STORE);
    loadData(db, data_dir);

    
    int result = RUN_ALL_TESTS();

    return result;
}