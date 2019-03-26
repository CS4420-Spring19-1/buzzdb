#pragma once

#include "field.h"

namespace emerald {
class DoubleField : public Field {
private:
  double value;

  // not implemented: equality operator, serialize, getType

public:
  /**
   * Constructor for the DoubleField class
   */
  DoubleField(double v);

  /**
   * Copy constructor for the DoubleField class
   */
  DoubleField(const DoubleField &field);

  /**
   * Prints the double field's contents
   */
  void print() const override;

  /**
   * Compares other_value with the current field using the op specified.
   * Equivalent to field.compare() in the Java implementation.
   * If function returns true, the tuple / attribute value needs to be
   *  included in the result.
   */
  bool filter(Predicate::opType op, Field *other_value) override;

  /**
   * Gets the double field's value
   */
  double getValue() const;
};
}
