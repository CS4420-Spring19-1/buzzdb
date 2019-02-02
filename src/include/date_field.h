#pragma once

#include "field.h"
#include <ctime>
#include <string>

namespace emerald
{
    class DateField : public Field {
        private:
            std::time_t value;
        public:
            DateField(std::string v);
            void print();
    };
} // emerald
