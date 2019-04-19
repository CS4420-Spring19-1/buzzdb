#pragma once
#include <iostream>
#include <sstream>
// #include "field.h"

namespace buzzdb {
/**
 * This class represents a type in BuzzDB.
 */
class Type {
 public:
  /**
   * Available types 
   */
  enum FieldType {
    INTEGER,
    STRING,
    DOUBLE
  };

  /**
   * Returns the number of bytes required to store a field of the respective
   * type.
   */
  int get_length(FieldType);

  // Field* Parse(FieldType, std::istringstream dis);

 private:
  const int STRING_LEN = 128;
};
}
