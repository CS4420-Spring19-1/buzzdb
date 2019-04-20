#include "transaction_aborted_exception.h"

namespace buzzdb {
TransactionAbortedException::TransactionAbortedException(
    const std::string & what_arg)
    : std::runtime_error(what_arg), what_message(what_arg) {
}

TransactionAbortedException::TransactionAbortedException(
    const char * what_arg)
    : std::runtime_error(what_arg), what_message(what_arg) {
}

const char * TransactionAbortedException::what() const throw() {
  std::string error_message = "TransactionAbortedException. " + what_message;
  return error_message.c_str();
}
}
