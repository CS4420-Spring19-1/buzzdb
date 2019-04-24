#pragma once

#include <stdexcept>

namespace buzzdb {
class TransactionAbortedException : public std::runtime_error {
 public:
  explicit TransactionAbortedException(const std::string & what_arg);

  explicit TransactionAbortedException(const char * what_arg);

  virtual const char * what() const throw();

 private:
  std::string what_message;
};
}
