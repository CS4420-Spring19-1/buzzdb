#pragma once

#include "field.h"

namespace buzzdb {
/**
 * The IntegerField class represents an integer field in a tuple.
 */
class IntegerField : public Field {
 public:
  /**
   * Constructor.
   * Creates a new IntegerField with value v.
   */
  IntegerField(int v);

  /**
   * Destructor.
   */
  ~IntegerField() = default;

  /**
   * Copy constructor.
   */
  IntegerField(const IntegerField & original);

  /**
   * Returns the value of the IntegerField.
   */
  int get_value() const;

  /**
   * Returns the type of the IntegerField.
   */
  Type get_type() const override;

  /**
   * Write the bytes representing the IntegerField to the specified Stream.
   */
  /* To be implemented
    void serialize(DataOutputStream dos) override;
  */

  /**
   * Compares the value of the IntegerField to the value of operand.
   * 
   * Throws IllegalCastException if operand is not a IntegerField *.
  bool Compare(Predicate::OpType op_type, Field * operand) override;
   */

  /**
   * Prints the IntegerField's contents.
   */
  void Print() const override;

  bool operator==(const IntegerField & other);

  bool operator!=(const IntegerField & other);

 private:
  int value;
};
}
