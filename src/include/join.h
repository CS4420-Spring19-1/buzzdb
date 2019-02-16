#pragma once 

#include "database.h"
#include "column_descriptor.h"
#include "join_condition.h"

namespace emerald
{
    Table* NestedLoopJoin(Database* db, std::vector<JoinCondition*> join_conditions);
} // emerald
