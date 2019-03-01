#include "projection.h"
#include "row_store.h"
#include "summary_list.h"
#include "utility.h"
#include <iostream>

namespace emerald
{
    // std::vector<Tuple*> ApplyExpressions(SummaryList* tuple_set_list, std::vector<ProjectionExpression*> selected_columns){
    //     //TO DO : complete the function

    //     return nullptr;
    // }

    Table* ProjectFromDataCube(DataCube* datacube, std::vector<ProjectionExpression*> selected_columns){
        //since this is part of the projection result, it is better stored in rowstore
        RowStore* result = new RowStore(-1);

        std::vector<Tuple*> tuples;
        std::vector<ColumnDescriptor*> columns;

        std::map<Dimension, Summary*> groups = datacube->get_summary_table();

        /*
            If the columns to project are the grouping attributes, get the values from the datacube itself
        */
        for(auto &column : selected_columns)
        {   
            int field_index = 0;
            for(auto &dimension : datacube->get_dimensions())
            {
                if(column->get_column().compare(dimension->get_column_name())==0){
                    //for each group, add tuple with the corresponding field
                    // if a tuple already exists, append the field to the tuple
                    size_t group_index = 0;
                    columns.push_back(dimension);
                    
                    for(auto &entry : groups){
                        if(group_index == tuples.size()){
                            // we are adding a tuple for this group for the first time
                            tuples.push_back(new Tuple());
                            tuples[tuples.size()-1]->add_field(entry.first.get_field(field_index));
                        } else {
                            tuples[group_index]->add_field(entry.first.get_field(field_index));
                        }
                        group_index++;
                    }
                    //since we found the matching field in the dimension, no need to iterate further
                    break;
                }
                field_index++;
            }
            
        }

        // set the column descriptor for the result table
        // we need the column names at least to perform any filtering later on
        result->getTableDescriptor()->AppendColumns(columns);

        result->insert_tuples(tuples);

        /*
            For each group,
                For each expression,
                    Evaluate the expression on the tuple set to project the column/aggregate value
        */
        
        // for(auto &entry : datacube->get_summary_table())
        // {
        //    if(entry.second->get_type()==Summary::SUMMARY_LIST){
        //        //std::vector<Tuple*> tuples = ApplyExpressions(static_cast<SummaryList*>(entry.second), selected_columns); 
        //    } 
        // }

        return result;

    }
} // emerald
