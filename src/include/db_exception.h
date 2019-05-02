#pragma once

#include <stdexcept>

namespace buzzdb {
class DbException : public std::runtime_error {
 public:
  explicit DbException(const std::string & what_arg);

  explicit DbException(const char * what_arg);

  virtual const char * what() const throw();

 private:
  std::string what_message;
};


}
