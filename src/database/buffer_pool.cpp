#include "buffer_pool.h"

namespace emerald {
BufferPool::BufferPool(int num_pages) {
MaxSize = num_pages;
}

int BufferPool::get_page_size() const {
  return PAGE_SIZE;
}

Page * BufferPool::GetPage(TransactionId * tid, PageId * pid, Permissions * perm) {
  return nullptr;
}

void BufferPool::ReleasePage(TransactionId * tid, PageId * pid) {
}

void BufferPool::TransactionComplete(TransactionId * tid) {
}

bool BufferPool::HoldsLock(TransactionId * tid, PageId * p) {
    return false;
}

void BufferPool::TransactionComplete(TransactionId * tid, bool commit) {
}

void BufferPool::InsertTuple(TransactionId * tid, int tableId, Tuple * t) {
}

void BufferPool::DeleteTuple(TransactionId * tid, Tuple * t) {
}

void BufferPool::FlushAllPages() {
}

void BufferPool::DiscardPage(PageId * pid) {
}

void BufferPool::FlushPage(PageId * pid) {
}

void BufferPool::FlushPages(TransactionId * tid) {
}

void BufferPool::EvictPage() {
}
}
