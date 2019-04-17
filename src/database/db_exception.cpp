#include "db_exception.h"

namespace emerald {
const char * DbException::what() const throw() {
  return "DbException occurred.";
}
}
