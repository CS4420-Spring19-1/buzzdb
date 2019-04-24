#include <gtest/gtest.h>
#include "record_id.h"
#include "heap_page_id.h"

namespace buzzdb {
class RecordIdUnitTest : public ::testing::Test {
 protected:
  RecordIdUnitTest()
    : sample_heap_page_id(1, 1), record_id(sample_heap_page_id, 1) {
  }

  HeapPageId sample_heap_page_id;
  RecordId record_id;
};

class GetterTests : public RecordIdUnitTest {
 protected:
  GetterTests() {
  }
};

class ConstructorTest : public RecordIdUnitTest {
 protected:
  ConstructorTest() {
  }
};

class OverloadedOperatorTests : public RecordIdUnitTest {
 protected:
  OverloadedOperatorTests()
      : different_heap_page_id(2, 2),
        record_id(sample_heap_page_id, 1),
        record_id_same(sample_heap_page_id, 1),
        record_id_different_page_id(different_heap_page_id, 1),
        record_id_different_tuple_number(sample_heap_page_id, 2),
        record_id_different(different_heap_page_id, 2) {
  }

  HeapPageId different_heap_page_id;
  RecordId record_id;
  RecordId record_id_same;
  RecordId record_id_different_page_id;
  RecordId record_id_different_tuple_number;
  RecordId record_id_different;
};

class CopyConstructorTest : public RecordIdUnitTest {
 protected:
  CopyConstructorTest() {
  }
};

/**
 * RecordId: Unit Test
 */
TEST_F(GetterTests, GetPageIdWorksCorrectly) {
  EXPECT_EQ(HeapPageId(1, 1), record_id.get_page_id());
}

TEST_F(GetterTests, GetTupleNumberWorksCorrectly) {
  EXPECT_EQ(1, record_id.get_tuple_number());
}

TEST_F(ConstructorTest, ConstructorWorksCorrectly) {
  EXPECT_EQ(HeapPageId(1, 1), record_id.get_page_id());
  EXPECT_EQ(1, record_id.get_tuple_number());

  // invalid PageId
  HeapPageId invalid_heap_page_id(-1, -1);
  EXPECT_THROW(RecordId invalid_record_id(invalid_heap_page_id, 1),
               std::invalid_argument);
  // invalid tuple number
  EXPECT_THROW(RecordId invalid_record_id(sample_heap_page_id, -1),
               std::invalid_argument);
}

TEST_F(OverloadedOperatorTests, EqualityOperatorWorksCorrectly) {
  // check comparison with self
  EXPECT_TRUE(record_id == record_id);

  // check comparison with same values
  EXPECT_TRUE(record_id == record_id_same);
  
  // check commutativity of operator
  EXPECT_TRUE(record_id_same == record_id);

  // check comparison with different page id
  EXPECT_FALSE(record_id == record_id_different_page_id);

  // check comparison with different tuple number
  EXPECT_FALSE(record_id == record_id_different_tuple_number);

  // check comparison with different values
  EXPECT_FALSE(record_id == record_id_different);
}

TEST_F(OverloadedOperatorTests, InequalityOperatorWorksCorrectly) {
  // check comparison with self
  EXPECT_FALSE(record_id != record_id);

  // check comparison with same values
  EXPECT_FALSE(record_id != record_id_same);
  
  // check commutativity of operator
  EXPECT_FALSE(record_id_same != record_id);

  // check comparison with different page id
  EXPECT_TRUE(record_id != record_id_different_page_id);

  // check comparison with different tuple number
  EXPECT_TRUE(record_id != record_id_different_tuple_number);

  // check comparison with different values
  EXPECT_TRUE(record_id != record_id_different);
}

TEST_F(CopyConstructorTest, CopyConstructorWorksCorrectly) {
  RecordId record_id_copy = record_id;

  // check that the two objects are equal
  // Implementation note: using EXPECT_EQ throws a compile error, not sure why.
  EXPECT_TRUE(record_id == record_id_copy);

  // check that the two objects are distinct
  EXPECT_NE(&record_id, &record_id_copy);
}
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    return result;
}
