#include <gtest/gtest.h>

#include "utility.h"
#include "database.h"
#include "join_condition.h"
#include "join.h"
#include "tuple_set.h"
#include "join_result.h"


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
    size_t table_desc_1_size = table_1->getTableDescriptor()->size();
    size_t table_desc_2_size = table_2->getTableDescriptor()->size();

    EXPECT_EQ(result->getTableDescriptor()->size(), table_desc_1_size+table_desc_2_size);

    for(size_t i = 0; i < table_desc_1_size; i++)
    {
        EXPECT_EQ(result->getTableDescriptor()->get_column(i)->get_column_id(), 
                        table_1->getTableDescriptor()->get_column(i)->get_column_id());
        ASSERT_EQ(result->getTableDescriptor()->get_column(i)->get_column_name(), 
                        table_1->getTableDescriptor()->get_column(i)->get_column_name());
        EXPECT_EQ(result->getTableDescriptor()->get_column(i)->get_column_type(), 
                        table_1->getTableDescriptor()->get_column(i)->get_column_type());
        EXPECT_EQ(result->getTableDescriptor()->get_column(i)->get_table_id(), 
                        table_1->getTableDescriptor()->get_column(i)->get_table_id());
    }

    for(size_t i = 0; i < table_desc_2_size; i++)
    {
        EXPECT_EQ(result->getTableDescriptor()->get_column(i+table_desc_1_size)->get_column_id(), 
                        table_2->getTableDescriptor()->get_column(i)->get_column_id());
        ASSERT_EQ(result->getTableDescriptor()->get_column(i+table_desc_1_size)->get_column_name(), 
                        table_2->getTableDescriptor()->get_column(i)->get_column_name());
        EXPECT_EQ(result->getTableDescriptor()->get_column(i+table_desc_1_size)->get_column_type(), 
                        table_2->getTableDescriptor()->get_column(i)->get_column_type());
        EXPECT_EQ(result->getTableDescriptor()->get_column(i+table_desc_1_size)->get_table_id(), 
                        table_2->getTableDescriptor()->get_column(i)->get_table_id());
    }
    
    //check whether the tuples are the matching tuples
    int column_1_id = table_1->getTableDescriptor()->getColumnId("O_CUSTKEY");
    int column_2_id = table_2->getTableDescriptor()->getColumnId("C_CUSTKEY");

    int table_1_id = table_1->get_table_id();
    int table_2_id = table_2->get_table_id();

    std::vector<TupleSet*> tuple_sets = static_cast<JoinResult*>(result)->get_tuples();

    for(auto &tuple_set : tuple_sets)
    {
        // for each tuple set, there will be two tuples. The join columns for each of these tuples should have same value
        int tuple_1_id = tuple_set->get_tuple_id(table_1_id);
        int tuple_2_id = tuple_set->get_tuple_id(table_2_id);

        EXPECT_GE(db->get_field(table_1_id, tuple_1_id, column_1_id)->filter(Predicate::EQ, db->get_field(table_2_id, tuple_2_id, column_2_id)), 0);
        
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

    int result = RUN_ALL_TESTS();

    return result;
}