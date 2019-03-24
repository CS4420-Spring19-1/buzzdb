#include "table.h"
#include "row_store.h"
#include "tuple.h"
#include <iostream>

namespace emerald {
    
    RowStore::RowStore(int table_id): Table(table_id, Table::ROW_STORE){
    };
    
    RowStore::~RowStore() {
        std::cout << "Calling clear\n";
        for(auto &tuple : tuples_){
            delete tuple;
        }
        tuples_.clear();
        std::cout << "Completed clear\n";
    }

    void RowStore::print() const {
        for (auto &tuple : tuples_) {
            tuple->print();
        }
    };

    // Returns size of the table
    size_t RowStore::size() const {
        return tuples_.size();
    };

    void RowStore::insertTuple(Tuple* tuple) {
        tuples_.push_back(tuple);
    };


    std::vector<Tuple*> RowStore::getTuples() const {
        return tuples_;
    };

    /* Used to populate the table by copying the tuples from another table.*/
    void RowStore::copy_tuples(Table* table) {
        if (table->getStorageType()==Table::storageType::ROW_STORE) {
            insert_tuples(static_cast<RowStore*>(table)->getTuples());
        } 
    };

    /* Inserts the array of Tuples provided. This is a deep copy of the tuples */
    void RowStore::insert_tuples(std::vector<Tuple*> tuples) {
        tuples_ = tuples;
    };

    /* Merges the given tuples and inserts the merged tuple into the table */
    void RowStore::merge_and_insert(Tuple* tuple_1, Tuple* tuple_2) {
        Tuple* result = tuple_1; // this should do a deep copy of tuple_1 to result
        result->append_fields(tuple_2->get_fields()); // this appends the rest of the fields to the result
        insertTuple(result);
    };

    Tuple* RowStore::get_tuple(int index) const {
        return tuples_[index];
    }
};