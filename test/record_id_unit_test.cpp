#include <gtest/gtest.h>
#include "record_id.h"
#include "heap_page_id.h"

namespace buzzdb {
/**
 * Unit test suite: RecordId
 */
TEST(GetterTests, GetPageIdWorksCorrectly) {
  RecordId record_id(HeapPageId(1, 1), 1);

  EXPECT_EQ(HeapPageId(1, 1), record_id.get_page_id());
}

TEST(GetterTests, GetTupleNumberWorksCorrectly) {
  RecordId record_id(HeapPageId(1, 1), 1);

  EXPECT_EQ(1, record_id.get_tuple_number());
}

TEST(ConstructorTests, ConstructorWorksCorrectly) {
  RecordId record_id_new(HeapPageId(1, 2), 3);

  EXPECT_EQ(HeapPageId(1, 2), record_id_new.get_page_id());
  EXPECT_EQ(3, record_id_new.get_tuple_number());
}

TEST(ConstructorTests, CopyConstructorWorksCorrectly) {
  RecordId record_id(HeapPageId(1, 1), 1);
  RecordId record_id_copy = record_id;

  EXPECT_EQ(record_id.get_page_id(), record_id_copy.get_page_id());
  EXPECT_EQ(record_id.get_tuple_number(), record_id_copy.get_tuple_number());

  // check that the two objects are distinct
  EXPECT_NE(&record_id, &record_id_copy);
}

TEST(OperatorOverloadTests, EqualityOperatorWorksCorrectly) {
  RecordId record_id(HeapPageId(1, 1), 1);
  RecordId record_id_same(HeapPageId(1, 1), 1);
  RecordId record_id_different_page_id(HeapPageId(2, 2), 1);
  RecordId record_id_different_tuple_number(HeapPageId(1, 1), 2);
  RecordId record_id_different(HeapPageId(2, 2), 2);
  RecordId record_id_copy = record_id;

  // check comparison with self
  EXPECT_TRUE(record_id == record_id);

  // check comparison with same values
  EXPECT_TRUE(record_id == record_id_same);
  
  // check commutativity of operator
  EXPECT_TRUE(record_id_same == record_id);

  // check comparison with copy of self 
  EXPECT_TRUE(record_id == record_id_copy);

  // check comparison with different table id
  EXPECT_FALSE(record_id == record_id_different_table_id);

  // check comparison with different page number
  EXPECT_FALSE(record_id == record_id_different_page_number);

  // check comparison with different values
  EXPECT_FALSE(record_id == record_id_different);
}

TEST(OperatorOverloadTest, InequalityOperatorWorksCorrectly) {
  RecordId record_id(HeapPageId(1, 1), 1);
  RecordId record_id_same(HeapPageId(1, 1), 1);
  RecordId record_id_different_page_id(HeapPageId(2, 2), 1);
  RecordId record_id_different_tuple_number(HeapPageId(1, 1), 2);
  RecordId record_id_different(HeapPageId(2, 2), 2);
  RecordId record_id_copy = record_id;

  // check comparison with self
  EXPECT_FALSE(record_id != record_id);

  // check comparison with same values
  EXPECT_FALSE(record_id != record_id_same);
  
  // check commutativity of operator
  EXPECT_FALSE(record_id_same != record_id);

  // check comparison with copy of self 
  EXPECT_FALSE(record_id != record_id_copy);

  // check comparison with different table id
  EXPECT_TRUE(record_id != record_id_different_table_id);

  // check comparison with different page number
  EXPECT_TRUE(record_id != record_id_different_page_number);

  // check comparison with different values
  EXPECT_TRUE(record_id != record_id_different);
}
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    return result;
}
