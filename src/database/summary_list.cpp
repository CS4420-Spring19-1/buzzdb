#include "summary_list.h"

namespace emerald
{
    SummaryList::SummaryList(){

    }

    void SummaryList::add_tuple_set(TupleSet* tuple_set){
        tuple_set_list_.push_back(tuple_set);
    }
} // emerald
