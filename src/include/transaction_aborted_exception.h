#pragma once

#include <exception>

namespace buzzdb {
class TransactionAbortedException : public std::exception {
 public:
  virtual const char * what() const throw();
};
}
