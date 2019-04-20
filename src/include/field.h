#pragma once
#include "type.h"
#include "predicate.h"

namespace buzzdb {
/**
 * This is an interface for Field values in tuples.
 */
class Field {
 public:
  /**
   * Destructor.
   * it is necessary for an interface class to have a virtual destructor to
   * ensure correct polymorphic deletion.
   */
  virtual ~Field();

  /**
   * Returns the type of the Field.
   * 
   * Consider restructuring:
   * https://stackoverflow.com/questions/34516232/enum-as-class-member-function-with-return-value
   */
  virtual Type::FieldType get_type() const = 0;

  /**
   * Write the bytes representing the field to the specified Stream.
   */
  /*
    virtual void serialize(DataOutputStream dos) = 0;
  */

  /**
   * Compares the value of the Field to the value of operand.
   */
  virtual bool Compare(Predicate::OpType op_type, Field * operand) = 0;

  /**
   * Prints the field's contents.
   */
  virtual void Print() const = 0;
};
}
