#include "join_condition.h"

namespace emerald
{
    JoinCondition::JoinCondition(Table* table_1, Table* table_2, Predicate* predicate){
        table_1_ = table_1;
        table_2_ = table_2;
        predicate_ = predicate;
    };

    Table* JoinCondition::get_table_1() const{
        return table_1_;
    };

    Table* JoinCondition::get_table_2() const{
        return table_2_;
    };

    Predicate* JoinCondition::get_predicate() const{
        return predicate_;
    };
} // emerald
