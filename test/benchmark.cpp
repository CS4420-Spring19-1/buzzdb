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
emerald::Database* db=nullptr;
emerald::DataCube* datacube = nullptr;

namespace emerald {

    void createDataCube(){
        //setup the database
        db = new Database();
        createTables(db, file_name, emerald::Table::COLUMN_STORE);
        loadData(db, data_dir);

        std::vector<std::string> group_by_columns;
        group_by_columns.push_back("O_ORDERDATE");
        group_by_columns.push_back("O_SHIPPRIORITY");

        std::vector<JoinCondition*> join_conditions;
        join_conditions.push_back(new JoinCondition(db->getTableRef("Orders"), 
                                                    db->getTableRef("Customer"), 
                                                    new Predicate("O_CUSTKEY", "=", "C_CUSTKEY")));

        std::vector<int> table_1_tuples, table_2_tuples;
        for(size_t i = 0; i < db->getTableRef("Orders")->size(); i++)
        {
            table_1_tuples.push_back(i);
        }
        
        for(size_t i = 0; i < db->getTableRef("Customer")->size(); i++)
        {
            table_2_tuples.push_back(i);
        }
        
        std::vector<std::vector<int>> tuples;
        tuples.push_back(table_1_tuples);
        tuples.push_back(table_2_tuples);

        auto start = std::chrono::high_resolution_clock::now();
        Table* joined_table = NestedLoopJoin(join_conditions, tuples);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;

        start = std::chrono::high_resolution_clock::now();
        datacube = new DataCube(db, joined_table, group_by_columns);
        elapsed += std::chrono::high_resolution_clock::now() - start;
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Datacube creation : " << time_milliseconds.count() << " ms \n";

        EXPECT_GT(datacube->get_summary_table().size(), 0);
    }

    void QueryOnDataCube(DataCube* dc){
        //PROJECT COLUMNS
        std::vector<emerald::ProjectionExpression*> selected_columns;
        selected_columns.push_back(new ProjectionExpression("NONE", "O_ORDERDATE"));
        selected_columns.push_back(new ProjectionExpression("NONE", "O_SHIPPRIORITY"));

        auto start = std::chrono::high_resolution_clock::now();
        Table* projected_result = ProjectFromDataCube(dc, selected_columns);
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);

        auto elapsed = std::chrono::high_resolution_clock::now() - start;

        std::cout << "Projection took : " << time_milliseconds.count() << " ms \n";
    
        EXPECT_GE(projected_result->size(), 0);

        //ORDER RESULTS
        std::vector<std::string> order_by_column;
        order_by_column.push_back("O_ORDERDATE");
        std::vector<bool> is_asc(true);

        start = std::chrono::high_resolution_clock::now();
        RowStore* ordered_result = static_cast<RowStore*>(OrderTable(projected_result, order_by_column, is_asc));
        time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        elapsed +=  std::chrono::high_resolution_clock::now() - start;
        
        std::cout << "Ordering took : " << time_milliseconds.count() << " ms \n";

        time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Query processing : " << time_milliseconds.count() << " ms \n";

        std::cout << ordered_result->size() << "\n";
        
        delete db;
        delete datacube;
    }

    void printCount(DataCube* dc){
        int groups=0, tuples=0;
        for(auto &entry : dc->get_summary_table()){
            groups++;
            tuples+= entry.second->size();
        }
        std::cout << "Groups: " << groups << " Tuples: " << tuples << "\n";
    }


    TEST(BenchmarkSuite, DataCube1){
        std::cout << "Query : Scan selectivity = 0.2\n";
        createDataCube();

        // APPLY FILTERS
        std::vector<Predicate*> predicates;
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "BUILDING"));
        //predicates.push_back(new Predicate("O_ORDERPRIORITY", "=", "1-URGENT"));

        auto start = std::chrono::high_resolution_clock::now();
        DataCube* datacube_filtered = GroupScan(db, datacube, predicates, "AND");
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Scan took : " << time_milliseconds.count() << " ms \n";

        printCount(datacube_filtered);

        EXPECT_GT(datacube_filtered->get_summary_table().size(), 0);
        EXPECT_GT(datacube_filtered->get_dimensions().size(), 0);

        QueryOnDataCube(datacube_filtered);
    }

    TEST(BenchmarkSuite, DataCube2){
        std::cout << "Query : Scan selectivity = 0.4\n";
        createDataCube();
        // APPLY FILTERS
        std::vector<Predicate*> predicates;
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "BUILDING"));
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "MACHINERY"));

        auto start = std::chrono::high_resolution_clock::now();
        DataCube* datacube_filtered = GroupScan(db, datacube, predicates, "OR");
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Scan took : " << time_milliseconds.count() << " ms \n"; 

        EXPECT_GT(datacube_filtered->get_summary_table().size(), 0);
        EXPECT_GT(datacube_filtered->get_dimensions().size(), 0);

        printCount(datacube_filtered);

        QueryOnDataCube(datacube_filtered);

    }

    TEST(BenchmarkSuite, DataCube3){
        std::cout << "Query : Scan selectivity = 0.6\n";
        createDataCube();
        // APPLY FILTERS
        std::vector<Predicate*> predicates;
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "BUILDING"));
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "MACHINERY"));
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "AUTOMOBILE"));

        auto start = std::chrono::high_resolution_clock::now();
        DataCube* datacube_filtered = GroupScan(db, datacube, predicates, "OR");
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Scan took : " << time_milliseconds.count() << " ms \n"; 

        EXPECT_GT(datacube_filtered->get_summary_table().size(), 0);
        EXPECT_GT(datacube_filtered->get_dimensions().size(), 0);

        printCount(datacube_filtered);

        QueryOnDataCube(datacube_filtered);

    }

    TEST(BenchmarkSuite, DataCube4){
        std::cout << "Query : Scan selectivity = 0.8\n";
        createDataCube();
        // APPLY FILTERS
        std::vector<Predicate*> predicates;
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "BUILDING"));
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "MACHINERY"));
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "AUTOMOBILE"));
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "FURNITURE"));

        auto start = std::chrono::high_resolution_clock::now();
        DataCube* datacube_filtered = GroupScan(db, datacube, predicates, "OR");
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Scan took : " << time_milliseconds.count() << " ms \n"; 

        EXPECT_GT(datacube_filtered->get_summary_table().size(), 0);
        EXPECT_GT(datacube_filtered->get_dimensions().size(), 0);

        printCount(datacube_filtered);

        QueryOnDataCube(datacube_filtered);

    }

    TEST(BenchmarkSuite, DataCube5){
        std::cout << "Query : Scan selectivity = 1\n";
        createDataCube();
        // APPLY FILTERS
        std::vector<Predicate*> predicates;
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "BUILDING"));
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "MACHINERY"));
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "AUTOMOBILE"));
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "FURNITURE"));
        predicates.push_back(new Predicate("C_MKTSEGMENT", "=", "HOUSEHOLD"));

        auto start = std::chrono::high_resolution_clock::now();
        DataCube* datacube_filtered = GroupScan(db, datacube, predicates, "OR");
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Scan took : " << time_milliseconds.count() << " ms \n"; 

        EXPECT_GT(datacube_filtered->get_summary_table().size(), 0);
        EXPECT_GT(datacube_filtered->get_dimensions().size(), 0);

        printCount(datacube_filtered);

        QueryOnDataCube(datacube_filtered);

    }

    void createDB(){
        //setup the database
        Database* db = new Database();
        createTables(db, file_name, emerald::Table::COLUMN_STORE);
        loadData(db, data_dir);
    }

    void QueryOnTable(std::vector<int> table_1_tuples, std::vector<int> table_2_tuples){
        //JOIN THE SELECTED TUPLES
        std::vector<std::vector<int>> tuple_ids;
        tuple_ids.push_back(table_1_tuples);
        tuple_ids.push_back(table_2_tuples);

        std::vector<JoinCondition*> join_conditions;
        join_conditions.push_back(new JoinCondition(db->getTableRef("Orders"), 
                                                    db->getTableRef("Customer"), 
                                                    new Predicate("O_CUSTKEY", "=", "C_CUSTKEY")));
        auto start = std::chrono::high_resolution_clock::now();
        Table* joined_table = NestedLoopJoin(join_conditions, tuple_ids);
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);

        auto elapsed = std::chrono::high_resolution_clock::now() - start;

        std::cout << "Join took : " << time_milliseconds.count() << " ms \n";

        //GROUP THE TUPLES
        std::vector<std::string> group_by_columns;
        group_by_columns.push_back("O_ORDERDATE");
        group_by_columns.push_back("O_SHIPPRIORITY");

        start = std::chrono::high_resolution_clock::now();
        DataCube* grouped_tuples = new DataCube(db, joined_table, group_by_columns);
        time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);

        elapsed += std::chrono::high_resolution_clock::now() - start;

        std::cout << "Grouping took : " << time_milliseconds.count() << " ms \n";
        
        //PROJECT RESULT
        std::vector<emerald::ProjectionExpression*> selected_columns;
        selected_columns.push_back(new ProjectionExpression("NONE", "O_ORDERDATE"));
        selected_columns.push_back(new ProjectionExpression("NONE", "O_SHIPPRIORITY"));
        
        start = std::chrono::high_resolution_clock::now();
        Table* projected_result = ProjectFromDataCube(grouped_tuples, selected_columns);
        time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        elapsed +=  std::chrono::high_resolution_clock::now() - start;
        
        std::cout << "Projection took : " << time_milliseconds.count() << " ms \n";

        //ORDER THE RESULT
        std::vector<std::string> order_by_column;
        order_by_column.push_back("O_ORDERDATE");
        std::vector<bool> is_asc(true);

        start = std::chrono::high_resolution_clock::now();
        RowStore* ordered_result = static_cast<RowStore*>(OrderTable(projected_result, order_by_column, is_asc));
        time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        elapsed +=  std::chrono::high_resolution_clock::now() - start;
        std::cout << "Ordering took : " << time_milliseconds.count() << " ms \n";
        
        time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Query processing : " << time_milliseconds.count() << " ms \n";

        std::cout << ordered_result->size() << "\n";
        
        delete db;
    }

    TEST(BenchmarkSuite, Table1){
        std::cout << "Query : Scan selectivity = 0.2\n";
        createDB();
        //APPLY FILTERS
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> table_2_tuples = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "BUILDING"));
        //std::vector<int> table_1_tuples = ColumnScan(db->getTableRef("Orders"), new Predicate("O_ORDERPRIORITY", "=", "1-URGENT"));
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Scan took : " << time_milliseconds.count() << " ms \n";
        std::cout << "Selectivity : " << (double)table_2_tuples.size()/db->getTableRef("Customer")->size() << "\n";
        
        std::vector<int> table_1_tuples;
        for(size_t i=0; i<db->getTableRef("Orders")->size(); i++){
            table_1_tuples.push_back(i);
        }

        QueryOnTable(table_1_tuples, table_2_tuples);
    }

    TEST(BenchmarkSuite, Table2){
        std::cout << "Query : Scan selectivity = 0.4\n";
        createDB();
        //APPLY FILTERS
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> table_2_tuples = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "BUILDING"));
        std::vector<int> tmp = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "MACHINERY"));
        table_2_tuples.insert(table_2_tuples.end(), tmp.begin(), tmp.end());
        
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Scan took : " << time_milliseconds.count() << " ms \n";
        std::cout << "Selectivity : " << (double)table_2_tuples.size()/db->getTableRef("Customer")->size() << "\n";
        
        std::vector<int> table_1_tuples;
        for(size_t i=0; i<db->getTableRef("Orders")->size(); i++){
            table_1_tuples.push_back(i);
        }

        QueryOnTable(table_1_tuples, table_2_tuples);
    }

    TEST(BenchmarkSuite, Table3){
        std::cout << "Query : Scan selectivity = 0.6\n";
        createDB();
        //APPLY FILTERS
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> table_2_tuples = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "BUILDING"));
        std::vector<int> tmp = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "MACHINERY"));
        table_2_tuples.insert(table_2_tuples.end(), tmp.begin(), tmp.end());
        tmp = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "AUTOMOBILE"));
        table_2_tuples.insert(table_2_tuples.end(), tmp.begin(), tmp.end());

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Scan took : " << time_milliseconds.count() << " ms \n";
        std::cout << "Selectivity : " << (double)table_2_tuples.size()/db->getTableRef("Customer")->size() << "\n";
        
        std::vector<int> table_1_tuples;
        for(size_t i=0; i<db->getTableRef("Orders")->size(); i++){
            table_1_tuples.push_back(i);
        }

        QueryOnTable(table_1_tuples, table_2_tuples);
    }

    TEST(BenchmarkSuite, Table4){
        std::cout << "Query : Scan selectivity = 0.8\n";
        createDB();
        //APPLY FILTERS
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> table_2_tuples = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "BUILDING"));
        std::vector<int> tmp = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "MACHINERY"));
        table_2_tuples.insert(table_2_tuples.end(), tmp.begin(), tmp.end());
        tmp = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "AUTOMOBILE"));
        table_2_tuples.insert(table_2_tuples.end(), tmp.begin(), tmp.end());
        tmp = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "FURNITURE"));
        table_2_tuples.insert(table_2_tuples.end(), tmp.begin(), tmp.end());

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Scan took : " << time_milliseconds.count() << " ms \n";
        std::cout << "Selectivity : " << (double)table_2_tuples.size()/db->getTableRef("Customer")->size() << "\n";
        
        std::vector<int> table_1_tuples;
        for(size_t i=0; i<db->getTableRef("Orders")->size(); i++){
            table_1_tuples.push_back(i);
        }

        QueryOnTable(table_1_tuples, table_2_tuples);
    }

    TEST(BenchmarkSuite, Table5){
        std::cout << "Query : Scan selectivity = 1\n";
        createDB();
        //APPLY FILTERS
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> table_2_tuples = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "BUILDING"));
        std::vector<int> tmp = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "MACHINERY"));
        table_2_tuples.insert(table_2_tuples.end(), tmp.begin(), tmp.end());
        tmp = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "AUTOMOBILE"));
        table_2_tuples.insert(table_2_tuples.end(), tmp.begin(), tmp.end());
        tmp = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "FURNITURE"));
        table_2_tuples.insert(table_2_tuples.end(), tmp.begin(), tmp.end());
        tmp = ColumnScan(db->getTableRef("Customer"), new Predicate("C_MKTSEGMENT", "=", "HOUSEHOLD"));
        table_2_tuples.insert(table_2_tuples.end(), tmp.begin(), tmp.end());

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "Scan took : " << time_milliseconds.count() << " ms \n";
        std::cout << "Selectivity : " << (double)table_2_tuples.size()/db->getTableRef("Customer")->size() << "\n";
        
        std::vector<int> table_1_tuples;
        for(size_t i=0; i<db->getTableRef("Orders")->size(); i++){
            table_1_tuples.push_back(i);
        }

        QueryOnTable(table_1_tuples, table_2_tuples);
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