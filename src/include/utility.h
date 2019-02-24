#pragma once

#include "database.h"
#include "dimension.h"
#include "summary.h"
#include <string>
#include <map>

namespace emerald
{
    void createTables(Database* db, std::string catalogFile);
    void loadData(Database* db, std::string data_dir);
    Field* constructField(std::string field_value, field_type type);
    void printSummaryTable(std::map<Dimension, Summary*> groups);
} // emerald
