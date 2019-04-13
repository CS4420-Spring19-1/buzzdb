#pragma once

#include <string>
#include "db_file.h"
#include "db_file_iterator.h"
#include "transaction_id.h"

namespace emerald {
class SeqScan {
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
  SeqScan(TransactionId & tid, int table_id, std::string table_alias);

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
  TupleDesc get_tuple_desc() const;

  bool HasNext();

  Tuple *Next();

  void Close();

  void Rewind();

 private:
  DbFile * db_file;
  std::string table_alias;
  DbFileIterator * iterator;
};
}
