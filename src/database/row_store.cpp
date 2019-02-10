#include "table.h"
#include "row_store.h"
#include "tuple.h"

namespace emerald {
    
    RowStore::RowStore(): Table(Table::ROW_STORE){};
    
    void RowStore::insertTuple(Tuple* tuple){
        tuples_.push_back(tuple);
    };

    void RowStore::print() const{
        for(auto &tuple : tuples_){
            tuple->print();
        }
    };

    std::vector<Tuple*> RowStore::getTuples() const{
        return tuples_;
    };

    // Returns size of the table
    int RowStore::size() const{
        return tuples_.size();
    };

    /* Used to populate the table by copying the tuples from another table.*/
    void RowStore::copy_tuples(Table* table){
        if (table->getStorageType()==Table::storageType::ROW_STORE) {
            insert_tuples(static_cast<RowStore*>(table)->getTuples());
        } 
    };

    /* Inserts the array of Tuples provided. This is a deep copy of the tuples */
    void RowStore::insert_tuples(std::vector<Tuple*> tuples){
        tuples_ = tuples;
    };

    /* Merges the given tuples and inserts the merged tuple into the table */
    void RowStore::merge_and_insert(Tuple* tuple_1, Tuple* tuple_2){
        Tuple* result = tuple_1; // this should do a deep copy of tuple_1 to result
        result->append_fields(tuple_2->get_fields()); // this appends the rest of the fields to the result
        insertTuple(result);
    };
};