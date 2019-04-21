#include <gtest/gtest.h>

#include "record_id.h"
#include "heap_page_id.h"

namespace buzzdb {
class RecordIdTest {
 public:
  RecordIdTest() {
    hpid = new HeapPageId(-1, 2);
    hpid2 = new HeapPageId(-1, 2);
    hpid3 = new HeapPageId(-2, 2);

    hrid_ = new RecordId(hpid, 3);
  }

  ~RecordIdTest() {
    delete hpid;
    delete hpid2;
    delete hpid3;
    delete hrid_;
  }

  // Unit test for RecordId.getPageId()
  void test1() {
    ASSERT_TRUE(hpid->Equal(hrid_->get_page_id()));
  }

  // Unit test for RecordId.tuplenumber()
  void test2() {
    ASSERT_EQ(3, hrid_->get_tuple_number());
  }

  // Unit test for RecordId equals()
  void test3() {
    RecordId hrid(hpid, 3);
    RecordId hrid2(hpid2, 3);
    RecordId hrid3(hpid, 4);
    RecordId hrid4(hpid3, 3);

    ASSERT_TRUE(hrid == hrid2);
    ASSERT_TRUE(hrid2 == hrid);
    ASSERT_FALSE(hrid == hrid3);
    ASSERT_FALSE(hrid3 == hrid);
    ASSERT_FALSE(hrid2 == hrid4);
    ASSERT_FALSE(hrid4 == hrid2);
  }
  
private: 
  RecordId* hrid_;
  HeapPageId* hpid;
  HeapPageId* hpid2;
  HeapPageId* hpid3;
};

RecordIdTest* recordId_test;
TEST(RecordIdTests, GetPageId) {
  recordId_test = new RecordIdTest();
  recordId_test->test1();
}

TEST(RecordIdTests, GetTupleNumber) {
  recordId_test->test2();
}

TEST(RecordIdTests, Equal) {
  recordId_test->test3();
  delete recordId_test;
}

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    return result;
    
}