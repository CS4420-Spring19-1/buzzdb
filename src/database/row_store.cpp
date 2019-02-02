#include "table.h"
#include "row_store.h"
#include "tuple.h"

namespace emerald {
    
    RowStore::RowStore(): Table(Table::ROW_STORE){};
    void RowStore::insertTuple(Tuple* tuple){
        tuples.push_back(tuple);
    }
    void RowStore::printTable(){
        for(size_t i = 0; i < tuples.size(); i++){
            tuples[i]->print();
        }
    }

};