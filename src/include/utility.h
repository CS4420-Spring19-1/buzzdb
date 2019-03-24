#pragma once

#include "database.h"
#include "dimension.h"
#include "summary.h"
#include <string>
#include <map>

namespace emerald {
    // not sure where these functions are being used
    void createTables(Database* db, std::string catalogFile, Table::storageType type);

    Field* constructField(std::string field_value, field_type type);

    void loadData(Database* db, std::string data_dir);

    void printSummaryTable(std::map<Dimension, Summary*> groups);

} // emerald
