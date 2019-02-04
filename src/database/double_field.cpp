#include "double_field.h"
#include "field.h"
#include <iostream>

namespace emerald
{
    DoubleField::DoubleField(double v):Field(field_type::DOUBLE),value(v){};
    void DoubleField::print(){
        std::cout << std::fixed << value << " ";
    };
    bool DoubleField::filter(Predicate::opType op, Field* value){
        DoubleField* double_value = static_cast<DoubleField*>(value);
        switch (op)
        {
            case Predicate::opType::EQ :
                return this->value==double_value->getValue();
                break;
            case Predicate::opType::NE :
                return this->value!= double_value->getValue();
                break;
            case Predicate::opType::GT :
                return this->value > double_value->getValue();
                break;
            case Predicate::opType::LT :
                return this->value < double_value->getValue();
                break;
            case Predicate::opType::GE :
                return this->value >= double_value->getValue();
                break;
            case Predicate::opType::LE :
                return this->value <= double_value->getValue();
                break;
            default:
                return false;
                break;
        } 
    }
    double DoubleField::getValue(){
        return this->value;
    }
} // emerald