#include "data_cube.h"
#include "join.h"
#include "group.h"
#include <iostream>

namespace emerald
{
    DataCube::DataCube(Database* db, std::vector<std::string> group_by_columns, std::vector<JoinCondition*> join_conditions){
        //join the tables
        Table* joined_table = NestedLoopJoin(db, join_conditions);

        //get the column descriptors
        TableDescriptor* table_desc = joined_table->getTableDescriptor();
        std::vector<ColumnDescriptor*> column_descs;
        
        /*Get the table descriptor and find the column descriptor for each grouping column*/
        for(auto &column : group_by_columns)
        {
            column_descs.push_back(table_desc->get_column(column));
        }

        //set the dimensions used in this datacube
        dimensions_ = column_descs;

        //group the tuples by the grouping columns
        summary_table_ = OrderedGroup(db, joined_table, column_descs);

    }

    //this constructor is used in column store implementation
    DataCube::DataCube(Database* db, Table* joined_table, std::vector<std::string> group_by_columns){
        //get the column descriptors
        TableDescriptor* table_desc = joined_table->getTableDescriptor();
        std::vector<ColumnDescriptor*> column_descs;
        
        /*Get the table descriptor and find the column descriptor for each grouping column*/
        for(auto &column : group_by_columns)
        {
            column_descs.push_back(table_desc->get_column(column));
        }

        //set the dimensions used in this datacube
        dimensions_ = column_descs;

        //group the tuples by the grouping columns
        summary_table_ = OrderedGroup(db, joined_table, column_descs);
    }

    DataCube::DataCube() {
        
    }

    std::map<Dimension, Summary*> DataCube::get_summary_table() const{
        return summary_table_;
    }

    void DataCube::add_mapping(Dimension dimension, Summary* summary){
        summary_table_[dimension] = summary;
    }

    std::vector<ColumnDescriptor*> DataCube::get_dimensions() const {
        return dimensions_;
    }

    void DataCube::set_dimensions(std::vector<ColumnDescriptor*> dimensions) {
        for(auto &dimension : dimensions)
        {
            dimensions_.push_back(dimension);
        }
        
    }
} // emerald