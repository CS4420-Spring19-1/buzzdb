#pragma once

namespace emerald
{
    class TupleDescriptor {
        private:
            int table_id_;
            int tuple_id_;
        public:
            TupleDescriptor();
    };
} // emerald