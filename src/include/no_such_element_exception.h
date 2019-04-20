#pragma once

#include <stdexcept>
#include <string>

namespace buzzdb {
class NoSuchElementException : std::runtime_error {
 public:
  explicit NoSuchElementException(const std::string & what_arg);

  explicit NoSuchElementException(const char * what_arg);

  virtual const char * what() const throw();

 private:
  std::string what_message;
};
}
