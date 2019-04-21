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

  /**
   * Implementation note:
   * - This overload has to be declared as a friend function for it to be used
   *   correctly by std::vector.
   * - An example of this usage is in TupleDesc::operator==(TupleDesc & other).
   * - The reason for this is still unknown.
   */
  friend bool operator==(const Type & first, const Type & second);

  bool operator!=(const Type & other);

 private:
  // psf: STRING_LEN = 128
};
}
