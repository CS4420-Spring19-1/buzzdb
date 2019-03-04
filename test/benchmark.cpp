#include <gtest/gtest.h>

#include "utility.h"
#include "database.h"
#include "projection.h"
#include "data_cube.h"
#include "join.h"
#include "group.h"
#include "projection_expression.h"
#include "join_condition.h"
#include "predicate.h"
#include "row_store.h"
#include "scan.h"
#include "order.h"
#include <chrono>

std::string file_name;
std::string data_dir;

namespace emerald {

    TEST(BenchmarkSuite, Query1DataCube){

        //setup the database
        Database* db = new Database();
        createTables(db, file_name, emerald::Table::ROW_STORE);
        loadData(db, data_dir);

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

        EXPECT_GT(datacube->get_summary_table().size(), 0);

        // APPLY FILTERS
        std::vector<Predicate*> predicates;
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "BUILDING"));
        predicates.push_back(new Predicate("O_ORDERPRIORITY", "=", "1-URGENT"));

        start = std::chrono::high_resolution_clock::now();
        DataCube* datacube_filtered = GroupScan(db, datacube, predicates);
        elapsed = std::chrono::high_resolution_clock::now() - start;

        EXPECT_GT(datacube_filtered->get_summary_table().size(), 0);
        EXPECT_GT(datacube_filtered->get_dimensions().size(), 0);

        //PROJECT COLUMNS
        std::vector<emerald::ProjectionExpression*> selected_columns;
        selected_columns.push_back(new ProjectionExpression("NONE", "O_ORDERDATE"));
        selected_columns.push_back(new ProjectionExpression("NONE", "O_SHIPPRIORITY"));
        
        start = std::chrono::high_resolution_clock::now();
        Table* projected_result = ProjectFromDataCube(datacube_filtered, selected_columns);
        elapsed += std::chrono::high_resolution_clock::now() - start;
    
        EXPECT_GT(projected_result->size(), 0);

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

    TEST(BenchmarkSuite, Query1ColumnStore){
        //setup the database
        Database* db = new Database();
        createTables(db, file_name, emerald::Table::COLUMN_STORE);
        loadData(db, data_dir);

        //APPLY FILTERS
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> table_1_tuples = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "BUILDING"));
        std::vector<int> table_2_tuples = ColumnScan(db->getTableRef("Orders"), new Predicate("O_ORDERPRIORITY", "=", "1-URGENT"));
        auto elapsed = std::chrono::high_resolution_clock::now() - start;

        //JOIN THE SELECTED TUPLES
        std::vector<std::vector<int>> tuple_ids;
        tuple_ids.push_back(table_1_tuples);
        tuple_ids.push_back(table_2_tuples);

        std::vector<JoinCondition*> join_conditions;
        join_conditions.push_back(new JoinCondition(db->getTableRef("Orders"), 
                                                    db->getTableRef("Customer"), 
                                                    new Predicate("O_CUSTKEY", "=", "C_CUSTKEY")));
        start = std::chrono::high_resolution_clock::now();
        Table* joined_table = NestedLoopJoin(join_conditions, tuple_ids);
        elapsed += std::chrono::high_resolution_clock::now() - start;

        //GROUP THE TUPLES
        std::vector<std::string> group_by_columns;
        group_by_columns.push_back("O_ORDERDATE");
        group_by_columns.push_back("O_SHIPPRIORITY");

        start = std::chrono::high_resolution_clock::now();
        DataCube* grouped_tuples = new DataCube(db, joined_table, group_by_columns);
        elapsed += std::chrono::high_resolution_clock::now() - start;

        //PROJECT RESULT
        std::vector<emerald::ProjectionExpression*> selected_columns;
        selected_columns.push_back(new ProjectionExpression("NONE", "O_ORDERDATE"));
        selected_columns.push_back(new ProjectionExpression("NONE", "O_SHIPPRIORITY"));
        
        start = std::chrono::high_resolution_clock::now();
        Table* projected_result = ProjectFromDataCube(grouped_tuples, selected_columns);
        elapsed +=  std::chrono::high_resolution_clock::now() - start;

        //ORDER THE RESULT
        std::vector<std::string> order_by_column;
        order_by_column.push_back("O_ORDERDATE");
        std::vector<bool> is_asc(true);

        start = std::chrono::high_resolution_clock::now();
        RowStore* ordered_result = static_cast<RowStore*>(OrderTable(projected_result, order_by_column, is_asc));
        elapsed +=  std::chrono::high_resolution_clock::now() - start;

        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Query processing : " << time_milliseconds.count() << " ms \n";

        ordered_result->print();
        delete db;
    }
}

int main(int argc, char **argv) {

    // Initialize Google's logging library.
    ::testing::InitGoogleTest(&argc, argv);
 
    assert(argc == 3); 

    file_name = argv[1];

    data_dir = argv[2];

    
    int result = RUN_ALL_TESTS();

    return result;
}