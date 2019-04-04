#pragma once

#include <string>
#include "buffer_pool.h"
#include "catalog.h"

namespace emerald {
class Database {
 public:
  Database();

  ~Database();

  static LogFile * get_log_file();

  static BufferPool * get_buffer_pool();

  static Catalog * get_catalog();

  static BufferPool * ResetBufferPool(int pages);

  static void Reset();

 private:
  const std::string LOGFILENAME = "log";

  static Database * instance;

  Catalog * catalog;
  BufferPool * buffer_pool;
  LogFile * log_file;
};
}
