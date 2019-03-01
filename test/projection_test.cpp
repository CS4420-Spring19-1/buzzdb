#include <gtest/gtest.h>

#include "utility.h"
#include "database.h"
#include "projection.h"
#include "data_cube.h"
#include "projection_expression.h"
#include "join_condition.h"
#include "predicate.h"
#include "row_store.h"

std::string file_name;
std::string data_dir;
emerald::Database* db = new emerald::Database();
emerald::DataCube* datacube = nullptr;

namespace emerald {

    TEST(ProjectionTestSuite, ShouldProjectFromDatacube){
        std::vector<ProjectionExpression*> selected_columns;
        selected_columns.push_back(new ProjectionExpression("NONE", "O_ORDERDATE"));
        selected_columns.push_back(new ProjectionExpression("NONE", "O_SHIPPRIORITY"));

        RowStore* result = static_cast<RowStore*>(ProjectFromDataCube(datacube, selected_columns));

        EXPECT_EQ(result->getTableDescriptor()->size(), 2);
         
        EXPECT_EQ(result->size(), datacube->get_summary_table().size());

        std::vector<Tuple*> tuples = result->getTuples();

        int tuple_id =0;
        for(auto &entry : datacube->get_summary_table())
        {
            EXPECT_EQ(entry.first.get_field(0)->filter(Predicate::EQ, tuples[tuple_id]->getField(0)), true);

            EXPECT_EQ(entry.first.get_field(1)->filter(Predicate::EQ, tuples[tuple_id]->getField(1)), true);
            tuple_id++;
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

    datacube = new emerald::DataCube(db, group_by_columns, join_conditions);

    int result = RUN_ALL_TESTS();

    return result;
}