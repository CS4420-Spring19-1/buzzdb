#pragma once
#include "tuple_set.h"
#include "table.h"

namespace emerald
{
    class JoinResult: public Table {
        private:
            std::vector<TupleSet*> tuples_;
        public:
            JoinResult(int table_id);
            JoinResult();
            void insert(TupleSet* tuple_set);
            std::vector<TupleSet*> get_tuples() const;

            size_t size() const;
            void print() const;
            ~JoinResult();
    };
} // emerald