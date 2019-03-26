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
   * Compares other_value with the current field using the op specified.
   * Equivalent to field.compare() in the Java implementation.
   * If function returns true, the tuple / attribute value needs to be
   *  included in the result.
   */
  bool filter(Predicate::opType op, Field *other_value) override;

  /**
   * Gets the date field's value
   */
  std::time_t getValue() const;
};
}
