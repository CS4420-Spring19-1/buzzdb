#pragma once

#include "table.h"
#include "tuple.h"
#include <vector>

namespace emerald
{
    class RowStore : public Table{
        private:
            std::vector<Tuple*> tuples;
        public:
            RowStore();
            void insertTuple(Tuple* tuple);
            void printTable();
    };
}; // emerald
