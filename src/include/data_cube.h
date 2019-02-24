#pragma once
#include "column_descriptor.h"
#include <vector>
#include <map>
#include "dimension.h"
#include "summary.h"
#include "join_condition.h"
#include "database.h"

namespace emerald
{
    //DataCube class contains the mapping between grouping attributes to the grouped tuples.
    //Grouped tuples may be stored as an index or a list of tuple offsets. The storage is abstracted out by Summary class
    class DataCube {
        private:
            //array of the group_by columns
            std::vector<ColumnDescriptor*> dimensions_;

            //a sorted map of the grouping attributes versus the grouped tuples
            std::map<Dimension, Summary*> summary_table_;

        public:
            DataCube();

            DataCube(Database* db,
                        std::vector<std::string> group_by_columns,  
                        std::vector<JoinCondition*> join_conditions);

            std::map<Dimension, Summary*> get_summary_table() const;

            void add_mapping(Dimension dimension, Summary* summary);

            std::vector<ColumnDescriptor*> get_dimensions() const;

    };
} // emerald
