#pragma once

#include "field.h"
#include <string>

namespace emerald {
class StringField : public Field {
 public:
  /**
   * Constructor for the StringField class
   */
  StringField(std::string s);

  /**
   * Copy constructor for the StringField class
   */
  StringField(const StringField & field);

  /**
   * Gets the string field's value
   */
  std::string get_value() const;

  /**
   * Returns the type of the Field.
   */
  Type::FieldType get_type() const override;

  /**
   * Write the bytes representing the field to the specified Stream.
   */
  /* To be implemented
    void serialize(DataOutputStream dos) override;
  */

  /**
   * Compares the value of the StringField to the value of operand.
   * 
   * Throws IllegalCastException if operand is not a StringField *.
   */
  bool Compare(Predicate::OpType op_type, Field * operand) override;

  /**
   * Prints the string field's contents
   */
  void Print() const override;

  /**
   * Overload of the equality operator.
   */
  bool operator==(StringField other);

 private:
  std::string value;
};
}
