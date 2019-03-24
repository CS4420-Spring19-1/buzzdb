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

            ~RowStore();

            // possible to add override keyword
            void print() const;

            // possible to add override keyword
            size_t size() const;

            void insertTuple(Tuple* tuple);

            std::vector<Tuple*> getTuples() const;

            void copy_tuples(Table* table);

            void insert_tuples(std::vector<Tuple*> tuples);

            void merge_and_insert(Tuple* tuple_1, Tuple* tuple_2);

            Tuple* get_tuple(int index) const;
    };
}; // emerald
