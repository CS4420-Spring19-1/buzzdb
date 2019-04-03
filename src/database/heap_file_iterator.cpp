#include "heap_file_iterator.h"

namespace emerald {
heap_file_iterator::heap_file_iterator(transaction_id tid, heap_file f) {
  this->iterator = NULL;
  this->page_index = 0;
  this->tid = tid;
  this->file = file;
}

void heap_file_iterator::open() {
  page_index = 0;
  page_Id page_id = new heap_page_id(file.getId(), page_index);
  page page = database.getBufferPool().getPage(tid, page_id, Permissions.READ_ONLY);
  Heap_page heap_page = (heap_page)page;
  iterator = heap_page.iterator();
}

bool heap_file_iterator::hasNext() {
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
      page_id page_id = new HeapPageId(file.getId(), page_index + 1);
      page page = database.getBufferPool().getPage(tid, page_id, Permissions.READ_ONLY);
      heap_page heap_page = (heap_page)page;
      return heapPage.iterator().hasNext();
    }
  }
}

tuple heap_file_iterator::next() {
  if (iterator == null) {
    throw new NoSuchElementException();
  }
  if (iterator.hasNext()) {
    return iterator.next();
  } 
  else {
    page_id page_id = new heap_page_id(file.getId(), page_index + 1);
    page page = database.getBufferPool().getPage(tid, page_id, Permissions.READ_ONLY);
    heap_page heap_page = (heap_page)page;

    if (page != null)
      if (heap_page.iterator().hasNext()) {
        page_index++;
        iterator = heap_page.iterator();
        return iterator.next();
      }
    throw new NoSuchElementException();
  }
}

void heap_file_iterator::restart() {
  close();
  open();
}

void heap_file_iterator::close() {
  iterator = null;
  page_index = 0;
}
}
