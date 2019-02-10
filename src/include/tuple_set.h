#pragma once
#include <vector>
#include "tuple_descriptor.h"

namespace emerald
{
    class TupleSet {
        private:
            std::vector<TupleDescriptor*> tuple_descriptors_;
        public:
            TupleSet();
    };
} // emerald