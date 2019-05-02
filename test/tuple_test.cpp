#include <gtest/gtest.h>
#include <stdexcept>
#include "heap_page_id.h"
#include "integer_field.h"
#include "utility.h"

namespace buzzdb {
class TupleTest : public ::testing::Test {
 protected:
  TupleTest() : {
  }
};

class ModifyTest : TupleTest {
 protected:
  ModifyTest() : {
    Tuple tup(Utility.GetTupleDesc(2));
    Tuple tup1(Utility.GetTupleDesc(1));
    HeapPageId pid1(0, 0);
  }
};

class GetterTests : TupleTest {
 protected:
  GetterTests() : {
    TupleDesc td = Utility.GetTupleDesc(5);
    Tuple tup(td);
  }
};

TEST(ModifyTest, ModifyFieldsTestCorrectly) {
  tup.set_field(0, new IntegerField(-1));
  tup.set_field(1, new IntegerField(0));

  IntegerField int_field1(-1);
  IntegerField int_field2(0);

  EXPECT_EQ(int_field1, *tup.get_field(0));
  EXPECT_EQ(int_field2, *tup.get_field(1));

  tup.set_field(0, new IntegerField(1));
  tup.set_field(1, new IntegerField(37));

  IntegerField int_field3(1);
  IntegerField int_field4(37);

  EXPECT_EQ(int_field3, *tup.get_field(0));
  EXPECT_EQ(int_field4, *tup.get_field(1));
}

TEST(GetterTests, GetTupleDescCorrectly) {
  EXPECT_EQ(td, tup.GetTupleDesc());
}

TEST(ModifyTest, ModifyRecordIdCorrectly) {
  RecordId* rid1 = new RecordId(pid1, 0);
  tup1.set_record_id(rid1);
  try {
    EXPECT_EQ(*rid1, *tup1.get_record_id());
  } catch (NoSuchElementException e) {
    throw NoSuchElementException("ModifyRecordId() test failed due to " + 
                                "RecordId equal operator not being implemented. 
                                This is not required for Lab 1," + 
                                "but should pass when you do implement the RecordId class");
  }
  delete rid1;
}

}