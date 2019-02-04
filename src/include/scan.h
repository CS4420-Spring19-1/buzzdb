#pragma once

#include "table.h"
#include "predicate.h"

namespace emerald
{
    Table* seqScan(Table* table, Predicate* predicate);
} // emerald
