#include "dimension.h"
#include <iostream>

namespace emerald
{
    Dimension::Dimension(std::vector<Field*> fields){
        fields_ = fields;
    };

    bool Dimension::operator==(const Dimension& dimension) const{
        if (fields_.size()!=dimension.size()) {
 
            return false;
        }
        bool is_equal = true;
        for(size_t i = 0; i<fields_.size(); i++)
        {
            if(!fields_[i]->filter(Predicate::EQ, dimension.get_field(i))){
                is_equal = false;
                break;
            }
        }
        return is_equal;
    };

    bool Dimension::operator<(const Dimension& dimension) const {
        if (fields_.size()!=dimension.size()) {
            return false;
        }

        //bool is_less = true;
        size_t i = 0;
        for(; i<fields_.size(); i++)
        {
            if(!fields_[i]->filter(Predicate::EQ, dimension.get_field(i))){
                // std::cout << "Setting is less false\n";
                // fields_[i]->print();
                // dimension.get_field(i)->print();
                // is_less = false;
                break;
            }
        }
        if(i == fields_.size()){
            return false;
        }

        return fields_[i]->filter(Predicate::LT, dimension.get_field(i));
    };

    size_t Dimension::size() const {
        return fields_.size();
    };

    Field* Dimension::get_field(int index) const{
        return fields_[index];
    }

    std::vector<Field*> Dimension::get_fields() const{
        return fields_;
    }
} // emerald
