#pragma once

#include "field.h"

namespace emerald
{
    class DoubleField : public Field{
        private:
            double value;
        public:
            DoubleField(double v);
            void print() const;
            bool filter(Predicate::opType op, Field* value);
            double getValue() const;
            DoubleField(const DoubleField& field);
    };
} // emerald
