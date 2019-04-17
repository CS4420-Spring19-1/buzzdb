#pragma once

#include <string>
#include "tuple.h"

namespace buzzdb {
class Field;
class Tuple;
/**
 * This class is used to perform comparisons between tuple values.
 */
class Predicate {
 public:
  /**
   * Constants used for return codes in Field::Compare
   */
  enum OpType {
    EQUALS,
    NOT_EQUALS,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_OR_EQUAL,
    LESS_THAN_OR_EQUAL
  };

  /**
   * Constructor for the Predicate class
   */
  Predicate(int field, OpType op_type, Field * operand);

  /**
   * Compares the field number of t
   */
  bool Filter(Tuple & t);

  /**
   * Interface to access operations by a string containing an integer index
   * for command-line convenience.
   */
  /* Parsing methods: not implemented
  static OpType GetOp(std::string s);
  */

  /**
   * Interface to access operations by an integer value for command-line
   * convenience.
   */
  /*
  static OpType GetOp(int i);
  */
  

 private:
  int field;
  OpType op_type;
  Field * operand;
  
  // not implemented: equality operator, copy constructor (necessary?)
};
}
