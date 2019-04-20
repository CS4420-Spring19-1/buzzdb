#pragma once

#include "record_id.h"
#include "tuple_desc.h"

namespace buzzdb {
/**
 * The Tuple class represents a tuple in a page.
 * - The schema of a Tuple is specified by td.
 * - The disk location of a Tuple is specified by rid.
 */
class Tuple {
 public:
  /**
   * Default constructor.
   * Creates a new empty Tuple that does not contain any fields.
   */
  Tuple();

  /**
   * Constructor.
   * Creates a new Tuple based on the schema given by td.
   */
  Tuple(TupleDesc td);

  /**
   * Destructor.
   */
  ~Tuple();

  /**
   * Copy constructor.
   */
  Tuple(const Tuple & original);

  /**
   * Returns the internal representation of the Tuple's contents.
   */
  const std::vector<Field *> & get_fields() const;

  /**
   * Returns the value of the i-th field.
   * If the i-th field has not been set, returns a nullptr.
   * 
   * Throws:
   * - std::domain_error: If i < 0. 
   * - std::out_of_range: If i >= number of fields. 
   */
  Field * get_field(int i) const;

  /**
   * Returns the TupleDesc.
   * A TupleDesc represents the schema of the Tuple.
   */
  const TupleDesc & get_tuple_desc() const;

  /**
   * Returns the disk location representation of the Tuple.
   */
  RecordId * get_record_id() const;

  /**
   * Changes the value of the i-th field of the Tuple to f.
   * 
   * Pre-condition:
   * - f should not be pointing to a Field object already pointed to by
   *   another Tuple. Failure to ensure this constraint will lead to
   *   undefined behaviour.
   * Throws:
   * - std::domain_error: If i < 0. 
   * - std::out_of_range: If i >= number of fields. 
   * - std::invalid_argument: If f is of incorrect Type, as specified by the
   *   TupleDesc. 
   */
  void set_field(int i, Field * f);
  
  /**
   * Sets the disk location information for the Tuple.
   */
  void set_record_id(RecordId * rid);

  bool operator==(const Tuple & other);

  bool operator!=(const Tuple & other);

 private:
  /**
   * The internal representation of the Tuple's contents.
   */
  std::vector<Field *> fields;

  /**
   * The representation of the Tuple's schema.
   */
  TupleDesc td;

  /**
   * The representation of the Tuple's location on disk.
   */
  RecordId * rid;
};
}
