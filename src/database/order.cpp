#include "order.h"
#include "row_store.h"
#include <algorithm>
#include <iostream>

namespace emerald
{
    struct Comparator{
    // should this be declared in header file?
        std::vector<int> fields;
        std::vector<bool> is_asc;

        bool operator()(const Tuple* t1, const Tuple* t2){
            int index=0;
            for(auto &field : fields)
            {
                if (t1->getField(field)->filter(Predicate::EQ, t2->getField(field))) {
                    /* If the field is equal, check the next field */
                    index++;
                    continue; 
                } else {
                    return is_asc[index]? t2->getField(field)->filter(Predicate::LT, t1->getField(field))
                                        : t1->getField(field)->filter(Predicate::LT, t2->getField(field));
                }
                
            }
            return false;
        }

        Comparator(std::vector<int> fields, std::vector<bool> is_asc) {
            this->fields = fields;
            this->is_asc = is_asc;
        }
    };

    Table* OrderTable(Table* table, std::vector<std::string> order_by_columns, std::vector<bool> is_asc){
        /* By the time, ordering step is reached, the table will be in a row store format. */
        std::vector<Tuple*> tuples = static_cast<RowStore*>(table)->getTuples();

        // for each column, find the column index
        std::vector<int> indexes;
        for(auto &column : order_by_columns)
        {
            int index = 0;
            for(auto &column_desc : table->getTableDescriptor()->get_columns()){
                if (column.compare(column_desc->get_column_name())==0) {
                    indexes.push_back(index);
                    break;
                }
                index++;   
            }
        }
        std::sort(tuples.begin(), tuples.end(), Comparator(indexes, is_asc));
        RowStore* ordered_result = new RowStore(-1);
        ordered_result->insert_tuples(tuples);
        return ordered_result;
    }
} // emerald
