#include "transaction_aborted_exception.h"

namespace buzzdb {
const char * TransactionAbortedException::what() const throw() {
  return "TransactionAbortedException occurred.";
}
}
