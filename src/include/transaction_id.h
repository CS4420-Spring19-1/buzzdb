#pragma once

#include <atomic>

namespace emerald {
class TransactionId {
 public:
  /**
   * No argument constructor for the TransactionId class 
   */
  TransactionId();

  TransactionId(long id);

  /**
   * Returns the transaction id value
   */
  long get_id_value();

  /**
   * Overload of the equality operator
   */
  bool operator==(TransactionId & other);


 private:
  /**
   * Internal counter of transaction ids.
   * Used to ensure that ids are unique.
   */
  static std::atomic_long counter;

  /**
   * Id of a TransactionId object
   */
  long id_value;
};
}
