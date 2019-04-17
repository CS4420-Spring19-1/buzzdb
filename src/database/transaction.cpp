#include "transaction.h"

// tests not written
/**
 * Implementation incomplete:
 * - Database class missing
 * - IO exceptions not handled
 */

namespace buzzdb {
Transaction::Transaction() : hasStarted(false) {
  tid = new TransactionId();
}

Transaction::~Transaction() {
  delete tid;
}

TransactionId * Transaction::get_id() {
  return tid;
}

void Transaction::Start() {
  hasStarted = true;
  /* Ported from Transaction.java
  Database.getLogFile().logXActionBegin(tid);
  // handle IO exception if needed
  */
}

void Transaction::Commit() {
  TransactionComplete(false);
}

void Transaction::TransactionComplete(bool abort) {
  if (!hasStarted) {
    return;
  }
  /* Ported from Transaction.java
  // write commit / abort records
  if (abort) {
    Database.getLogFile().logAbort(tid); // does rollback too
  } else {
    // write back all pages that this transaction dirtied
    Database.getBufferPool().flushPages();
    Database.getLogFile().logCommit(tid);
  }

  Database.getBufferPool().transactionComplete(tid, !abort); // release locks
  // handle IO exception if needed

  hasStarted = false;
  */

  // Placeholder code to avoid compiler warning, delete once resolved.
  if (abort) {
  }
}
}
