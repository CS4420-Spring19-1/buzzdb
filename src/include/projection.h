#pragma once
#include "table.h"
#include "data_cube.h"
#include "projection_expression.h"

namespace emerald
{
    Table* ProjectFromDataCube(DataCube* datacube, std::vector<ProjectionExpression*> selected_columns);
} // emerald
