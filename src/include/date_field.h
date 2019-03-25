#pragma once

#include "field.h"
#include <ctime>
#include <string>

namespace emerald {
class DateField : public Field {
private:
  std::time_t value;

  // not implemented: equality operator, serialize, getType

public:
  /**
   * Constructor for the DateField class
   */
  DateField(std::string v);

  /**
   * Copy constructor for the DateField class
   */
  DateField(const DateField &field);

  /**
   * Prints the date field's contents
   */
  void print() const override;

  /**
   * Compares the given field with this field using the op specified in the predicate.
   * Equivalent to field.compare() in the java implementation.
   */
  bool filter(Predicate::opType op, Field *value) override;

  /**
   * Gets the date field's value
   */
  std::time_t getValue() const;
};
}
