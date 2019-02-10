#pragma once 

#include "database.h"
#include "column_descriptor.h"
#include "table.h"
#include "join_condition.h"

namespace emerald
{
    Table* NestedLoopJoin(Database* db, std::vector<int> table_ids, std::vector<JoinCondition*> join_conditions);
} // emerald
