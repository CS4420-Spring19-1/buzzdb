#pragma once

#include "field.h"

namespace emerald
{
   class IntegerField : public Field{
       private:
            int value;
        public:
            IntegerField(int v);
            void print() const;
            bool filter(Predicate::opType op, Field* value);
            int getValue() const;
            IntegerField(const IntegerField& field);
   }; 
} // emerald
