#include "unsupported_operation_exception.h"

namespace buzzdb {
UnsupportedOperationException::UnsupportedOperationException(const std::string & what_arg) 
    : std::runtime_error(what_arg), what_message(what_arg) {
}

UnsupportedOperationException::UnsupportedOperationException(const char * what_arg)
    : std::runtime_error(what_arg), what_message(what_arg) {
}

const char * NoSuchElementException::what() const throw() {
  std::string error_message = "UnsupportedOperationException. " + what_message;
  return error_message.c_str();
}
}