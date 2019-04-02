// is this necessary? I am genuinely not sure.
#pragma once

namespace emerald {
    // not sure how this class works
    class TupleDesc {
        private:
            int table_id_;
            int tuple_id_;
        public:
            TupleDesc();
            TupleDesc(int table_id, int tuple_id);
            int get_table_id() const;
            int get_tuple_id() const;
            bool equals(const TupleDescriptor* tuple_desc) const;
            TupleDesc(const TupleDescriptor &tuple_desc);
    };
} // emerald