#include "join.h"
#include "row_store.h"

namespace emerald
{
    Table* NestedLoopJoinHelper(JoinCondition* join_condition){
        /* Determine which columns in the table need to be joined. Assumption is that in the 
            predicate the first field correponds to table 1 and second field corresponds to table 2*/
        Predicate* join_predicate = join_condition->get_predicate();
        int table_1_column_id = join_condition->get_table_1()->getTableDescriptor()->getColumnId(join_predicate->getColumn());
        int table_2_column_id = join_condition->get_table_2()->getTableDescriptor()->getColumnId(join_predicate->getValue());

        Table* result = new RowStore();
        /* Loop through both the tables, select only those tuples that match the join_predicate */
        for(auto &tuple_1 : static_cast<RowStore*>(join_condition->get_table_1())->getTuples())
        {
            for(auto &tuple_2 : static_cast<RowStore*>(join_condition->get_table_2())->getTuples())
            {
                if(tuple_1->getField(table_1_column_id)->filter(join_predicate->getOp(), tuple_2->getField(table_2_column_id))){
                    static_cast<RowStore*>(result)->merge_and_insert(tuple_1, tuple_2);
                }
            }  
        }
    };

    Table* NestedLoopJoin(Database* db, std::vector<int> table_ids, std::vector<JoinCondition*> join_conditions){
        Table* joined_table = new RowStore();

        /*
           Loop through the join conditions and join the tables
           If there are more than two tables, invoke NestedLoopJoin() with the result of the previous join results
        */
        for(auto &join_condition : join_conditions)
        {
            /* Get the table descriptors from both the tables and merge them*/
            joined_table->merge_table_desc(join_condition->get_table_1()->getTableDescriptor());
            joined_table->merge_table_desc(join_condition->get_table_2()->getTableDescriptor());
            
            if (joined_table->size()==0) {
                /* This is the first join. Join the two table references and store the result in joined_table */
                joined_table = NestedLoopJoinHelper(join_condition);
            } else {
                /* joined_table has the joined tuples from previous joins. Need to join the current table with that result */
                Table* tmp_table = NestedLoopJoinHelper(new JoinCondition(joined_table, join_condition->get_table_2(), join_condition->get_predicate()));
                free(joined_table); // All of the previous join results are not required
                joined_table = tmp_table;
            }
            
        }
        
        return joined_table;
        
    }
} // emerald
