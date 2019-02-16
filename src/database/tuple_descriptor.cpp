#include "tuple_descriptor.h"

namespace emerald
{
    TupleDescriptor::TupleDescriptor(int table_id, int tuple_id){
        table_id_ = table_id;
        tuple_id_ = tuple_id;
    }

    int TupleDescriptor::get_table_id() const{
        return table_id_;
    }

    int TupleDescriptor::get_tuple_id() const {
        return tuple_id_;
    }
} // emerald
