#pragma once

#include "field.h"

namespace emerald {
class IntegerField : public Field {
 private:
  int value;

  // not implemented: equality operator, serialize, getType

 public:
  /**
   * Constructor for the IntegerField class
   */
  IntegerField(int v);

  /**
   * Copy constructor for the IntegerField class
   */
  IntegerField(const IntegerField &field);

  /**
   * Prints the integer field's contents
   */
  void print() const override;

  /**
   * Compares the given field with this field using the op specified in the predicate.
   * Equivalent to field.compare() in the java implementation.
   */
  bool filter(Predicate::opType op, Field *value) override;

  /**
   * Gets the integer field's value
   */
  int getValue() const;
};
}
