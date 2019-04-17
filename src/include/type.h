#pragma once

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
  int get_length();

  /* To be implemented
  Field parse();
  */

 private:
  // psf: STRING_LEN = 128
};
}
