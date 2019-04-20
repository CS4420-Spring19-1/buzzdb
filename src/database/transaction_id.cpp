#include "transaction_id.h"

namespace buzzdb {
std::atomic_long TransactionId::counter = {1};

TransactionId::TransactionId() : id_value(counter.fetch_add(1)) {
}

long TransactionId::get_id_value() const {
  return id_value;
}

bool TransactionId::operator==(const TransactionId & other) {
  return id_value == other.id_value; 
}

bool TransactionId::operator!=(const TransactionId & other) {
  return id_value != other.id_value; 
}

bool TransactionId::operator<(const TransactionId & other) {
  return id_value > other.id_value; 
}

bool TransactionId::operator>(const TransactionId & other) {
  return id_value > other.id_value; 
}

bool TransactionId::operator<=(const TransactionId & other) {
  return id_value <= other.id_value; 
}

bool TransactionId::operator>=(const TransactionId & other) {
  return id_value >= other.id_value; 
}
}
