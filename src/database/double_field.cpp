#include "double_field.h"
#include "field.h"
#include <iostream>

namespace emerald
{
    DoubleField::DoubleField(double v):Field(field_type::DOUBLE),value(v){};
    void DoubleField::print(){
        std::cout << std::fixed << value << " ";
    };
} // emerald