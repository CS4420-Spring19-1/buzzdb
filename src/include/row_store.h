#pragma once

#include "table.h"
#include "tuple.h"
#include <vector>

namespace emerald
{
    class RowStore : public Table{
        private:
            std::vector<Tuple*> tuples_;
        public:
            RowStore();
            void insertTuple(Tuple* tuple);
            void print() const;
            std::vector<Tuple*> getTuples() const;
            virtual int size() const;
            virtual void copy_tuples(Table* table);
            void insert_tuples(std::vector<Tuple*> tuples);
            void merge_and_insert(Tuple* tuple_1, Tuple* tuple_2);
    };
}; // emerald
