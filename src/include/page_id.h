#pragma once

namespace buzzdb {
/**
 * This is an interface to a page identifier for a specific page in a specific
 * table.
 * 
 * This class must have a constructor that accepts n integer parameters, where
 * n is the number of integers returned in the array from serialize.
 */
class PageId {
 public:
  /*
   * Necessary for an interface class to ensure correct polymorphic deletion.
   */
  virtual ~PageId();

  /**
   * Returns the table id of the table the page is in
   */
  virtual int get_table_id() = 0;

  /**
   * Returns the page number
   */
  virtual int get_page_number() = 0;

  /**
   * Returns a representation of the PageId object as a collection of integers.
   * Used for logging.
   * 
   * rep is the return array. As such, it should be a 2 element int array.
   */
  virtual void Serialize(int rep[]) = 0;
};
}
