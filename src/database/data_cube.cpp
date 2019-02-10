#include "data_cube.h"
#include "join.h"

namespace emerald
{
    DataCube::DataCube(Database* db, std::vector<int> table_ids, std::vector<std::string> group_by_columns, std::vector<ColumnDescriptor*> predicate_columns, std::vector<JoinCondition*> join_conditions){
        //join the tables
        Table* joined_table = NestedLoopJoin(db, table_ids, join_conditions);

        //group the tuples by the grouping columns
        

    }
} // emerald