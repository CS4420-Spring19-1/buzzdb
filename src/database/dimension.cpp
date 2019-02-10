#include "dimension.h"

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
        bool is_less = true;
        for(size_t i = 0; i<fields_.size(); i++)
        {
            if(!fields_[i]->filter(Predicate::LE, dimension.get_field(i))){
                is_less = false;
                break;
            }
        }
        return is_less;
    };

    int Dimension::size() const {
        return fields_.size();
    };

    Field* Dimension::get_field(int index) const{
        return fields_[index];
    }
} // emerald
