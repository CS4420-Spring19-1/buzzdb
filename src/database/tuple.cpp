#include "tuple.h"
#include <iostream>

namespace emerald
{
    Tuple::Tuple(){

    }
    
    Tuple::Tuple(std::vector<Field*> fields){
        fields_ = fields;
    };

    void Tuple::print() const{
        for(auto &field : fields_)
        {
            field->print();
        }
        std::cout << std::endl;
    };

    Field* Tuple::getField(int index) const{
        return fields_[index];
    };

    // Copy constructor for Tuple class
    Tuple::Tuple(const Tuple& tuple){
        fields_ = tuple.get_fields();
    };

    std::vector<Field*> Tuple::get_fields() const{
        return fields_;
    };

    void Tuple::append_fields(std::vector<Field*> fields){
        fields_.insert(fields_.end(), fields.begin(), fields.end());
    };

    void Tuple::add_field(Field* field){
        fields_.push_back(field);
    }
} // emerald
