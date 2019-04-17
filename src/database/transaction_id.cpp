#include "transaction_id.h"

// tests not written

namespace buzzdb {
/**
 * Initialization of private static member in TransactionId class
 */ 
// std::atomic_long TransactionId::counter = 1;
int TransactionId::counter = 1;

TransactionId::TransactionId() {
  // id_value = counter.fetch_add(1);
  id_value = counter++;
}

TransactionId::TransactionId(long id) {
  this->id_value = id;
}

long TransactionId::get_id_value() {
  return id_value;
}

bool TransactionId::operator==(TransactionId & other) {
  return id_value == other.id_value; 
}
}
