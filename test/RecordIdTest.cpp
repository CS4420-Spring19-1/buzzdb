#include <gtest/gtest.h>

#include "record_id.h"
#include "heap_page_id.h"

namespace emerald {
class RecordIdTest {
public:
  RecordIdTest() {
    hpid = new HeapPageId(-1, 2);
    hpid2 = new HeapPageId(-1, 2);
    hpid3 = new HeapPageId(-2, 2);

    hrid = new RecordId(hpid, 3);
    hrid2 = new RecordId(hpid2, 3);
    hrid3 = new RecordId(hpid, 4);
    hrid4 = new RecordId(hpid3, 3);
  }

  ~RecordIdTest() {
    delete hrid;
    delete hrid2;
    delete hrid3;
    delete hrid4;
    delete hpid;
    delete hpid2;
    delete hpid3;
  }

  // Unit test for RecordId.getPageId()
  void test1() {
    ASSERT_EQ(hpid, hrid->get_page_id());
  }

  // Unit test for RecordId.tuplenumber()
  void test2() {
    ASSERT_EQ(3, hrid->get_tuple_number());
  }

  // Unit test for RecordId equals()
  void test3() {
    ASSERT_EQ(hrid, hrid2);
    ASSERT_EQ(hrid2, hrid);
    ASSERT_FALSE(hrid == hrid3);
    ASSERT_FALSE(hrid3 == hrid);
    ASSERT_FALSE(hrid2 == hrid4);
    ASSERT_FALSE(hrid4 == hrid2);
  }
  
private:
  RecordId* hrid;
  RecordId* hrid2;
  RecordId* hrid3;
  RecordId* hrid4;
  HeapPageId* hpid;
  HeapPageId* hpid2;
  HeapPageId* hpid3;
}

RecordId* recordId_test;
TEST(RecordIdTest, GetPageId) {
  recordId_test = new RecordIdTest();
  recordId_test->test1();
}

Test(RecordIdTest, GetTupleNumber) {
  recordId_test->test2();
}

Test(RecordIdTest, Equal) {
  recordId_test->test3();
  delete recordId_test;
}

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    return result;
}