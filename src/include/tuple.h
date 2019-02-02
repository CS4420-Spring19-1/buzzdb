#pragma once
#include<vector>

#include "field.h"

namespace emerald{
    class Tuple{
        private:
            std::vector<Field*> fields;
        public:
            Tuple();
            Tuple(std::vector<Field*> fields);
            void print();
    };
};