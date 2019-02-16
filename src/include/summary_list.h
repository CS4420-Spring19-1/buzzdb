#pragma once

#include "summary.h"
#include "tuple_set.h"

namespace emerald
{
    class SummaryList : public Summary {
        private:
            std::vector<TupleSet*> tuple_set_list_;
        public:
            SummaryList();
            void add_tuple_set(TupleSet* tuple_set);

    };
} // emerald
