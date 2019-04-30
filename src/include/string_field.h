#pragma once

#include <string>
#include "field.h"

namespace buzzdb {
/**
 * The StringField class represents a string field in a tuple.
 */
class StringField : public Field {
 public:
  /**
   * Constructor.
   * Creates a new StringField with value s.
   */
  StringField(std::string s);

  /**
   * Destructor.
   */
  ~StringField() = default;

  /**
   * Copy constructor.
   */
  StringField(const StringField & original);

  /**
   * Returns the value of the StringField.
   */
  std::string get_value() const;

  /**
   * Returns the type of the StringField.
   */
  Type get_type() const override;

  /**
   * Creates an StringField by parsing the stream and returns a pointer to it.
   */
  static Field * ParseStreamForField(std::stringstream * byte_stream_pointer);

  /**
   * Write the bytes representing the StringField to the specified Stream.
   */
  void Serialize(std::stringstream * byte_stream_pointer) override;

  /**
   * Compares the value of the StringField to the value of operand.
   * 
   * Throws IllegalCastException if operand is not a StringField *.
  bool Compare(Predicate::OpType op_type, Field * operand) override;
   */

  /**
   * Prints the StringField's contents.
   */
  void Print() const override;

  bool operator==(const Field & other) override;

  bool operator!=(const Field & other) override;

 private:
  std::string value;
};
}
