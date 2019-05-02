#include <gtest/gtest.h>
#include <iostream>
#include "field.h"
#include "utility.h"


namespace buzzdb {
class TupleDescTest : public ::testing::Test {
 protected:
  TupleDescTest() : {
  }   
};

class CombineTest : public TupleDescTest {
 protected: 
  CombineTest() : {
    TupleDesc td1 = Utility.GetTupleDesc(1, "td1");
    TupleDesc td2 = Utility.GetTupleDesc(2, "td2");
    TupleDesc td3;
  }

 private:
  // Ensures that combined's field names = td1's field names + td2's field names
  static bool CombineStringArrays(TupleDesc td1, TupleDesc td2, TupleDesc combined);
};

bool CombineTest::CombineStringArrays(TupleDesc td1, TupleDesc td2, TupleDesc combined) {
  for (int i=0; i<td1.get_number_fields(); i++) {
    if (!(td1.get_field_name(i).empty() && combined.get_field_name(i).empty()) ||
        td1.get_field_name(i) == combined.get_field_name(i)) {
          return false;
        }
  }

  for (int i=td1.get_number_fields(); i<td1.get_number_fields()+td2.get_number_fields(); i++) {
    if (!(td1.get_field_name(i-td1.get_number_fields()).empty() && combined.get_field_name(i).empty()) ||
        td1.get_field_name(i-td1.get_number_fields()) == combined.get_field_name(i)) {
          return false;
        }
  }
  return true;
}

class GetTypeTest : public TupleDescTest {
 protected:
  GetTypeTest() {
  }
};

class NameToIdTest : public TupleDescTest {
 protected:
  NameToId() {
  }
};

class GetSizeTest : public TupleDescTest {
 protected:
  GetSizeTest() {
  }
};

class NumFieldsTest : public TupleDescTest {
 protected:
  NumFieldsTest() {
  }
};

class TestEquals : public TupleDescTest {
 protected:
  TestEquals {
    std::vector<Field::Type> type_array;
    type_array.push_back(Field::Type::INTEGER);
    
    TupleDesc single_int = TupleDesc(type_array);
    TupleDesc single_int2 = TupleDesc(type_array);
    
    type_array.push_back(Field::Type::STRING);
    TupleDesc intstring = TupleDesc(type_array);
  }
};

TEST(CombineTest, CombineTupleDescWorkCorrectly) {
  // td1 + td2 = td3
  td3 = TupleDesc.Combine(td1, td2)
  EXPECT_EQ(3, td3.get_number_fields());
  EXPECT_EQ(3*Field.get_length(Field::Type::INTEGER), td3.get_size());

  for (int i=0; i<3; ++i) {
    EXPECT_EQ(Field::Type::INTEGER, td3.get_field_type(i));
  }

  EXPECT_EQ(CombineTest.CombineStringArrays(td1, td2, td3), true);

  // td2 + td1 = td3
  td3 = TupleDesc.Combine(td2, td1)
  EXPECT_EQ(3, td3.get_number_fields());
  EXPECT_EQ(3*Field.get_length(Field::Type::INTEGER), td3.get_size());

  for (int i=0; i<3; ++i) {
    EXPECT_EQ(Field::Type::INTEGER, td3.get_field_type(i));
  }

  EXPECT_EQ(CombineTest.CombineStringArrays(td2, td1, td3), true);

  // td2 + td2 = td3
  td3 = TupleDesc.Combine(td2, td2)
  EXPECT_EQ(4, td3.get_number_fields());
  EXPECT_EQ(4*Field.get_length(Field::Type::INTEGER), td3.get_size());

  for (int i=0; i<4; ++i) {
    EXPECT_EQ(Field::Type::INTEGER, td3.get_field_type(i));
  }

  EXPECT_EQ(CombineTest.CombineStringArrays(td2, td2, td3), true);
}

TEST(GetTypeTest, GetTypeCorrectly) {
  int lengths[3] = {1, 2, 1000};
  for (int len: lengths) {
    TupleDesc td = Utility.GetTupleDesc(len);
    for (int i=0; i<len; i++) {
      EXPECT_EQ(Field::Type::INTEGER, td.get_field_type(i));
    }
  }
}

TEST(NameToIdTest, ParseNameToIdCorrectly) {
  int lengths[3] = {1, 2, 1000};
  std::string prefix = "test";

  for (int len: lengths) {
    // Make sure to retrieve well-named fields
    TupleDesc td = Utility.GetTupleDesc(len, prefix);
    for (int i=0; i<len; i++) {
      EXPECT_EQ(i, td.get_index_of_named_field(prefix + i));
    }

    // Make sure you throw exception for non-existent fields
    try {
      td.get_index_of_named_field("foo");
      std::err << "foo is not a valid field name" << "\n";
    } catch (NoSuchElementException e){  
      // expected to go here
    }

    // Make sure you throw exception for null searches
    try {
      td.get_index_of_named_field("");
      std::err << "null is not a valid field name" << "\n";
    } catch (NoSuchElementException e){  
      // expected to go here
    }

    // Make sure you throw exception when all field names are null
    td = Utility.GetTupleDesc(len);
    try {
      td.get_index_of_named_field(prefix);
      std::err << "no fields are named, so you can't find it" << "\n";
    } catch (NoSuchElementException e) {
      // expected to go here
    }
  }
}

TEST(GetSizeTest, GetSizeCorrectly) {
  int lengths[3] = {1, 2, 1000};
  for (int len: lengths) {
    TupleDesc td = Utility.GetTupleDesc(len);
    EXPECT_EQ(len*Field.get_length(Field::Type::INTEGER), td.get_size(i));
  }
}

TEST(NumFieldsTest, GetNumFieldsCorrectly) {
  int lengths[3] = {1, 2, 1000};
  for (int len: lengths) {
    TupleDesc td = Utility.GetTupleDesc(len);
    EXPECT_EQ(len, td.get_number_fields());
  }
}

TEST(TestEqualsTest, TupleDescEquals)
  EXPECT_TRUE(single_int == single_int);
  EXPECT_TRUE(single_int == single_int2);
  EXPECT_TRUE(single_int2 == single_int);
  EXPECT_TRUE(intstring == intstring);

  EXPECT_FALSE(single_int == intstring);
  EXPECT_FALSE(single_int2 == intstring);
  EXPECT_FALSE(intstring == single_int);
  EXPECT_FALSE(intstring == single_int2);
}
