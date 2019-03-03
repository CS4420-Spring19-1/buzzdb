#include "scan.h"
#include "utility.h"
#include "row_store.h"
#include "column_store.h"
#include "summary_list.h"
#include <iostream>

namespace emerald
{
    Table* seqScanRowStore(RowStore* table, int columnIndex, Predicate::opType op, Field* value){
        
        std::vector<Tuple*> tuples = table->getTuples();
        RowStore* result = new RowStore(table->get_table_id());
        //new table will have the same descriptor as the input table
        result->copyTableDesc(table->getTableDescriptor());
        for(size_t i = 0; i < tuples.size(); i++)
        {
            if(tuples[i]->getField(columnIndex)->filter(op, value)){
                result->insertTuple(tuples[i]);
            }
        }
        return result;
    };

    Table* seqScan(Table* table, Predicate* predicate){
        TableDescriptor* tableDesc = table->getTableDescriptor();
        int columnIndex = tableDesc->getColumnId(predicate->getColumn());
        field_type type = tableDesc->getColumnType(columnIndex);
        Field* value = constructField(predicate->getValue(), type); 

        return seqScanRowStore(static_cast<RowStore*>(table), columnIndex, predicate->getOp(), value);

    };

    Summary* SummaryListScan(Database* db, SummaryList* tuple_list, std::vector<Predicate*> predicates){
        SummaryList* result = new SummaryList();

        // use the first tuple_set to figure out which tables the predicates belong to
        TupleSet* tuple_set_tmp = tuple_list->get_tuples()[0];
        std::vector<ColumnDescriptor*> columns;
        for(auto &predicate : predicates)
        {
            for(auto &tuple : tuple_set_tmp->get_tuple_descs())
            {
                //get the table id for the tuple
                int table_id = tuple->get_table_id();

                //get the table descriptor and check if the predicate column exists
                ColumnDescriptor* column = db->getTable(table_id)->getTableDescriptor()->get_column(predicate->getColumn());
                if(column != nullptr){
                    //predicate column belongs to this table
                    columns.push_back(column);
                    break;
                }
            }
        }
         
        // for every tuple_set in the tuple_list, apply the predicate
        for(auto &tuple_set : tuple_list->get_tuples())
        {
            bool isMatch = true;
            int index = 0;
            // FIX : this logic assumes that all the operations are connected by AND
            for(auto &predicate : predicates)
            {
                int tuple_id = tuple_set->get_tuple_id(columns[index]->get_table_id());
                if(!db->get_field(columns[index]->get_table_id(), tuple_id, columns[index]->get_column_id())
                        ->filter(predicate->getOp(), 
                            constructField(predicate->getValue(), columns[index]->get_column_type()))){
                    isMatch = false;
                    break;
                }                
                index++;
            }  
            if (isMatch) {
                // tuple_set satisfied all conditions; add it to result
                // currently, this is doing a shallow copy, but this should be fine
                result->add_tuple_set(tuple_set);
            }
        }
        
        return result;
    }

    DataCube* GroupScan(Database* db, DataCube* datacube, std::vector<Predicate*> predicates){
        //create an empty datacube
        DataCube* result = new DataCube();

        //for each group, apply the predicates. If any tuple in the group satisfies the predicate, add the group and tuples to the result
        for(auto &entry : datacube->get_summary_table())
        {
            Summary* filtered_tuples = nullptr;
            if(entry.second->get_type()==Summary::SUMMARY_LIST){
                filtered_tuples = SummaryListScan(db, static_cast<SummaryList*>(entry.second), predicates);
            }

            if(filtered_tuples->size()>0){
                //some tuple of this group matched the predicates; add this entry to the result
                result->add_mapping(entry.first, filtered_tuples);
            }
        }

        return result;
    }

    std::vector<int> ColumnScan(Table* table, Predicate* predicate){
        int column_id = table->getTableDescriptor()->getColumnId(predicate->getColumn());

        std::vector<Field*> fields = static_cast<ColumnStore*>(table)->get_column(column_id)->get_fields();

        std::vector<int> tuple_ids;

        field_type type = table->getTableDescriptor()->getColumnType(column_id);
        Field* value = constructField(predicate->getValue(), type);

        for(size_t i = 0; i < fields.size(); i++)
        {
            if(fields[i]->filter(predicate->getOp(), value)){
                tuple_ids.push_back(i);
            }
        }
        return tuple_ids;
    }
} // emerald
