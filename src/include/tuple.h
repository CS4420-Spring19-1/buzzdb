#pragma once
#include<vector>

#include "field.h"

namespace emerald{
    class Tuple{
        private:
            std::vector<Field*> fields_;
        public:
            Tuple();
            Tuple(std::vector<Field*> fields);
            void print() const;
            Field* getField(int index) const;
            Tuple(const Tuple& tuple);
            std::vector<Field*> get_fields() const;
            void append_fields(std::vector<Field*> fields);
    };
};