#include "db_exception.h"

namespace buzzdb {
DbException::DbException(const std::string & what_arg) 
    : std::runtime_error(what_arg), what_message(what_arg) {
}

DbException::DbException(const char * what_arg)
    : std::runtime_error(what_arg), what_message(what_arg) {
}

const char * DbException::what() const throw() {
  std::string error_message = "DbException. " + what_message;
  return error_message.c_str();
}
}
