#pragma once

#include "table.h"
#include "predicate.h"

namespace emerald
{
    class JoinCondition {
        private:
            Table* table_1_;
            Table* table_2_;
            Predicate* predicate_;
        public:
            JoinCondition();
            JoinCondition(Table* table_1, Table* table_2, Predicate* predicate);
            Table* get_table_1() const;
            Table* get_table_2() const;
            Predicate* get_predicate() const;
    };
} // emerald
