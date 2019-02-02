#include "database.h"
#include "table.h"
#include "utility.h"
#include "emerald_db.h"
#include "configuration.h"

namespace emerald
{
    configuration state;
    Database* setupDB(){
        Database* db = new Database();
        createTables(db, state.file_name);
        loadData(db, state.data_dir);
        return db;
    }

    void RunDB(){
        Database* db = setupDB();
        db->getTable(0)->printTable();
    }
    
} // emerald
