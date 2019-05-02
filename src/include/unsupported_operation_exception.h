#pragma once

#include <stdexcept>
#include <string>

namespace buzzdb {
class UnsupportedOperationException: public std::runtime_error {
 public:
  explicit UnsupportedOperationException(const std::string & what_arg);

  explicit UnsupportedOperationException(const char * what_arg);

  virtual const char * what() const throw();

 private:
  std::string what_message;
};
}