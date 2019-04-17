#pragma once

#include <exception>

namespace buzzdb {
class DbException : public std::exception {
 public:
  virtual const char * what() const throw();
};
}
