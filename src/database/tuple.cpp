#include "tuple.h"
#include <iostream>

namespace emerald
{
    Tuple::Tuple(std::vector<Field*> fields){
        this->fields = fields;
    }
    void Tuple::print(){
        for(size_t i = 0; i < fields.size(); i++)
        {
            fields[i]->print();
        }
        std::cout << std::endl;
    }
} // emerald
