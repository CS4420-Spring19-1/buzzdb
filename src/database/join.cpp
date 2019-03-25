#include "join.h"
#include "row_store.h"
#include "column.h"
#include "column_store.h"
#include "join_result.h"
#include "tuple_set.h"
#include <iostream>

namespace emerald
{
    void NestedLoopJoinHelper(Database* db, JoinCondition* join_condition, JoinResult* result){
    // function uses dynamic memory allocation
    // function not declared in header
        /* Determine which columns in the table need to be joined. Assumption is that in the 
            predicate the first field correponds to table 1 and second field corresponds to table 2*/
        Predicate* join_predicate = join_condition->get_predicate();
        int table_1_column_id = join_condition->get_table_1()->getTableDescriptor()->getColumnId(join_predicate->getColumn());
        int table_2_column_id = join_condition->get_table_2()->getTableDescriptor()->getColumnId(join_predicate->getValue());

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
        
    };

    Table* NestedLoopJoin(Database* db, std::vector<JoinCondition*> join_conditions){
    // function uses dyanmic memory allocation
        JoinResult* joined_table = new JoinResult(-1);
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
                NestedLoopJoinHelper(db, join_condition, joined_table);
            } else {
                /* joined_table has the joined tuples from previous joins. Need to join the current table with that result */
                NestedLoopJoinHelper(db, 
                                        new JoinCondition(joined_table, join_condition->get_table_2(), join_condition->get_predicate())
                                        ,joined_table);

            }
            
        }
        return joined_table;
        
    };

    // function not declared in header
    // function uses dynamic memory allocation
    void NestedLoopJoinHelper(JoinCondition* join_condition, JoinResult* result, std::vector<int> table_1_tuples, std::vector<int> table_2_tuples){
        /* Determine which columns in the table need to be joined. Assumption is that in the 
            predicate the first field correponds to table 1 and second field corresponds to table 2*/
        Predicate* join_predicate = join_condition->get_predicate();
        int table_1_column_id = join_condition->get_table_1()->getTableDescriptor()->getColumnId(join_predicate->getColumn());
        int table_2_column_id = join_condition->get_table_2()->getTableDescriptor()->getColumnId(join_predicate->getValue());

        if (join_condition->get_table_1()->getStorageType()==Table::JOIN_INDEX) {
            // TO DO         
        } else {
            std::vector<Field*> columns_1 = static_cast<ColumnStore*>(join_condition->get_table_1())->get_column(table_1_column_id)->get_fields();
            std::vector<Field*> columns_2 = static_cast<ColumnStore*>(join_condition->get_table_2())->get_column(table_2_column_id)->get_fields();
            
            /* Loop through both the columns, select only those tuples that match the join_predicate */
            for(auto &tuple_1 : table_1_tuples)
            {
                for(auto &tuple_2 : table_2_tuples)
                {
                    if(columns_1[tuple_1]->filter(join_predicate->getOp(), columns_2[tuple_2])){
                        TupleSet* tuple_set = new TupleSet();
                        tuple_set->insert(new TupleDescriptor(join_condition->get_table_1()->get_table_id(), tuple_1));
                        tuple_set->insert(new TupleDescriptor(join_condition->get_table_2()->get_table_id(), tuple_2));
                        result->insert(tuple_set);
                    }
                }  
            }
        }
        
    };

    Table* NestedLoopJoin(std::vector<JoinCondition*> join_conditions, std::vector<std::vector<int>> filters){
    // function uses dynamic memory allocation
        JoinResult* joined_table = new JoinResult(-1);

        int table_index=0;
        for(auto &join_condition : join_conditions)
        {
            /* Get the table descriptors from both the tables and merge them*/
            if(filters[table_index].size() > 0){
                // if any tuple from table 1 needs to be joined
                joined_table->merge_table_desc(join_condition->get_table_1()->getTableDescriptor());
            }
            if(filters[table_index+1].size() > 0){
                joined_table->merge_table_desc(join_condition->get_table_2()->getTableDescriptor());

            }
            if (joined_table->size()==0) {
                /* This is the first join. Join the two table references and store the result in joined_table */
                NestedLoopJoinHelper(join_condition, joined_table, filters[table_index], filters[table_index+1]);
                table_index+=2;
            } else {
                /* joined_table has the joined tuples from previous joins. Need to join the current table with that result */
                
                table_index++;
            }
            
        }
        return joined_table;
    }

} // emerald
