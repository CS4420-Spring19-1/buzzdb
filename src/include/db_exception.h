#pragma once

#include <exception>

namespace emerald {
class DbException : public std::exception {
 public:
  virtual const char * what() const throw();
};
}
