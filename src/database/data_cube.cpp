#include "data_cube.h"
#include "join.h"
#include "group.h"

namespace emerald
{
    DataCube::DataCube(Database* db, std::vector<std::string> group_by_columns, std::vector<JoinCondition*> join_conditions){
        //join the tables
        Table* joined_table = NestedLoopJoin(db, join_conditions);

        //group the tuples by the grouping columns
        summary_table_ = OrderedGroup(db, joined_table, group_by_columns);

    }

    DataCube::DataCube() {
        
    }

    std::map<Dimension*, Summary*> DataCube::get_summary_table() const{
        return summary_table_;
    }

    void DataCube::add_mapping(Dimension* dimension, Summary* summary){
        summary_table_[dimension] = summary;
    }
} // emerald