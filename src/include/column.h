#pragma once
#include "field.h"
#include <vector>

namespace emerald
{
    class Column
    {
        private:
            std::vector<Field*> fields_;
        public:
            Column(/* args */);
            ~ Column();
            size_t size() const;
            void insert(Field* field);
            Field* get_field(int index) const;
            std::vector<Field*> get_fields() const;
    };
} // emerald
