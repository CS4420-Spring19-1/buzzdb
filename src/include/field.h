#pragma once

#include "field_type.h"
#include "predicate.h"

namespace emerald {
  class Field
  {
    private:
      field_type type;
    
    public:
      Field();
      
      Field(field_type type);
      
      virtual void print() const = 0;
      
      // if filter returns true, the tuple/attribute value needs to be included in the result
      virtual bool filter(Predicate::opType op, Field* value) = 0;

      // maybe should declare copy constructor and getter as virtual here too
  };
}; // emerald
