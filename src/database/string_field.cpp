#include <iostream>
#include <string_field.h>

namespace emerald
{
    StringField::StringField(std::string v):Field(field_type::STRING),value(v){};

    void StringField::print() const{
        std::cout << value << " ";
    };

    bool StringField::filter(Predicate::opType op, Field* value){
        StringField* str_value = static_cast<StringField*>(value);
        switch (op)
        {
            case Predicate::opType::EQ :
                return this->value.compare(str_value->getValue())==0;
                break;
            case Predicate::opType::NE :
                return this->value.compare(str_value->getValue())!=0;
                break;
            case Predicate::opType::GT :
                return this->value.compare(str_value->getValue())>0;
                break;
            case Predicate::opType::LT :
                return this->value.compare(str_value->getValue())<0;
                break;
            case Predicate::opType::GE :
                return this->value.compare(str_value->getValue())>=0;
                break;
            case Predicate::opType::LE :
                return this->value.compare(str_value->getValue())<=0;
                break;
            default:
                return false;
                break;
        } 
    };

    std::string StringField::getValue() const{
        return this->value;
    };

    StringField::StringField(const StringField& field):Field(field_type::STRING){
        value = field.getValue();
    };
} // emerald
