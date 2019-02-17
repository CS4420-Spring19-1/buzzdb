#include "join.h"
#include "row_store.h"
#include "join_result.h"
#include "tuple_set.h"
#include <iostream>

namespace emerald
{
    Table* NestedLoopJoinHelper(Database* db, JoinCondition* join_condition){
        /* Determine which columns in the table need to be joined. Assumption is that in the 
            predicate the first field correponds to table 1 and second field corresponds to table 2*/
        Predicate* join_predicate = join_condition->get_predicate();
        int table_1_column_id = join_condition->get_table_1()->getTableDescriptor()->getColumnId(join_predicate->getColumn());
        int table_2_column_id = join_condition->get_table_2()->getTableDescriptor()->getColumnId(join_predicate->getValue());

        JoinResult* result = new JoinResult(-1); //setting a dummy table_id

        if (join_condition->get_table_1()->getStorageType()==Table::JOIN_INDEX) {
            //for the join column 1, get the table id
            int table_id = join_condition->get_table_1()->getTableDescriptor()->get_column(join_predicate->getColumn())->get_table_id();
            
            //get the join index reference
            JoinResult* table_1 = static_cast<JoinResult*>(join_condition->get_table_1());

            //get the tuples from second table
            RowStore* table_2 = static_cast<RowStore*>(join_condition->get_table_2());

            for(auto &tuple : table_1->get_tuples())
            {
                // From the tuple set, determine which tuple belongs to the same table as the join column
                // Get the field value using the table_id, tuple_id and column_id
                Field* field = db->get_field(table_id, tuple->get_tuple_id(table_id), table_1_column_id);
                
                for(size_t tuple_2_idx = 0; tuple_2_idx < table_2->getTuples().size(); tuple_2_idx++)
                {
                    //get appropriate field value from join index as well as the table and compare
                    if(field->filter(join_predicate->getOp(), table_2->get_tuple(tuple_2_idx)->getField(table_2_column_id))){
                        //add the matching tuple descriptor to the existing tuple set
                        tuple->insert(new TupleDescriptor(table_2->get_table_id(), tuple_2_idx));
                        
                        //add the new tuple to the result
                        result->insert(tuple);
                    }
                }
                
            }            
        } else {
            RowStore* table_1 = static_cast<RowStore*>(join_condition->get_table_1());
            RowStore* table_2 = static_cast<RowStore*>(join_condition->get_table_2());
            
            /* Loop through both the tables, select only those tuples that match the join_predicate */
            for(size_t tuple_1_idx=0; tuple_1_idx < table_1->getTuples().size(); tuple_1_idx++)
            {
                for(size_t tuple_2_idx=0; tuple_2_idx < table_2->getTuples().size(); tuple_2_idx++)
                {
                    if(table_1->get_tuple(tuple_1_idx)->getField(table_1_column_id)->filter(join_predicate->getOp(), table_2->get_tuple(tuple_2_idx)->getField(table_2_column_id))){
                        TupleSet* tuple_set = new TupleSet();
                        tuple_set->insert(new TupleDescriptor(table_1->get_table_id(), tuple_1_idx));
                        tuple_set->insert(new TupleDescriptor(table_2->get_table_id(), tuple_2_idx));
                        result->insert(tuple_set);
                    }
                }  
            }
        }
        
        return result;
        
    };

    Table* NestedLoopJoin(Database* db, std::vector<JoinCondition*> join_conditions){
        Table* joined_table = new JoinResult(-1);
        std::cout  << "Before looping\n";
        /*
           Loop through the join conditions and join the tables
           If there are more than two tables, invoke NestedLoopJoin() with the result of the previous join results
        */
        for(auto &join_condition : join_conditions)
        {
            /* Get the table descriptors from both the tables and merge them*/
            joined_table->merge_table_desc(join_condition->get_table_1()->getTableDescriptor());
            //joined_table->merge_table_desc(join_condition->get_table_2()->getTableDescriptor());
            std::cout << "Merged table_des\n";
            if (joined_table->size()==0) {
                /* This is the first join. Join the two table references and store the result in joined_table */
                joined_table = NestedLoopJoinHelper(db, join_condition);
            } else {
                /* joined_table has the joined tuples from previous joins. Need to join the current table with that result */
                Table* tmp_table = NestedLoopJoinHelper(db, new JoinCondition(joined_table, join_condition->get_table_2(), join_condition->get_predicate()));
                free(joined_table); // All of the previous join results are not required
                joined_table = tmp_table;
            }
            
        }
        
        return joined_table;
        
    }
} // emerald
