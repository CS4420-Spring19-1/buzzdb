#include "db_exception.h"

namespace buzzdb {
const char * DbException::what() const throw() {
  return "DbException occurred.";
}
}
