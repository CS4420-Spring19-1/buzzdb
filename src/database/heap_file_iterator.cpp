#include "heap_file_iterator.h"
#include "database.h"

namespace emerald {
HeapFileIterator::HeapFileIterator(TransactionId tid, HeapFile f) {
  this->iterator = NULL;
  this->page_index = 0;
  this->tid = tid;
  this->file = file;
}

void HeapFileIterator::Open() {
  page_index = 0;
  PageId page_id = new heap_page_id(file.getId(), page_index);
  Page page = Database.getBufferPool().getPage(tid, page_id, Permissions.READ_ONLY);
  HeapPage heap_page = (heap_page)page;
  iterator = HeapPage.iterator();
}

bool HeapFileIterator::HasNext() {
  if (iterator == NULL) {
    return false;
  }
  if (iterator.hasNext()) {
    return true;
  } 
  else {
    if (page_index >= file.num_pages() - 1) {
      return false;
    } 
    else {
      PageId page_id = new HeapPageId(file.getId(), page_index + 1);
      Page page = Database.getBufferPool().getPage(tid, page_id, Permissions.READ_ONLY);
      HeapPage heap_page = (HeapPage) page;
      return heap_page.Iterator().HasNext();
    }
  }
}

Tuple HeapFileIterator::Next() {
  if (iterator == null) {
    throw new NoSuchElementException();
  }
  if (iterator.hasNext()) {
    return iterator.next();
  } 
  else {
    PageId page_id = new HeapPageId(file.getId(), page_index + 1);
    Page page = database.getBufferPool().getPage(tid, page_id, Permissions.READ_ONLY);
    HeapPage heap_page = (HeapPage) page;

    if (page != null)
      if (heap_page.Iterator().HasNext()) {
        page_index++;
        iterator = heap_page.Iterator();
        return iterator.Next();
      }
    throw new NoSuchElementException();
  }
}

void HeapFileIterator::Restart() {
  Close();
  Open();
}

void HeapFileIterator::Close() {
  iterator = null;
  page_index = 0;
}
}
