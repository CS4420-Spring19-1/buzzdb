#include "double_field.h"
#include "field.h"
#include <iostream>

namespace emerald
{
    DoubleField::DoubleField(double v) : Field(field_type::DOUBLE), value(v) {
    }; // redundant semicolon?

    // line length exceeds 80 characters
    DoubleField::DoubleField(const DoubleField& field) : Field(field_type::DOUBLE) {
        value = field.getValue();
    }; // redundant semicolon?

    void DoubleField::print() const {
        std::cout << std::fixed << value << " ";
    }; // redundant semicolon?

    bool DoubleField::filter(Predicate::opType op, Field* value) {
        DoubleField* double_value = static_cast<DoubleField*>(value);
        switch (op) {
            // SEG FAULT
            // value is a variable, not a pointer; should not be dereferenced
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
    }; // redundant semicolon?

    double DoubleField::getValue() const{
        return this->value;
    }; // redundant semicolon?
} // emerald