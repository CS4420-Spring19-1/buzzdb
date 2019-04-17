#pragma once

#include "field.h"

namespace buzzdb {
class IntegerField : public Field {
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
   * Gets the integer field's value
   */
  int get_value() const;

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
   * Compares the value of the IntegerField to the value of operand.
   * 
   * Throws IllegalCastException if operand is not a IntegerField *.
   */
  bool Compare(Predicate::OpType op_type, Field * operand) override;

  /**
   * Prints the integer field's contents
   */
  void Print() const override;

  /**
   * Overload of the equality operator.
   */
  bool operator==(IntegerField other);

 private:
  int value;
};
}
