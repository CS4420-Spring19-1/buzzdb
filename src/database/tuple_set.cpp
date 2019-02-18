#include "tuple_set.h"

namespace emerald
{
    void TupleSet::insert(TupleDescriptor* tuple_desc){
        tuple_descriptors_.push_back(tuple_desc);
    }

    // Given a table_id, this method returns the tuple id, in the tuple set, that belongs to the table
    // TO DO: If there are more than one tuple that belongs to the table, what should be done???
    int TupleSet::get_tuple_id(int table_id){
        for(auto &tuple_desc : tuple_descriptors_)
        {
            if (tuple_desc->get_table_id()==table_id) {
                return tuple_desc->get_tuple_id();
            }
            
        }
        return -1;
    }

    TupleSet::TupleSet(){}

    bool TupleSet::equals(const TupleSet* tuple_set) const{
        bool isEqual = true;
        for(size_t i = 0; i < tuple_set->get_tuple_descs().size(); i++)
        {
            if(!(tuple_descriptors_[i]->equals(tuple_set->get_tuple_descs()[i]))){
                isEqual = false;
                break;
            }
        }
        return isEqual;
    }

    std::vector<TupleDescriptor*> TupleSet::get_tuple_descs() const{
        return tuple_descriptors_;
    }
} // emerald
