#include <gtest/gtest.h>

#include "utility.h"
#include "database.h"
#include "join_result.h"
#include "join_condition.h"
#include "join.h"
#include "group.h"
#include "summary_list.h"

std::string file_name;
std::string data_dir;
emerald::Database* db = new emerald::Database();
emerald::Database* db2 = new emerald::Database();
emerald::Table* joined_table = nullptr;
emerald::Table* joined_table_2 = nullptr;

namespace emerald {

    void SetupDBRowStore(){
        //setup the database
    
        createTables(db, file_name, Table::ROW_STORE);
        loadData(db, data_dir);

        Table* table_1 = db->getTableRef("Orders");
        Table* table_2 = db->getTableRef("Customer");

        std::vector<JoinCondition*> join_conditions;
        join_conditions.push_back(new JoinCondition(table_1, 
                                                    table_2, 
                                                    new Predicate("O_CUSTKEY", "=", "C_CUSTKEY")));

        joined_table = NestedLoopJoin(db, join_conditions);
    }

    void SetupDBColumnStore(){
        //setup the database
    
        createTables(db2, file_name, Table::COLUMN_STORE);
        loadData(db2, data_dir);

        Table* table_1 = db2->getTableRef("Orders");
        Table* table_2 = db2->getTableRef("Customer");

        std::vector<JoinCondition*> join_conditions;
        join_conditions.push_back(new JoinCondition(table_1, 
                                                    table_2, 
                                                    new Predicate("O_CUSTKEY", "=", "C_CUSTKEY")));

        std::vector<std::vector<int>> tuple_ids;
        std::vector<int> table_1_tuples;
        for(size_t i = 0; i < table_1->size(); i++)
        {
            table_1_tuples.push_back(i);
        }
        
        std::vector<int> table_2_tuples;
        for(size_t i = 0; i < table_2->size(); i++)
        {
            table_2_tuples.push_back(i);
        }
        
        tuple_ids.push_back(table_1_tuples);
        tuple_ids.push_back(table_2_tuples);


        joined_table_2 = NestedLoopJoin(join_conditions, tuple_ids);
    }

    TEST(GroupTestSuite, ShouldGroupByOneColumn){
        SetupDBRowStore();
        std::vector<ColumnDescriptor*> group_by_columns;
        group_by_columns.push_back(db->getTableRef("Orders")->getTableDescriptor()->get_column("O_SHIPPRIORITY"));


        std::map<Dimension, Summary*> groups = OrderedGroup(db, joined_table, group_by_columns);
        
        EXPECT_GT(groups.size(), 0);

        //printSummaryTable(groups);

        int column_id = joined_table->getTableDescriptor()->get_column("O_SHIPPRIORITY")->get_column_id();
        int table_id = joined_table->getTableDescriptor()->get_column("O_SHIPPRIORITY")->get_table_id();

        //for each tuple set, check whether the tuple set is grouped against the right value in the map
        std::vector<TupleSet*> tuple_sets = static_cast<JoinResult*>(joined_table)->get_tuples();
        for(auto &tuple_set : tuple_sets)
        {
            
            int tuple_id = tuple_set->get_tuple_id(table_id);
            std::vector<Field*> fields;
            fields.push_back(db->get_field(table_id, tuple_id, column_id));

            Dimension dimension(fields);
            Summary* summary = groups[dimension];
            
            ASSERT_NE(summary, nullptr);

            EXPECT_GT(static_cast<SummaryList*>(summary)->get_tuples().size(), 0);

            bool found = 0;
            for(auto &summary_tuple_set : static_cast<SummaryList*>(summary)->get_tuples())
            {

                if(tuple_set->equals(summary_tuple_set)){
                    found = 1;
                    break;
                }
            }

            EXPECT_EQ(found, 1);
        }
         
    }

    TEST(GroupTestSuite, ShouldGroupByTwoColumns){
        SetupDBRowStore();
        std::vector<ColumnDescriptor*> group_by_columns;
        /* Segmentation fault occurs if the order of grouping attributes change. Unable to figure out why */
        group_by_columns.push_back(db->getTableRef("Orders")->getTableDescriptor()->get_column("O_ORDERDATE"));
        group_by_columns.push_back(db->getTableRef("Orders")->getTableDescriptor()->get_column("O_SHIPPRIORITY"));

        std::map<Dimension, Summary*> groups = OrderedGroup(db, joined_table, group_by_columns);

        EXPECT_GT(groups.size(), 0);

        int column_2_id = joined_table->getTableDescriptor()->get_column("O_SHIPPRIORITY")->get_column_id();
        int table_2_id = joined_table->getTableDescriptor()->get_column("O_SHIPPRIORITY")->get_table_id();
        int column_1_id = joined_table->getTableDescriptor()->get_column("O_ORDERDATE")->get_column_id();
        int table_1_id = joined_table->getTableDescriptor()->get_column("O_ORDERDATE")->get_table_id();

        //for each tuple set, check whether the tuple set is grouped against the right value in the map
        std::vector<TupleSet*> tuple_sets = static_cast<JoinResult*>(joined_table)->get_tuples();
        
        for(auto &tuple_set : tuple_sets)
        {
            int tuple_1_id = tuple_set->get_tuple_id(table_1_id);
            int tuple_2_id = tuple_set->get_tuple_id(table_2_id);
            std::vector<Field*> fields;
            fields.push_back(db->get_field(table_1_id, tuple_1_id, column_1_id));
            fields.push_back(db->get_field(table_2_id, tuple_2_id, column_2_id));

            Dimension dimension(fields);
            SummaryList* summary = static_cast<SummaryList*>(groups[dimension]);

            bool found = 0;
            for(auto &summary_tuple_set : summary->get_tuples())
            {
                if(tuple_set->equals(summary_tuple_set)){
                    found = 1;
                    break;
                }
            }
            EXPECT_EQ(found, 1);
        }  
    } 

    TEST(GroupTestSuite, ShouldGroupColumnStoreByOneColumn){
        SetupDBColumnStore();
        std::vector<ColumnDescriptor*> group_by_columns;
        group_by_columns.push_back(db->getTableRef("Orders")->getTableDescriptor()->get_column("O_SHIPPRIORITY"));

        std::map<Dimension, Summary*> groups = OrderedGroup(db, joined_table, group_by_columns);
        
        EXPECT_GT(groups.size(), 0);

        //printSummaryTable(groups);

        int column_id = joined_table->getTableDescriptor()->get_column("O_SHIPPRIORITY")->get_column_id();
        int table_id = joined_table->getTableDescriptor()->get_column("O_SHIPPRIORITY")->get_table_id();

        //for each tuple set, check whether the tuple set is grouped against the right value in the map
        std::vector<TupleSet*> tuple_sets = static_cast<JoinResult*>(joined_table)->get_tuples();
        for(auto &tuple_set : tuple_sets)
        {
            
            int tuple_id = tuple_set->get_tuple_id(table_id);
            std::vector<Field*> fields;
            fields.push_back(db->get_field(table_id, tuple_id, column_id));

            Dimension dimension(fields);
            Summary* summary = groups[dimension];
            
            ASSERT_NE(summary, nullptr);

            EXPECT_GT(static_cast<SummaryList*>(summary)->get_tuples().size(), 0);

            bool found = 0;
            for(auto &summary_tuple_set : static_cast<SummaryList*>(summary)->get_tuples())
            {

                if(tuple_set->equals(summary_tuple_set)){
                    found = 1;
                    break;
                }
            }

            EXPECT_EQ(found, 1);
        }   
    }

    TEST(GroupTestSuite, ShouldGroupColumnStoreByTwoColumns){
        SetupDBColumnStore();
        std::vector<ColumnDescriptor*> group_by_columns;
        group_by_columns.push_back(db->getTableRef("Orders")->getTableDescriptor()->get_column("O_ORDERDATE"));
        group_by_columns.push_back(db->getTableRef("Orders")->getTableDescriptor()->get_column("O_SHIPPRIORITY"));

        std::map<Dimension, Summary*> groups = OrderedGroup(db, joined_table, group_by_columns);

        EXPECT_GT(groups.size(), 0);

        int column_2_id = joined_table->getTableDescriptor()->get_column("O_SHIPPRIORITY")->get_column_id();
        int table_2_id = joined_table->getTableDescriptor()->get_column("O_SHIPPRIORITY")->get_table_id();
        int column_1_id = joined_table->getTableDescriptor()->get_column("O_ORDERDATE")->get_column_id();
        int table_1_id = joined_table->getTableDescriptor()->get_column("O_ORDERDATE")->get_table_id();

        //for each tuple set, check whether the tuple set is grouped against the right value in the map
        std::vector<TupleSet*> tuple_sets = static_cast<JoinResult*>(joined_table)->get_tuples();
        
        for(auto &tuple_set : tuple_sets)
        {
            int tuple_1_id = tuple_set->get_tuple_id(table_1_id);
            int tuple_2_id = tuple_set->get_tuple_id(table_2_id);
            std::vector<Field*> fields;
            fields.push_back(db->get_field(table_1_id, tuple_1_id, column_1_id));
            fields.push_back(db->get_field(table_2_id, tuple_2_id, column_2_id));

            Dimension dimension(fields);
            SummaryList* summary = static_cast<SummaryList*>(groups[dimension]);

            bool found = 0;
            for(auto &summary_tuple_set : summary->get_tuples())
            {
                if(tuple_set->equals(summary_tuple_set)){
                    found = 1;
                    break;
                }
            }
            EXPECT_EQ(found, 1);
        }  
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