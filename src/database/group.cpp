#include "group.h"
#include "row_store.h"
#include "join_result.h"
#include "summary_list.h"

namespace emerald
{
    std::map<Dimension*, Summary*> OrderedGroup(Database* db, Table* table, std::vector<std::string> group_by_columns){
        std::vector<ColumnDescriptor*> column_descs;
        TableDescriptor* table_desc = table->getTableDescriptor();
        std::map<Dimension*, Summary*> groups;
        
        /*Get the table descriptor and find the column descriptor for each grouping column*/
        for(auto &column : group_by_columns)
        {
            column_descs.push_back(table_desc->get_column(column));
        }

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
                                
                /* Create the dimension object */
                Dimension* dimension = new Dimension(fields);

                // Insert the dimension into the map
                static_cast<SummaryList*>(groups[dimension])->add_tuple_set(tuple); 

            }
            
        }
        return groups; 
    }
} // emerald
