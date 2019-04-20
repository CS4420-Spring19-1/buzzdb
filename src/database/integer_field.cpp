#include "integer_field.h"
#include <iostream>

namespace buzzdb {
IntegerField::IntegerField(int v) : value(v) {
}

IntegerField::IntegerField(const IntegerField & original)
    : value(original.get_value()) { 
}

int IntegerField::get_value() const {
  return this->value;
}

Field::Type IntegerField::get_type() const {
  return Type::INTEGER;
}

/*
bool IntegerField::Compare(Predicate::OpType op_type, Field * operand) {
  IntegerField * operand_value_pointer = static_cast<IntegerField *>(operand);
  int operand_value = operand_value_pointer->get_value();
  switch (op_type) {
    case Predicate::OpType::EQUALS:
      return this->value == operand_value;
      break;
    case Predicate::OpType::NOT_EQUALS:
      return this->value != operand_value;
      break;
    case Predicate::OpType::GREATER_THAN:
      return this->value > operand_value;
      break;
    case Predicate::OpType::LESS_THAN:
      return this->value < operand_value;
      break;
    case Predicate::OpType::GREATER_THAN_OR_EQUAL:
      return this->value >= operand_value;
      break;
    case Predicate::OpType::LESS_THAN_OR_EQUAL:
      return this->value <= operand_value;
      break;
    default:
      return false; // should throw an exception instead of returning false
      break;
  }
}
*/

void IntegerField::Print() const {
  std::cout << value << " ";
}

bool IntegerField::operator==(const IntegerField & other) {
  return value == other.value;
}

bool IntegerField::operator!=(const IntegerField & other) {
  return !(*this == other);
}
}
