#pragma once

#include <exception>

namespace emerald {
class TransactionAbortedException : public std::exception {
 public:
  virtual const char * what() const throw();
};
}
