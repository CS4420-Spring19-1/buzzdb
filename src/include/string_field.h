#pragma once

#include "field.h"
#include <string>

namespace emerald
{
    class StringField : public Field{
        private:
            std::string value;
        public:
            StringField(std::string v);
            void print();
            bool filter(Predicate::opType op, Field* value);
            std::string getValue();
    };
} // emerald
