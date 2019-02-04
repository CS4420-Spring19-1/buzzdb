#include "table.h"
#include "row_store.h"
#include "tuple.h"

namespace emerald {
    
    RowStore::RowStore(): Table(Table::ROW_STORE){};
    void RowStore::insertTuple(Tuple* tuple){
        tuples.push_back(tuple);
    }
    void RowStore::print(){
        for(size_t i = 0; i < tuples.size(); i++){
            tuples[i]->print();
        }
    }
    std::vector<Tuple*> RowStore::getTuples(){
        return this->tuples;
    }
};