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
   * Creates an IntegerField by parsing the stream and returns a pointer to it.
   */
  static Field * ParseStreamForField(std::stringstream * byte_stream_pointer);

  /**
   * Write the bytes representing the IntegerField to the specified Stream.
   */
  void Serialize(std::stringstream * byte_stream) override;

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

  bool operator==(const Field & other) override;

  bool operator!=(const Field & other) override;

 private:
  int value;
};
}
