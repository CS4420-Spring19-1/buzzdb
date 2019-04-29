#pragma once

#include <iostream>
#include <sstream>
#include "heap_page_id.h"
#include "page.h"
#include "transaction_id.h"
#include "tuple.h"

namespace buzzdb {
/**
 * The HeapPage class represents a page in a table implemented as a HeapFile.
 * - This class implements the Page interface.
 */
class HeapPage : public Page {
 public:
  /**
   * Default constructor.
   */
  HeapPage() = delete;

  /**
   * Destructor
   */
  ~HeapPage();

  /**
   * Constructor.
   * - data is a representation of a page's data and will be parsed by the
   *   constructor to build the new HeapPage.
   */
  HeapPage(HeapPageId & id, unsigned char data[]);

  /**
   * Returns the id of the page.
   */
  const PageId & get_id() const override;

  /**
   * Returns the transaction id of the last transaction that dirtied the page.
   * Returns null if the page is not dirty.
   */
  const TransactionId * get_id_of_last_dirty_transaction() const override;

  /**
   * Sets the dirty state of the page as dirtied by a particular transaction.
   */
  void MarkDirty(bool dirty, TransactionId * tid) override;

  /**
   * Returns a representation of the Page before any modifications were made to
   * it.
   * 
   * Used by recovery.
   */
  Page * GetBeforeImage() override;

  /**
   * A transaction that wrote this Page just committed it. Copy current content
   * to the before image.
   */
  void SetBeforeImage() override;

  /**
   * Returns the number of tuples in the heap page.
   */
  int get_number_of_tuples();

  /**
   * Returns the size of the heap page's header.
   */
  int get_header_size();

  /**
   * Generates an unsigned char array representing the heap page's contents.
   * 
   * Used to serialize the page to disk.
   * When the array created is parsed into the HeapPage constructor, a new
   * heap page with identical contents should be created.
   */
  void CreatePageDataRepresentation(unsigned char * rep);

  /**
   * Generated an unsigned char array representing an empty heap page's
   * contents.
   */
  static void CreateEmptyPageDataRepresentation(unsigned char * rep);

  /**
   * Deletes the specified tuple from the heap page.
   * 
   * The tuple's record id will be updated accordingly.
   * 
   * Throws:
   * - DbException: If the tuple is not on the heap page,
   *   or if the tuple's slot is already empty.
   */
  void DeleteTuple(Tuple * t);

  /**
   * Adds the specified tuple to the heap page.
   * 
   * The tuple's record id will be updated accordingly.
   * 
   * Throws:
   * - DbException: If the tuple's schema does not match the table's scheme,
   *   or if the tuple already resides on a page,
   *   or if the heap page has no empty slots.
   */
  void InsertTuple(Tuple * t);

  /**
   * Returns the number of empty slots on the heap page.
   */
  int GetNumEmptySlots();

  /**
   * Returns true if the slot given by the index is filled,
   * and false otherwise.
   */
  bool IsSlotUsed(int index);

  /**
   * Fills or clears a slot on the heap page.
   */
  void SetSlot(int index, bool updated_status_of_slot);

  /* Not implemented
  Iterator<tuple> iterator();
  */

 private:
  HeapPageId pid;
  TupleDesc table_schema;
  std::vector<Tuple *> tuples;
  unsigned char * header;
  unsigned char * old_data;
  TransactionId * id_of_transaction_that_dirtied_page;
  int number_of_slots;

  /**
   * If the slot given by slot_index is set to be used, the next tuple is
   * parsed from the given byte stream and returned. Otherwise, the internal
   * stream pointer is moved forward to the next tuple and a nullptr is
   * returned.
   * 
   * Throws:
   * - NoSuchElementException: If there is an error while parsing the tuple.
   */
  Tuple * ParseNextTuple(std::stringstream * byte_stream_pointer,
                          int slot_index);

  Field * ParseIntoField(std::stringstream * byte_stream_pointer,
                         Field::Type field_type);
};
}
