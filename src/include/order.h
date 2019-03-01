#pragma once
#include "table.h"

namespace emerald
{
    Table* OrderTable(Table* table, std::vector<std::string> order_by_columns, std::vector<bool> is_asc);


} // emerald
