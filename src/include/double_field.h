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
   * Compares the given field with this field using the op specified in the predicate.
   * Equivalent to field.compare() in the java implementation.
   */
  bool filter(Predicate::opType op, Field *value) override;

  /**
   * Gets the double field's value
   */
  double getValue() const;
};
}
