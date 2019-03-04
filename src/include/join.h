#pragma once 

#include "database.h"
#include "column_descriptor.h"
#include "join_condition.h"


namespace emerald
{
    Table* NestedLoopJoin(Database* db, std::vector<JoinCondition*> join_conditions);

    Table* NestedLoopJoin(std::vector<JoinCondition*> join_conditions, std::vector<std::vector<int>> filters);
} // emerald
