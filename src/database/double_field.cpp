#include "double_field.h"
#include "field.h"
#include <iostream>

namespace emerald {
DoubleField::DoubleField(double v) : Field(field_type::DOUBLE), value(v){
}

DoubleField::DoubleField(const DoubleField &field) : Field(field_type::DOUBLE) {
  value = field.getValue();
}

void DoubleField::print() const {
  std::cout << std::fixed << value << " ";
}

bool DoubleField::filter(Predicate::opType op, Field *other_value) {
  DoubleField *double_value = static_cast<DoubleField *>(other_value);
  switch (op) {
    case Predicate::opType::EQ:
      return this->value == double_value->getValue();
      break;
    case Predicate::opType::NE:
      return this->value != double_value->getValue();
      break;
    case Predicate::opType::GT:
      return this->value > double_value->getValue();
      break;
    case Predicate::opType::LT:
      return this->value < double_value->getValue();
      break;
    case Predicate::opType::GE:
      return this->value >= double_value->getValue();
      break;
    case Predicate::opType::LE:
      return this->value <= double_value->getValue();
      break;
    default:
      return false;
      break;
  }
}

double DoubleField::getValue() const {
  return this->value;
}
}
