#include "transaction.h"
#include "database.h"

namespace buzzdb {
Transaction::Transaction() : tid(TransactionId()), hasStarted(false) {
}

const TransactionId & Transaction::get_id() const {
  return tid;
}

void Transaction::Start() {
  hasStarted = true;
  Database::get_log_file()->LogXActionBegin(tid);
  // todo: ensure IOExceptions are handled
}

void Transaction::Commit() {
  TransactionComplete(false);
}

void Transaction::TransactionComplete(bool abort) {
  if (!hasStarted) {
    return;
  }

  // todo: write commit / abort records
  if (abort) {
    Database::get_log_file()->LogAbort(tid);  // does rollback too
  } else {
    Database::get_buffer_pool()->FlushPages(&tid);
    Database::get_log_file()->LogCommit(tid);
  }

  Database::get_buffer_pool()->TransactionComplete(&tid, !abort);
  // release locks
  // todo: ensure IOExceptions are handled

  /**
   * Setting this here means we could possibly write multiple abort records.
   * Is that ok?
   */
  hasStarted = false;
}
}
