#pragma once
#include <vector>
#include "tuple_descriptor.h"
#include "field.h"

namespace emerald
{
    class TupleSet {
        private:
            std::vector<TupleDescriptor*> tuple_descriptors_;
        public:
            TupleSet();
            void insert(TupleDescriptor* tuple_desc);
            int get_tuple_id(int table_id);
            bool equals(const TupleSet* tuple_set) const;
            std::vector<TupleDescriptor*> get_tuple_descs() const;
    };
} // emerald