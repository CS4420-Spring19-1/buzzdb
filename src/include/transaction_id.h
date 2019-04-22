#pragma once

#include <atomic>

namespace buzzdb {
/**
 * The TransactionId class encapsulates the id of a particular transaction.
 * - Each assigned id is unique.
 */
class TransactionId {
 public:
  /**
   * Default constructor.
   * Creates a new TransactionId, assigning the next available transaction id.
   */
  TransactionId();

  /**
   * Destructor.
   */
  ~TransactionId() = default;

  /**
   * Returns the transaction id value.
   */
  long get_id_value() const;

  bool operator==(const TransactionId & other);

  bool operator!=(const TransactionId & other);

  bool operator<(const TransactionId & other);

  bool operator>(const TransactionId & other);

  bool operator<=(const TransactionId & other);

  bool operator>=(const TransactionId & other);

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
