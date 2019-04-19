#include <gtest/gtest.h>
#include "heap_page_id.h"

namespace buzzdb {
class PidTests {
 public:
  PidTests() {
    pid = new HeapPageId(1, 1);
  }

  ~PidTests() {
    delete pid;
  }

  void test1() {
    ASSERT_EQ(1, pid->get_table_id());
  }

  void test2() {
    ASSERT_EQ(1, pid->get_page_number());
  }

  void test3() {
    HeapPageId pid1(1, 1);
    HeapPageId pid1Copy(1, 1);
    HeapPageId pid2(2, 2);

    // equals() with wrong type should return false

    ASSERT_TRUE(pid1 == pid1);
    ASSERT_TRUE(pid1 == pid1Copy);
    ASSERT_TRUE(pid1Copy == pid1);
    ASSERT_TRUE(pid2 == pid2);

    ASSERT_FALSE(pid1 == pid2);
    ASSERT_FALSE(pid1Copy == pid2);
    ASSERT_FALSE(pid2 == pid1);
    ASSERT_FALSE(pid1Copy == pid2);

  }
 private:
  HeapPageId* pid;
};

PidTests* pid_test;
// Unit test for HeapPageId->getTableId()
TEST(PidTest, GetTableId) {
  pid_test = new PidTests();
  pid_test->test1();
};

// Unit test for HeapPageId->pageno()
TEST(PidTest, GetTableNumber) {
  pid_test->test2();
};
// Unit test for HeapPageId.hashCode()
// Not exist in c++
TEST(PidTest, Equal) {
  pid_test->test3();
  delete pid_test;
}
}

// int main(int argc, char** argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     int result = RUN_ALL_TESTS();
//     return result;
// }