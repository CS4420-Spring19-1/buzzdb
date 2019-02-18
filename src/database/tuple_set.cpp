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

} // emerald
