#pragma once

#include "field_type.h"
#include "predicate.h"

namespace emerald {
class Field {
 private:
  field_type type;

  // not implemented: equality operator, serialize, getType

 public:
  /**
   * No argument constructor for the Field class
   */
  Field();

  /**
   * Constructor for the Field class
   */
  Field(field_type type);

  /**
   * Prints the field's contents
   */
  virtual void print() const = 0;

  /**
   * Compares the given field with this field using the op specified in the predicate.
   * Equivalent to field.compare() in the java implementation.
   */
  // if filter returns true, the tuple/attribute value needs to be included in the result
  virtual bool filter(Predicate::opType op, Field* value) = 0;
};
}
