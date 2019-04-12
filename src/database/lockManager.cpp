#include "lockManager.h"

namespace emerald {
LockManager::LockManager(int num_pages) {
  // mutexes = new Object[num_pages];
  read_lock_holders = new std::vector<std::set<TransactionId*>>(num_pages);
  write_lock_holders = new std::vector<TransactionId*>(num_pages);
  for (size_t i = 0; i < num_pages; i++) {
    // mutexes = new Object();
    read_lock_holders.push_back(new std::set<TransactionId*>());
    write_lock_holders.push_back(nullptr);
  }
  writers = new std::vector<int>(num_pages);
}

LockManager::HoldsReadLock(TransactionId* tid, int idx) {
  return read_lock_holders[idx].contains(tid);
}

LockManager::HoldsWriteLock(TransactionId* tid, int idx) {
  return tid == write_lock_holders[idx];
}

bool LockManager::isHolding(TransactionId* tid, int idx) {
  return HoldsWriteLock(tid, idx) || HoldsReadLock(tid, idx);
}

void LockManager::ArquireReadLock(TransactionId* tid, int idx) {

}

bool LockManager::ReleaseReadLock(TransactionId* tid, int idx) {

}

bool LockManager::HasOtherReader(TransactionId* tid, int idx) {

}

void LockManager::ArquireWriteLock(TransactionId* tid, int idx) {

}

void LockManager::ReleaseWriteLock(TransactionId* tid, int idx) {

}

void LockManager::Acquire(TransactionId* tid, int idx, Permissions* perm) {

}

bool LockManager::Release(TransactionId* tid, int idx) {
  return ReleaseWriteLock(tid, idx) || ReleaseReadLock(tid, idx);
}

}