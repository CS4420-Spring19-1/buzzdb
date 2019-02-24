#pragma once
#include "field.h"
#include <vector>

namespace emerald
{
    class Dimension {
        private:
            std::vector<Field*> fields_;
        public:
            Dimension();

            Dimension(std::vector<Field*> fields);
            bool operator==(const Dimension& dimension) const;
            bool operator<(const Dimension& dimension) const;
            size_t size() const;
            Field* get_field(int index) const;
            std::vector<Field*> get_fields() const;
    };
} // emerald
