#include <gtest/gtest.h>
#include "heap_page_id.h"

namespace buzzdb {
/**
 * Unit test suite: HeapPageId
 */
TEST(GetterTests, GetTableIdWorksCorrectly) {
  HeapPageId heap_page_id(1, 1);

  EXPECT_EQ(1, heap_page_id.get_table_id());
}

TEST(GetterTests, GetPageNumberWorksCorrectly) {
  HeapPageId heap_page_id(1, 1);

  EXPECT_EQ(1, heap_page_id.get_page_number());
}

TEST(ConstructorTests, ConstructorWorksCorrectly) {
  HeapPageId heap_page_id_new(22, 0);

  EXPECT_EQ(22, heap_page_id_new.get_table_id());
  EXPECT_EQ(0, heap_page_id_new.get_page_number());
}

TEST(ConstructorTests, CopyConstructorWorksCorrectly) {
  HeapPageId heap_page_id(1, 1);
  HeapPageId heap_page_id_copy = heap_page_id;

  EXPECT_EQ(heap_page_id.get_table_id(), heap_page_id_copy.get_table_id());
  EXPECT_EQ(heap_page_id.get_page_number(), heap_page_id_copy.get_page_number());

  // check that the two objects are distinct
  EXPECT_NE(&heap_page_id, &heap_page_id_copy);
}

TEST(OperatorOverloadTests, EqualityOperatorWorksCorrectly) {
  HeapPageId heap_page_id(1, 1);
  HeapPageId heap_page_id_same(1, 1);
  HeapPageId heap_page_id_different_table_id(10, 1);
  HeapPageId heap_page_id_different_page_number(1, 27);
  HeapPageId heap_page_id_different(10, 27);
  HeapPageId heap_page_id_copy = heap_page_id;

  // check comparison with self
  EXPECT_TRUE(heap_page_id == heap_page_id);

  // check comparison with same values
  EXPECT_TRUE(heap_page_id == heap_page_id_same);
  
  // check commutativity of operator
  EXPECT_TRUE(heap_page_id_same == heap_page_id);

  // check comparison with copy of self 
  EXPECT_TRUE(heap_page_id == heap_page_id_copy);

  // check comparison with different table id
  EXPECT_FALSE(heap_page_id == heap_page_id_different_table_id);

  // check comparison with different page number
  EXPECT_FALSE(heap_page_id == heap_page_id_different_page_number);

  // check comparison with different values
  EXPECT_FALSE(heap_page_id == heap_page_id_different);
}

TEST(OperatorOverloadTest, InequalityOperatorWorksCorrectly) {
  HeapPageId heap_page_id(1, 1);
  HeapPageId heap_page_id_same(1, 1);
  HeapPageId heap_page_id_different_table_id(10, 1);
  HeapPageId heap_page_id_different_page_number(1, 27);
  HeapPageId heap_page_id_different(10, 27);
  HeapPageId heap_page_id_copy = heap_page_id;

  // check comparison with self
  EXPECT_FALSE(heap_page_id != heap_page_id);

  // check comparison with same values
  EXPECT_FALSE(heap_page_id != heap_page_id_same);
  
  // check commutativity of operator
  EXPECT_FALSE(heap_page_id_same != heap_page_id);

  // check comparison with copy of self 
  EXPECT_FALSE(heap_page_id != heap_page_id_copy);

  // check comparison with different table id
  EXPECT_TRUE(heap_page_id != heap_page_id_different_table_id);

  // check comparison with different page number
  EXPECT_TRUE(heap_page_id != heap_page_id_different_page_number);

  // check comparison with different values
  EXPECT_TRUE(heap_page_id != heap_page_id_different);
}
}

/**
 * Test driver
 */
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    return result;
}
