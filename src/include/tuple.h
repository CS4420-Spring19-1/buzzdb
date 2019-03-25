#pragma once
#include<vector>

#include "field.h"

namespace emerald {
    class Tuple {
        private:
            std::vector<Field*> fields_;

        public:
            Tuple();

            Tuple(std::vector<Field*> fields);

            Tuple(const Tuple& tuple);

            void print() const;
             
            Field* getField(int index) const;

            std::vector<Field*> get_fields() const;

            void append_fields(std::vector<Field*> fields);

            void add_field(Field* field);
    };
};