#include "integer_field.h"
#include <iostream>

namespace emerald
{
    IntegerField::IntegerField(int v):Field(field_type::INTEGER),value(v){};
    void IntegerField::print(){
        std::cout << value << " ";
    }
} // emerald
