#include <gtest/gtest.h>
#include <stdexcept>
#include "heap_page_id.h"

namespace buzzdb {
class HeapPageIdUnitTest : public ::testing::Test {
 protected:
  HeapPageIdUnitTest() : heap_page_id(1, 1) {
  }

  HeapPageId heap_page_id;
};

class GetterTests : public HeapPageIdUnitTest {
 protected:
  GetterTests() {
  }
};

class CopyConstructorTest : public HeapPageIdUnitTest {
 protected:
  CopyConstructorTest() {
  }
};

class OverloadedOperatorTests : public HeapPageIdUnitTest {
 protected:
  OverloadedOperatorTests()
      : heap_page_id_same(1, 1),
        heap_page_id_different_table_id(10, 1),
        heap_page_id_different_page_number(1, 27),
        heap_page_id_different(10, 27) {
  }

  HeapPageId heap_page_id_same;
  HeapPageId heap_page_id_different_table_id;
  HeapPageId heap_page_id_different_page_number;
  HeapPageId heap_page_id_different;
};

/**
 * HeapPageId: Unit Test
 */
TEST_F(GetterTests, GetTableIdWorksCorrectly) {
  EXPECT_EQ(1, heap_page_id.get_table_id());
}

TEST_F(GetterTests, GetPageNumberWorksCorrectly) {
  EXPECT_EQ(1, heap_page_id.get_page_number());
}

TEST(ConstructorTest, ConstructorWorksCorrectly) {
  HeapPageId heap_page_id(1, 1);

  EXPECT_EQ(1, heap_page_id.get_table_id());
  EXPECT_EQ(1, heap_page_id.get_page_number());

  // invalid table id
  EXPECT_THROW(HeapPageId invalid_heap_page_id(-1, 1), std::invalid_argument);
  // invalid page number
  EXPECT_THROW(HeapPageId invalid_heap_page_id(1, -1), std::invalid_argument);
}

TEST_F(OverloadedOperatorTests, EqualityOperatorWorksCorrectly) {
  // check comparison with self
  EXPECT_TRUE(heap_page_id == heap_page_id);

  // check comparison with same values
  EXPECT_TRUE(heap_page_id == heap_page_id_same);
  
  // check commutativity of operator
  EXPECT_TRUE(heap_page_id_same == heap_page_id);

  // check comparison with different table id only
  EXPECT_FALSE(heap_page_id == heap_page_id_different_table_id);

  // check comparison with different page number only
  EXPECT_FALSE(heap_page_id == heap_page_id_different_page_number);

  // check comparison with different values
  EXPECT_FALSE(heap_page_id == heap_page_id_different);
}

TEST_F(OverloadedOperatorTests, InequalityOperatorWorksCorrectly) {
  // check comparison with self
  EXPECT_FALSE(heap_page_id != heap_page_id);

  // check comparison with same values
  EXPECT_FALSE(heap_page_id != heap_page_id_same);
  
  // check commutativity of operator
  EXPECT_FALSE(heap_page_id_same != heap_page_id);

  // check comparison with different table id only
  EXPECT_TRUE(heap_page_id != heap_page_id_different_table_id);

  // check comparison with different page number only
  EXPECT_TRUE(heap_page_id != heap_page_id_different_page_number);

  // check comparison with different values
  EXPECT_TRUE(heap_page_id != heap_page_id_different);
}

TEST_F(CopyConstructorTest, CopyConstructorWorksCorrectly) {
  HeapPageId heap_page_id_copy = heap_page_id;

  // check that the two objects are equal
  // Implementation note: using EXPECT_EQ throws a compile error, not sure why.
  EXPECT_TRUE(heap_page_id == heap_page_id_copy);

  // check that the two objects are distinct
  EXPECT_NE(&heap_page_id, &heap_page_id_copy);
}
}

/**
 * Test driver
 */
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
