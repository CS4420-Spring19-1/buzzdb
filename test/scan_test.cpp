#include <gtest/gtest.h>

#include "utility.h"
#include "database.h"
#include "scan.h"
#include "column_store.h"


std::string file_name;
std::string data_dir;
emerald::Database* db = new emerald::Database();

namespace emerald {

    TEST(ScanTestSuite, ShouldFilterColumnStore){
        Predicate* predicate = new Predicate("C_MKTSEGMENT", "=", "BUILDING");

        std::vector<int> tuple_ids = ColumnScan(db->getTableRef("Customer"), predicate);

        EXPECT_GT(tuple_ids.size(), 0);

        int column_id = db->getTableRef("Customer")->getTableDescriptor()->getColumnId("C_MKTSEGMENT");
        field_type type = db->getTableRef("Customer")->getTableDescriptor()->getColumnType(column_id);

        std::vector<Field*> fields = static_cast<ColumnStore*>(db->getTableRef("Customer"))->get_column(column_id)->get_fields();
        
        for(auto &tuple_id : tuple_ids)
        {
            EXPECT_EQ(fields[tuple_id]->filter(predicate->getOp(), constructField(predicate->getValue(), type)), true);
        }
        
    }

}

int main(int argc, char **argv) {

  // Initialize Google's logging library.
    ::testing::InitGoogleTest(&argc, argv);
 
    assert(argc == 3); 

    file_name = argv[1];

    data_dir = argv[2];

    //setup the database
    
    createTables(db, file_name, emerald::Table::COLUMN_STORE);
    loadData(db, data_dir);

    int result = RUN_ALL_TESTS();

    return result;
}