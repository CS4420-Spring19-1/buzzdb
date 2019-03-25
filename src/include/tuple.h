#pragma once
#include<vector>

#include "field.h"
#include "tuple_descriptor.h"

namespace emerald {
class Tuple {
 private:
  /**
   * Internal representation of a tuple
   */
  std::vector<Field*> fields_;

 public:
  /**
   * No argument constructor of the Tuple class
   */
  Tuple();

  /**
   * Constructor of the Tuple class
   */
  Tuple(std::vector<Field*> fields);

  /**
   * Copy constructor of the Tuple class
   */
  Tuple(const Tuple& tuple);

  /**
   * Prints the tuple's contents
   */
  void print() const;
  /**
   * Returns a pointer to the ith field in the tuple.
   * Returns null if field is not set.
   */
  Field* getField(int index) const;


  /**
   * Returns a vector of all fields in the tuple.
   * Returns null if field is not set (?).
   */
  std::vector<Field*> get_fields() const;

  /**
   * Returns a pointer to the ith field in the tuple.
   * Returns null if field is not set.
   */
  void append_fields(std::vector<Field*> fields);

  /**
   * Returns a pointer to the ith field in the tuple.
   * Returns null if field is not set.
   */
  void add_field(Field* field);
};
}
