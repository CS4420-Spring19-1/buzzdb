#pragma once

#include <string>
#include "buffer_pool.h"
#include "catalog.h"
#include "log_file.h"

namespace emerald {
/**
 * This class is a class that initializes several static variables used by the
 * database system.
 * 
 * It provides a set of methods that can be used to access these variables from
 * anywhere.
 * 
 * This class is designed as a singleton, meaning that there is only one
 * instance of the class can exist at a time and that instance is a static
 * member of the class.
 */
class Database {
 public:
  /**
   * Used to access the singular instance of the Database class.
   * 
   * The instance is initialized on the first call of this function.
   */
  static Database * get_instance();

  static LogFile * get_log_file();

  static BufferPool * get_buffer_pool();

  static Catalog * get_catalog();

  static BufferPool * ResetBufferPool(int pages);

  /**
   * Resets the database, primarily used for unit tests.
   */
  static void Reset();

 private:
  /**
   * Constructor for the Database class.
   * Declared private as this Database class is a singleton.
   */
  Database();

  /**
   * Destructor for the Database class.
   * Declared private as this Database class is a singleton.
   */
  ~Database();

  const std::string LOGFILENAME = "log";

  static Database * instance;

  Catalog * catalog;

  BufferPool * buffer_pool;

  LogFile * log_file;
};
}
