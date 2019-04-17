#pragma once

#include "page_id.h"
#include "heap_page_id.h"

namespace buzzdb {
/**
 * This class is a reference to a specific tuple on a specific page
 *  of a specific table.
 */
class RecordId {
 public:
  /**
   * Constructor of the RecordId class
   */
  RecordId(HeapPageId * pid, int tuple_number);

  /**
   * Returns the tuple number
   */
  int get_tuple_number() const;

  /**
   * Returns the page id that the tuple is on
   */
  HeapPageId* get_page_id() const;

  /**
   * Overload of the equality operator
   */
  bool operator==(RecordId other);

  bool Equal(RecordId* other);
 private:
  HeapPageId * pid;
  int tuple_number;
};
}
