#pragma once

#include "page_id.h"

namespace emerald {
/**
 * This class is a reference to a specific tuple on a specific page
 *  of a specific table.
 */
class RecordId {
 public:
  /**
   * Constructor of the RecordId class
   */
  RecordId(PageId * pid, int tuple_number);

  /**
   * Returns the tuple number
   */
  int get_tuple_number() const;

  /**
   * Returns the page id that the tuple is on
   */
  PageId & get_page_id() const;

  /**
   * Overload of the equality operator
   */
  bool operator==(RecordId other);

 private:
  PageId * pid;
  int tuple_number;
};
}
