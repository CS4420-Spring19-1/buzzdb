#include <gtest/gtest.h>
#include "heap_page_id.h"

namespace emerald {
class PidTests {
public:
  PidTests() {
    pid = new HeapPageId(1, 1);
  }

  ~PidTests() {
    delete pid;
    pid = nullptr;
  }

  void test1() {
    ASSERT_EQ(1, pid->get_table_id());
  }

  void test2() {
    ASSERT_EQ(1, pid->get_page_number());
  }

  void test3() {
    HeapPageId* pid1 = new HeapPageId(1, 1);
    HeapPageId* pid1Copy = new HeapPageId(1, 1);
    HeapPageId* pid2 = new HeapPageId(2, 2);

    // equals() with null should return false
    ASSERT_FALSE(pid1 == nullptr);

    // equals() with wrong type should return false
    // ASSERT_FALSE(pid->equals(new Object()));

    ASSERT_TRUE(pid1 == pid1);
    ASSERT_TRUE(pid1 == pid1Copy);
    ASSERT_TRUE(pid1Copy == pid1);
    ASSERT_TRUE(pid2 == pid2);

    ASSERT_FALSE(pid1 == pid2);
    ASSERT_FALSE(pid1Copy == pid2);
    ASSERT_FALSE(pid2 == pid1);
    ASSERT_FALSE(pid1Copy == pid2);

    delete pid1;
    pid1 = nullptr;
    delete pid1Copy;
    pid1Copy = nullptr;
    delete pid2;
    pid2 = nullptr;
  }
private:
  HeapPageId* pid;
}

  PidTests* pid_test;
  // Unit test for HeapPageId->getTableId()
  TEST(PidTests, GetTableId) {
    pid_test = new PidTests();
    pid_test->test1();
  }

  // Unit test for HeapPageId->pageno()
  Test(PidTests, GetTableNumber) {
    pid_test->test2();
  }

  // Unit test for HeapPageId.hashCode()
  // Not exist in c++

  Test(PidTests, Equal) {
    pid_test->test3();
    delete pid_test;
  }

}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    return result;
}