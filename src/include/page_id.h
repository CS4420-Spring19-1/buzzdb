#pragma once

#include <array>

namespace buzzdb {
/**
 * The PageId interface class is an interface for page identifiers.
 * - Each Page belongs to a table and is indexed by its page number.
 * - A Page can be uniquely identified by the combination of its table id
 *   and page number.
 * - This class must have a constructor that accepts 2 integer parameters.
 */
class PageId {
 public:
  /**
   * Destructor.
   * It is necessary for an interface class to have a virtual destructor to
   * ensure correct polymorphic deletion.
   */
  virtual ~PageId() = 0;

  /**
   * Returns the id of the table the page is in.
   */
  virtual int get_table_id() const = 0;

  /**
   * Returns the index of the page in its table.
   */
  virtual int get_page_number() const = 0;

  /**
   * Returns a representation of the PageId as a 2 element integer array.
   * The first element is the table id and the second element is the page id.
   * Used for logging.
   */
  virtual std::array<int, 2> Serialize() = 0;

  virtual bool operator==(const PageId & other) = 0;

  virtual bool operator!=(const PageId & other) = 0;
};
}
