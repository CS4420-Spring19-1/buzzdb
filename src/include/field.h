#pragma once

#include "field_type.h"

namespace emerald
{
  class Field
  {
    private:
      field_type type;
    public:
      Field();
      Field(field_type type);
      virtual void print(){};
  };
  
  
    
}; // emerald
