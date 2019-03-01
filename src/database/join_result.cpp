#include "join_result.h"

namespace emerald
{
    JoinResult::JoinResult(int table_id): Table(table_id, Table::JOIN_INDEX){}

    void JoinResult::insert(TupleSet* tuple_set){
        tuples_.push_back(tuple_set);
    }

    std::vector<TupleSet*> JoinResult::get_tuples() const {
        return tuples_;
    };

    size_t JoinResult::size() const{
        return tuples_.size();
    }

    void JoinResult::print() const{
        
    }

    JoinResult::~JoinResult(){
        for(auto &tuple : tuples_)
        {
            delete tuple;
        }
        tuples_.clear();
    }
} // emerald