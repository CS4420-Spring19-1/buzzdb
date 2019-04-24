#pragma once

#include "page_id.h"
#include "heap_page_id.h"

namespace buzzdb {
/**
 * The RecordId class represents the location of a tuple.
 * - A tuple is contained within a page and is indexed within the page by
 *   its tuple_number.
 */
class RecordId {
 public:
  /**
   * Default constructor.
   * Not available as a RecordId should be explicitely initialized.
   */
  RecordId() = delete;

  /**
   * Constructor.
   * Creates a new RecordId with page id pid and tuple number tuple_number.
   */
  RecordId(PageId & pid, int tuple_number);

  /**
   * Returns the tuple's index in the page.
   */
  int get_tuple_number() const;

  /**
   * Returns the id of the page containing the tuple.
   */
  const PageId & get_page_id() const;

  bool operator==(const RecordId & other);

  bool operator!=(const RecordId & other);

 private:
  PageId & pid;
  int tuple_number;
};
}
