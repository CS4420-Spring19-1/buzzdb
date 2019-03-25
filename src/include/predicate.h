#pragma once

#include <string>

namespace emerald {
/**
 * Thie class is used to perform comparisons between Fields
 */
class Predicate {

 private:
  std::string column;
  opType op;
  std::string value;
  
  // not implemented: equality operator, copy constructor (necessary?)

 public:
 /**
  * Constants used for return codes in Field::filter
  */
  enum opType {
    EQ, // equals
    NE, // not equals
    GT, // greater than
    LT, // less than
    GE, // greater than or equal to
    LE  // less than oe equal to
  };

  /**
   * No argument constructor for the Predicate class
   */
  Predicate();

  /**
   * Constructor for the Predicate class
   */
  Predicate(std::string column_name, std::string op, std::string value);

  /**
   * Returns the predicate's column 
   */
  std::string getColumn();

  /**
   * Returns the predicate's value
   */
  std::string getValue();

  /**
   * Returns the predicate's op
   */
  opType getOp();
};
}
