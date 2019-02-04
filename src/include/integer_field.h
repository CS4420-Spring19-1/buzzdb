#pragma once

#include "field.h"

namespace emerald
{
   class IntegerField : public Field{
       private:
            int value;
        public:
            IntegerField(int v);
            void print();
            bool filter(Predicate::opType op, Field* value);
            int getValue();
   }; 
} // emerald
