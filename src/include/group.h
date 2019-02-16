#pragma once
#include <map>
#include <vector>
#include "dimension.h"
#include "summary.h"
#include "database.h"

namespace emerald
{
    /*This method groups the tables in sorted order using a tree structure*/
    std::map<Dimension*, Summary*> OrderedGroup(Database* db, Table* table, std::vector<std::string> group_by_columns);
} // emerald
