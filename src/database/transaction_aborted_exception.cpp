#include "transaction_aborted_exception.h"

namespace emerald {
const char * TransactionAbortedException::what() const throw() {
  return "TransactionAbortedException occurred.";
}
}
