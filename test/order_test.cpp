#include <gtest/gtest.h>

#include "utility.h"
#include "database.h"
#include "projection.h"
#include "data_cube.h"
#include "projection_expression.h"
#include "join_condition.h"
#include "predicate.h"
#include "row_store.h"
#include "order.h"

std::string file_name;
std::string data_dir;
emerald::Database* db = new emerald::Database();
emerald::Table* projected_result = nullptr;

namespace emerald {

    TEST(OrderingTestSuite, ShouldOrderByOneColumnAsc){
        std::vector<std::string> order_by_column;
        order_by_column.push_back("O_ORDERDATE");
        std::vector<bool> is_asc(true);
        size_t size = projected_result->size();
        
        RowStore* ordered_result = static_cast<RowStore*>(OrderTable(projected_result, order_by_column, is_asc));

        EXPECT_EQ(size, ordered_result->size());

        std::vector<Tuple*> tuples = static_cast<RowStore*>(ordered_result)->getTuples();

        for(size_t i = 0; i < size-1; i++)
        {
            /* check if the tuples are in ascending order */
            /* Since only two columns are projected out, O_ORDERDATE is the first columns*/
            EXPECT_EQ(tuples[i]->getField(0)->filter(Predicate::LE, tuples[i+1]->getField(0)), true);
        }
        

    }
}

int main(int argc, char **argv) {

    // Initialize Google's logging library.
    ::testing::InitGoogleTest(&argc, argv);
 
    assert(argc == 3); 

    file_name = argv[1];

    data_dir = argv[2];

    //setup the database
    
    createTables(db, file_name);
    loadData(db, data_dir);

    std::vector<std::string> group_by_columns;
    group_by_columns.push_back("O_ORDERDATE");
    group_by_columns.push_back("O_SHIPPRIORITY");

    std::vector<emerald::JoinCondition*> join_conditions;
    join_conditions.push_back(new emerald::JoinCondition(db->getTableRef("Orders"), 
                                                db->getTableRef("Customer"), 
                                                new emerald::Predicate("O_CUSTKEY", "=", "C_CUSTKEY")));

    emerald::DataCube* datacube = new emerald::DataCube(db, group_by_columns, join_conditions);
    
    std::vector<emerald::ProjectionExpression*> selected_columns;
    selected_columns.push_back(new emerald::ProjectionExpression("NONE", "O_ORDERDATE"));
    selected_columns.push_back(new emerald::ProjectionExpression("NONE", "O_SHIPPRIORITY"));
    
    projected_result = ProjectFromDataCube(datacube, selected_columns);

    int result = RUN_ALL_TESTS();

    return result;
}