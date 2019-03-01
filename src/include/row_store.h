#pragma once

#include "table.h"
#include <vector>

namespace emerald
{
    class RowStore : public Table{
        private:
            std::vector<Tuple*> tuples_;
        public:
            RowStore(int table_id);
            void insertTuple(Tuple* tuple);
            void print() const;
            std::vector<Tuple*> getTuples() const;
            size_t size() const;
            void copy_tuples(Table* table);
            void insert_tuples(std::vector<Tuple*> tuples);
            void merge_and_insert(Tuple* tuple_1, Tuple* tuple_2);
            Tuple* get_tuple(int index) const;
            ~RowStore();
    };
}; // emerald
