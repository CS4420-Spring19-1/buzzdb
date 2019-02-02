#include "date_field.h"
#include <sstream>
#include <iostream>
#include <iomanip>

namespace emerald
{ 
    DateField::DateField(std::string v): Field(field_type::DATE){
        std::string date_format = "%m/%d/%y";
        std::istringstream ss(v);
        std::tm dt;
        ss >> std::get_time(&dt, date_format.c_str());
        this->value = std::mktime(&dt);
    }
    void DateField::print(){
        std::tm dt = *std::localtime(&value);
        std::stringstream wss;
        wss << (std::put_time(&dt, "%m/%d/%y"));
        std::cout << wss.str() << " ";
    }
} // emerald