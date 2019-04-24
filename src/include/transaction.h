#pragma once

#include <exception>
#include "transaction_id.h"

namespace buzzdb {
/**
 * The Transaction class represents a transaction in a DBMS.
 */
class Transaction {
 public:
  /**
   * Default constructor.
   */
  Transaction();

  /**
   * Destructor.
   */
  ~Transaction() = default;

  /**
   * Returns the TransactionId.
   */
  const TransactionId & get_id() const;

  /**
   * Starts the transaction.
   */
  void Start();

  /**
   * Completes the transaction by commiting all changes made.
   */
  void Commit();

 private:
  TransactionId tid;
  bool hasStarted;

  /**
   * Handles the details of Commit and Abort (to be implemented later)
   */
  void TransactionComplete(bool abort);
};
}
