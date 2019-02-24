#pragma once
#include "data_cube.h"

namespace emerald
{
    DataCube* OrderGroup(DataCube* datacube, std::vector<std::string> order_by_columns, bool asc);
} // emerald
