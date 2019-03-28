#pragma once

#include <exception>
#include "transaction_id.h"

namespace emerald {
class Transaction {
 public:
  /**
   * No argument constructor for the Transaction class
   */
  Transaction();

  /**
   * Destructor for the Transaction class
   */
  ~Transaction();

  /**
   * Returns the TransactionId object
   */
  TransactionId & get_id();

  /**
   * Starts the transaction
   */
  void Start();

  /**
   * Completes the transaction by commiting all changes made
   */
  void Commit();

 private:
  TransactionId * tid;
  bool hasStarted;

  /**
   * Handles the details of Commit and Abort (to be implemented later)
   */
  void TransactionComplete(bool abort);
};
}
