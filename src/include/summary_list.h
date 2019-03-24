#pragma once

#include "summary.h"
#include "tuple_set.h"

namespace emerald {
    class SummaryList : public Summary {
        private:
            std::vector<TupleSet*> tuple_set_list_;

        public:
            SummaryList();

            void add_tuple_set(TupleSet* tuple_set);

            std::vector<TupleSet*> get_tuples() const;

            // can add override keyword here
            size_t size() const;
    };
} // emerald
