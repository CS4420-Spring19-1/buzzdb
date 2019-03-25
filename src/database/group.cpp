#include "group.h"
#include "row_store.h"
#include "join_result.h"
#include "summary_list.h"
#include <iostream>

namespace emerald
{
    std::map<Dimension, Summary*> OrderedGroup(Database* db, Table* table, std::vector<ColumnDescriptor*> column_descs){

        std::map<Dimension, Summary*> groups;

        /*Scan through the table and extract the required columns into a Dimension field*/
        if (table->getStorageType()==Table::JOIN_INDEX) {
            for(auto &tuple : static_cast<JoinResult*>(table)->get_tuples())
            {
                std::vector<Field*> fields;

                for(auto &column : column_descs)
                {
                    /* Determine which tuple in the tuple set belongs to the same table as the current */
                    int tuple_id = tuple->get_tuple_id(column->get_table_id());

                    /* Use the table_id, tuple_id and column_id to get the field*/
                    fields.push_back(db->get_field(column->get_table_id(), tuple_id, column->get_column_id()));
                }
                
                // /* Create the dimension object */
                Dimension dimension(fields);

                // Insert the dimension into the map
                if(groups[dimension]==nullptr){
                    groups[dimension] = new SummaryList();
                } 
                static_cast<SummaryList*>(groups[dimension])->add_tuple_set(tuple); 
                

            }
            
        }
        // what if the first if clause evaluates to false?
        return groups; 
    }
} // emerald
