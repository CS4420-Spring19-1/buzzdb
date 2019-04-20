#pragma once

#include "page_id.h"

namespace buzzdb {
/**
 * The HeapPageId class represents the identifier for a HeapPage.
 * - This class implements the PageId interface.
 */
class HeapPageId : public PageId {
 public:
  HeapPageId();


  /**
   * Constructor.
   * Creates a new HeapPageId with the given table_id and page_number.
   */
  HeapPageId(int table_id, int page_number);

  /**
   * Destructor.
   */
  ~HeapPageId() override = default;

  /**
   * Copy constructor.
   */
  HeapPageId(const HeapPageId & original);

  /**
   * Returns the id of the table the page is in.
   */
  int get_table_id() const override;

  /**
   * Returns the index of the page in its table.
   */
  int get_page_number() const override;

  /**
   * Returns a representation of the HeapPageId as a 2 element integer array.
   * The first element is the table id and the second element is the page id.
   * Used for logging.
   */
  std::array<int, 2> Serialize() override;


  bool operator==(HeapPageId other);

 private:
  int table_id;
  int page_number;
};
}