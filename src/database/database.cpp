#include "database.h"

namespace buzzdb {
Database * Database::instance = nullptr;

Database * Database::get_instance() {
  if (instance == nullptr) {
    instance = new Database();
  }
  return instance;
}

LogFile * Database::get_log_file() {
}

BufferPool * Database::get_buffer_pool() {
  return instance->buffer_pool;
}

Catalog * Database::get_catalog() {
  return instance->catalog;
}

BufferPool * Database::ResetBufferPool(int pages) {
  delete instance->buffer_pool;
  instance->buffer_pool = new BufferPool(pages, instance->catalog);
}

void Database::Reset() {
  delete instance;
  instance = new Database();
}

Database::Database() {
  catalog = new Catalog();
  buffer_pool = new BufferPool(BufferPool::DEFAULT_PAGES, catalog);
  /* File class does not exist
  try {
    log_file = new LogFile(new File(this->LOGFILENAME));
  } catch {
    // catch IOException here
  }
  */
}

Database::~Database() {
  delete catalog;
  delete buffer_pool;
  delete log_file;
}
} 
