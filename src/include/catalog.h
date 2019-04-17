#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "db_file.h"
#include "tuple_desc.h"

namespace buzzdb {

/**
 * The Catalog keeps track of all available tables in the database and their
 * associated schemas.
 * For now, this is a stub catalog that must be populated with tables by a
 * user program before it can be used -- eventually, this should be converted
 * to a catalog that reads a catalog table from disk.
 * 
 * @Threadsafe
 */
class Catalog {
 public:
  /**
   * Default constructor for the Catalog class.
   */
  Catalog();

  /**
   * Destructor for the Catalog class.
   */
  ~Catalog();

  /**
   * Add a new table to the catalog.
   * This table's contents are stored in the specified DbFile.
   * @param file the contents of the table to add;  file.getId() is the identfier of
   *    this file/tupledesc param for the calls getTupleDesc and getFile
   * @param name the name of the table -- may be an empty string.  May not be null.  If a name
   * @param pkeyField the name of the primary key field
   * conflict exists, use the last table to be added as the table for a given name.
   */
  void AddTable(DbFile * file, std::string name, std::string p_key_field);

  void AddTable(DbFile* file, std::string name);

  /**
   * Return the id of the table with a specified name,
   * @throws NoSuchElementException if the table doesn't exist
   */
  int get_table_id(std::string name);

  /**
   * Returns the tuple descriptor (schema) of the specified table
   * @param tableid The id of the table, as specified by the DbFile.getId()
   *     function passed to addTable
   * @throws NoSuchElementException if the table doesn't exist
   */
  TupleDesc get_tuple_desc(int table_id);

  std::string get_table_name(int table_id);

  DbFile * get_db_file(int table_id);

  std::string get_primary_key(int table_id);

  std::unordered_map<int, DbFile*>::iterator TableIdIterator();

  void Clear();

  void LoadSchema();

 private:
  std::unordered_map<int, std::string> * names;
  std::unordered_map<int, DbFile *> * db_fields;
  std::unordered_map<int, std::string> * p_fields;
};
}
