#include "no_such_element_exception.h"

namespace buzzdb {
NoSuchElementException::NoSuchElementException(const std::string & what_arg) 
    : std::runtime_error(what_arg), what_message(what_arg) {
}

NoSuchElementException::NoSuchElementException(const char * what_arg)
    : std::runtime_error(what_arg), what_message(what_arg) {
}

const char * NoSuchElementException::what() const throw() {
  std::string error_message = "NoSuchElementException. " + what_message;
  return error_message.c_str();
}
}
