#include <gtest/gtest.h>

#include "utility.h"
#include "database.h"


std::string file_name;
std::string data_dir;
emerald::Database* db = new emerald::Database();

namespace emerald {

TEST(DatacubeTestSuite, ShouldCreateDatacube){
    //need to be completed
    EXPECT_EQ(1,1);
}

}

int main(int argc, char **argv) {

  // Initialize Google's logging library.
    ::testing::InitGoogleTest(&argc, argv);
 
    assert(argc == 3); 

    file_name = argv[1];

    data_dir = argv[2];

    //setup the database
    
    createTables(db, file_name);
    loadData(db, data_dir);

    int result = RUN_ALL_TESTS();

    return result;
}