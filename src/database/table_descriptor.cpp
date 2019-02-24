#include "table_descriptor.h"
#include <string>
#include "field_type.h"
#include <iostream>

namespace emerald
{
    TableDescriptor::TableDescriptor(){
        
    }

    TableDescriptor::TableDescriptor(int table_id, std::vector<std::string> column_names, std::vector<std::string> column_types){
       for(size_t i = 0; i < column_names.size(); i++)
       {
           field_type type;
           if(column_types[i].compare("INTEGER")==0){
               type = field_type::INTEGER;
           } else if(column_types[i].compare("STRING")==0){
               type = field_type::STRING;
           } else if(column_types[i].compare("BOOLEAN")==0){
               type = field_type::BOOLEAN;
           } else if(column_types[i].compare("DOUBLE")==0){
               type = field_type::DOUBLE;
           } else {
               type = field_type::DATE;
           }
           columns_.push_back(new ColumnDescriptor(table_id, i, column_names[i], type)); 
       }
   };

   void TableDescriptor::print() const{
       std::cout << "Inside Table Descriptor print\n";
       for(auto &column : columns_){
           std::cout << column->get_column_name() << " : " << static_cast<std::underlying_type<field_type>::type>(column->get_column_type()) << '\n';
       }
   };

    int TableDescriptor::getColumnId(std::string column_name) const{
       for(size_t i = 0; i<columns_.size(); i++){
           if(column_name.compare(columns_[i]->get_column_name())==0){
               return i;
           }
       }
       return -1;
    };

    field_type TableDescriptor::getColumnType(int index) const{
       return columns_[index]->get_column_type();
    };


    TableDescriptor::TableDescriptor(const TableDescriptor &tableDesc){
        columns_ = tableDesc.get_columns();
    };

    //Appends the given array of columns to the existing columns array
    void TableDescriptor::AppendColumns(std::vector<ColumnDescriptor*> columns){
        for(auto column : columns)
        {
            columns_.push_back(column);
        }
    };

    std::vector<ColumnDescriptor*> TableDescriptor::get_columns() const{
        return columns_;
    }

    ColumnDescriptor* TableDescriptor::get_column(std::string name) const{
        for(auto &column : columns_){
           if(name.compare(column->get_column_name())==0){
               return column;
           }
        }
        return nullptr;
    }

    ColumnDescriptor* TableDescriptor::get_column(int index) const {
        return columns_[index];
    }

    size_t TableDescriptor::size() const{
        return columns_.size();
    }
} // emerald
