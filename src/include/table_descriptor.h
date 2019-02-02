#pragma once

#include<vector>
#include<string>
#include <unordered_map>
#include<iostream>
#include "field_type.h"

namespace emerald
{
   class TableDescriptor
   {
    private:
       std::vector<std::string> column_names;
       std::vector<field_type> column_types; 
    public:
        TableDescriptor();
        TableDescriptor(std::vector<std::string> column_names, std::vector<std::string> column_types);  
        void print();    
        std::vector<field_type> getColumnTypes();
   };
}; // emerald
