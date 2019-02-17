#include <gtest/gtest.h>

#include "utility.h"
#include "database.h"
#include "join_condition.h"
#include "join.h"


std::string file_name;
std::string data_dir;
emerald::Database* db = new emerald::Database();

namespace emerald {

TEST(JoinTestSuite, ShouldJoinTwoTables){
    Table* table_1 = db->getTableRef("Orders");
    Table* table_2 = db->getTableRef("Customer");

    std::vector<JoinCondition*> join_conditions;
    join_conditions.push_back(new JoinCondition(table_1, 
                                                table_2, 
                                                new Predicate("O_CUSTKEY", "=", "C_CUSTKEY")));

    Table* result = NestedLoopJoin(db, join_conditions);

    //check if result is a join index
    EXPECT_EQ(result->getStorageType(), Table::JOIN_INDEX);
    //check if table descriptor of the result is the combination of the two input tables
    //check whether the tuples are the matching tuples
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

    int result = RUN_ALL_TESTS();

    return result;
}