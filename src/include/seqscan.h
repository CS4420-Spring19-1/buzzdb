#pragma once

#include <string>
#include "table.h"
#include "predicate.h"
#include "db_file_iterator.h"
#include <iostream>

namespace emerald {
class SeqScan {
  private:
    TransactionId* tid;
    int table_id;
    std::string table_alias;
    DbFileIterator* iterator;

  public:
    /**
     * Creates a sequential scan over the specified table as a part of the
     * specified transaction.
     * 
     * @param tid
     *            The transaction this scan is running as a part of.
     * @param tableid
     *            the table to scan.
     * @param tableAlias
     *            the alias of this table (needed by the parser); the returned
     *            tupleDesc should have fields with name tableAlias.fieldName
     *            (note: this class is not responsible for handling a case where
     *            tableAlias or fieldName are null. It shouldn't crash if they
     *            are, but the resulting name can be null.fieldName,
     *            tableAlias.null, or null.null).
     */
    SeqScan(TransactionId* tid, int table_id, std::string table_alias);
    SeqScan(TransactionId* tid, int table_id);

    std::string get_table_name();

    /**
    * @return Return the alias of the table this operator scans. 
    **/
    std::string get_alias();

    /**
     * Reset the tableid, and tableAlias of this operator.
     * @param tableid
     *            the table to scan.
     * @param tableAlias
     *            the alias of this table (needed by the parser); the returned
     *            tupleDesc should have fields with name tableAlias.fieldName
     *            (note: this class is not responsible for handling a case where
     *            tableAlias or fieldName are null. It shouldn't crash if they
     *            are, but the resulting name can be null.fieldName,
     *            tableAlias.null, or null.null).
     */
    void Reset(int table_id, std::string table_alias);

    void Open();

    /**
     * Returns the TupleDesc with field names from the underlying HeapFile,
     * prefixed with the tableAlias string from the constructor. This prefix
     * becomes useful when joining tables containing a field(s) with the same
     * name.
     * 
     * @return the TupleDesc with field names from the underlying HeapFile,
     *         prefixed with the tableAlias string from the constructor.
     */
    TupleDesc* get_tuple_desc();

    bool HasNext();

    Tuple* Next();

    void Close();

    void Rewind();
}
  
} // emerald
