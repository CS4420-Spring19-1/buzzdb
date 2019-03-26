#include "date_field.h"
#include <sstream>
#include <iostream>
#include <iomanip>

namespace emerald {
DateField::DateField(std::string v) : Field(field_type::DATE) {
  std::string date_format = "%m/%d/%y";
  std::istringstream ss(v);
  std::tm dt;
  ss >> std::get_time(&dt, date_format.c_str());
  dt.tm_sec = 0;
  dt.tm_hour = 0;
  dt.tm_min = 0;
  this->value = std::mktime(&dt);
}

DateField::DateField(const DateField &field) : Field(field_type::DATE) {
  value = field.getValue();
}

void DateField::print() const {
  std::tm dt = *std::gmtime(&value);
  std::stringstream wss;
  wss << (std::put_time(&dt, "%m/%d/%y"));
  std::cout << wss.str() << " \n";
}

// function not declared in header file
// function used in filter()
std::string toString(time_t value) {
  std::tm dt = *std::gmtime(&value);
  std::stringstream wss;
  wss << (std::put_time(&dt, "%m/%d/%y"));
  return wss.str();
}

bool DateField::filter(Predicate::opType op, Field *other_value) {
  DateField *date_value = static_cast<DateField *>(other_value);
  switch (op) {
    case Predicate::opType::EQ:
      return toString(this->value).compare(toString(date_value->getValue())) == 0;
      break;
    case Predicate::opType::NE:
      return std::difftime(this->value, date_value->getValue()) != 0;
      break;
    case Predicate::opType::GT:
      return std::difftime(this->value, date_value->getValue()) > 0;
      break;
    case Predicate::opType::LT:
      return std::difftime(this->value, date_value->getValue()) < 0;
      break;
    case Predicate::opType::GE:
      return std::difftime(this->value, date_value->getValue()) >= 0;
      break;
    case Predicate::opType::LE:
      return std::difftime(this->value, date_value->getValue()) <= 0;
      break;
    default:
      return false;
      break;
  }
}

std::time_t DateField::getValue() const {
  return this->value;
}
}
