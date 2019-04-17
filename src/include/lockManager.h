#pragma once
#include <set>
#include <vector>
#include "transaction_id.h"

namespace buzzdb {
class LockManager {
public:
  LockManager(int num_pages);
  isHolding(TransactionId* tid, int idx);
  bool isHolding(TransactionId* tid, int idx);
  void Acquire(TransactionId* tid, int idx, Permissions* perm);
  bool Release(TransactionId* tid, int idx);

private:
  std::vector<std::set<TransactionId*>> read_lock_holders;
  std::vector<TransactionId*> write_lock_holders;
  std::vector<int> writers;
  // private final Random rand = new Random();
  int MIN_TIME = 100;
  int MAX_TIME = 1000;

  bool HoldsReadLock(TransactionId* tid, int idx);
  
  bool HoldWriteLock(TransactionId* tid, int idx); 
  
  void ArquireReadLock(TransactionId* tid, int idx);
  
  bool ReleaseReadLock(TransactionId* tid, int idx);
  
  bool HasOtherReader(TransactionId* tid, int idx);
  
  void ArquireWriteLock(TransactionId* tid, int idx);
  
  bool ReleaseWriteLock(TransactionId* tid, int idx);
}
} // emerald