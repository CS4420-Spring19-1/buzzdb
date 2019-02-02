#include <iostream>
#include <string_field.h>

namespace emerald
{
    StringField::StringField(std::string v):Field(field_type::STRING),value(v){};
    void StringField::print(){
        std::cout << value << " ";
    }
} // emerald
