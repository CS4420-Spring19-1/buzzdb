#pragma once

#include <string>
#include "table.h"
#include "predicate.h"
#include "db_file_iterator.h"
#include <iostream>

namespace emerald
{
  class SeqScan{
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
      void reset(int table_id, std::string table_alias) {
        this->table_id = table_id;
        this->table_alias = table_alias;
      }

      SeqScan(TransactionId* tid, int table_id) {
        // this(tid, tableid, Database.getCatalog().getTableName(tableid));
      }

      void open() {
        iterator = Database.getCatalog().getDatabaseFile(tableid).iterator(tid);
        iterator->open();
      }

      TupleDesc* get_tuple_desc() {
        // return Database.getCatalog().getTupleDesc(tableid);
      }

      bool hasNext() {
        if (iterator == NULL) return false;
        return iterator->hasNext();
      }

      Tuple* next() {
        if (iterator == null) {
          // throw new NoSuchElementException();
        }
        Tuple* t = iterator->next();

        if (t == null) {
          // throw new NoSuchElementException();
        }

        return t;
      }

      void close() {
        iterator = null;
      }

      void rewind() {
        close();
        open();
      }
  }
    
} // emerald
