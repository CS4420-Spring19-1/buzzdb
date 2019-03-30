#include "heap_file_iterator.h"

namespace emerald {
HeapFileIterator::HeapFileIterator(TransactionId tid, HeapFile f) {
  this->interator = NULL;
  this->pageIndex = 0;
  this->tid = tid;
  this->file = file;
}

void HeapFileIterator::open() {
  pageIndex = 0;
  PageId pageId = new HeapPageId(file.getId(), pageIndex);
  Page page = database.getBufferPool().getPage(tid, pageId, Permissions.READ_ONLY);
  HeapPage heapPage = (HeapPage)page;
  iterator = heapPage.iterator();
}

bool HeapFileIterator::hasNext() {
  if (iterator == NULL) {
    return false;
  }
  if (iterator.hasNext()) {
    return true;
  } else {
    if (pageIndex >= file.numPages() - 1) {
      return false;
    } else {
      PageId pageId = new HeapPageId(file.getId(), pageIndex + 1);
      Page page = Database.getBufferPool().getPage(tid, pageId, Permissions.READ_ONLY);
      HeapPage heapPage = (HeapPage)page;
      return heapPage.iterator().hasNext();
    }
  }
}

tuple HeapFileIterator::next() {
  if (iterator == null) {
    throw new NoSuchElementException();
  }
  if (iterator.hasNext()) {
    return iterator.next();
  } else {
    PageId pageId = new HeapPageId(file.getId(), pageIndex + 1);
    Page page = database.getBufferPool().getPage(tid, pageId, Permissions.READ_ONLY);
    HeapPage heapPage = (HeapPage)page;

    if (page != null)
      if (heapPage.iterator().hasNext()) {
        pageIndex++;
        iterator = heapPage.iterator();
        return iterator.next();
      }
    throw new NoSuchElementException();
  }
}

void HeapFileIterator::restart() {
  close();
  open();
}

void HeapFileIterator::close() {
  iterator = null;
  pageIndex = 0;
}
}
