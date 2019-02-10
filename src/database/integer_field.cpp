#include "integer_field.h"
#include <iostream>

namespace emerald
{
    IntegerField::IntegerField(int v):Field(field_type::INTEGER),value(v){};

    void IntegerField::print() const{
        std::cout << value << " ";
    };

    bool IntegerField::filter(Predicate::opType op, Field* value){
        IntegerField* int_value = static_cast<IntegerField*>(value);
        switch (op)
        {
            case Predicate::opType::EQ :
                return this->value==int_value->getValue();
                break;
            case Predicate::opType::NE :
                return this->value!= int_value->getValue();
                break;
            case Predicate::opType::GT :
                return this->value > int_value->getValue();
                break;
            case Predicate::opType::LT :
                return this->value < int_value->getValue();
                break;
            case Predicate::opType::GE :
                return this->value >= int_value->getValue();
                break;
            case Predicate::opType::LE :
                return this->value <= int_value->getValue();
                break;
            default:
                return false;
                break;
        } 
    };

    int IntegerField::getValue() const{
        return this->value;
    };

    IntegerField::IntegerField(const IntegerField& field){
        value = field.getValue();
    };
} // emerald
