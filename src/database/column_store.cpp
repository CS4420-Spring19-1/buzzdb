#include "column_store.h"

namespace emerald
{
    ColumnStore::ColumnStore(int table_id) : Table(table_id, Table::COLUMN_STORE){};

    void ColumnStore::print() const{

    } 

    size_t ColumnStore::size() const{
        return columns_[0]->size();
    }

    void ColumnStore::insert_tuple(std::vector<Field*> fields) {
        if (columns_.size()==0) {
            /* we are inserting the first row. Initialize the columns */
            for(size_t i = 0; i < fields.size(); i++)
            {
                columns_.push_back(new Column());
            }
            
        }
        
        for(size_t i = 0; i < fields.size(); i++)
        {
            columns_[i]->insert(fields[i]);
        }
        
    }

    std::vector<Column*> ColumnStore::get_columns() const {
        return columns_;
    }

    Column* ColumnStore::get_column(int index) const {
        return columns_[index];
    }
} // emerald
