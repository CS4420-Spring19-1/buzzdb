#include "table_descriptor.h"
#include <string>
#include "field_type.h"

namespace emerald
{
    TableDescriptor::TableDescriptor(std::vector<std::string> column_names, std::vector<std::string> column_types){
       for(size_t i = 0; i < column_names.size(); i++)
       {
           this->column_names.push_back(column_names[i]);
           if(column_types[i].compare("INTEGER")==0){
               this->column_types.push_back(field_type::INTEGER);
           } else if(column_types[i].compare("STRING")==0){
               this->column_types.push_back(field_type::STRING);
           } else if(column_types[i].compare("BOOLEAN")==0){
               this->column_types.push_back(field_type::BOOLEAN);
           } else if(column_types[i].compare("DOUBLE")==0){
               this->column_types.push_back(field_type::DOUBLE);
           } else {
               this->column_types.push_back(field_type::DATE);
           } 
       }
   };
   void TableDescriptor::print(){
       for(size_t i=0; i<column_names.size(); i++){
           std::cout << column_names[i] << " : " << static_cast<std::underlying_type<field_type>::type>(column_types[i]) << '\n';
       }
   };
   std::vector<field_type> TableDescriptor::getColumnTypes(){
       return column_types;
   };
   int TableDescriptor::getColumnId(std::string column_name){
       for(size_t i=0; i<column_names.size(); i++){
           if(column_name.compare(column_names[i])==0){
               return i;
           }
       }
       return -1;
   };
   field_type TableDescriptor::getColumnType(int index){
       return this->column_types[index];
   }
   std::vector<std::string> TableDescriptor::getColumnNames(){
       return this->column_names;
   }
   void TableDescriptor::setColumnNames(std::vector<std::string> column_names){
       this->column_names = column_names;
   }
    void TableDescriptor::setColumnTypes(std::vector<field_type> column_types){
        this->column_types = column_types;
    }
    TableDescriptor::TableDescriptor(const TableDescriptor &tableDesc){
        this->column_names = tableDesc.column_names;
        this->column_types = tableDesc.column_types;
    }
} // emerald
