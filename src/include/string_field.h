#pragma once

#include "field.h"
#include <string>

namespace emerald {
class StringField : public Field {
private:
  std::string value;

  // not implemented: equality operator, serialize, getType

public:
  /**
   * Constructor for the StringField class
   */
  StringField(std::string v);

  /**
   * Copy constructor for the StringField class
   */
  StringField(const StringField &field);

  /**
   * Prints the string field's contents
   */
  void print() const override;

  /**
   * Compares the given field with this field using the op specified in the predicate.
   * Equivalent to field.compare() in the java implementation.
   */
  bool filter(Predicate::opType op, Field *value) override;

  /**
   * Gets the string field's value
   */
  std::string getValue() const;
};
}
