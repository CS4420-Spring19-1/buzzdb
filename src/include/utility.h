#pragma once

#include "database.h"
#include <string>

namespace emerald
{
    void createTables(Database* db, std::string catalogFile);
    void loadData(Database* db, std::string data_dir);
    Field* constructField(std::string field_value, field_type type);
} // emerald
