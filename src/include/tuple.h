#pragma once

#include "record_id.h"
#include "tuple_desc.h"

namespace emerald {
class Field;
/**
 * This class maintains information about the contents of a tuple.
 * Tuples have a specified schema specified by a TupleDesc object and contain
 * Field objects with the respective data.
 */
class Tuple {

 public:
  /**
   * Default constructor of the Tuple class
   */
  Tuple();

  /**
   * Constructor of the Tuple class
   */
  Tuple(TupleDesc td);

  /**
   * Destructor of the Tuple class
   */
  ~Tuple();

  /**
   * Copy constructor of the Tuple class
   */
  Tuple(Tuple & tuple);

  /**
   * Returns the schema representation of the Tuple.
   */
  TupleDesc get_tuple_desc() const;

  /**
   * Returns the disk location representation of the Tuple.
   */
  RecordId * get_record_id() const;
  
  /**
   * Sets the disk location information for the Tuple.
   */
  void set_record_id(RecordId * rid);

  /**
   * Returns the internal representation of the Tuple's contents.
   */
  void get_fields(Field ** fields);

  /**
   * Returns the value of the ith field.
   * Returns null if the ith field has not been set.
   */
  Field * get_field(int i) const;

  /**
   * Changes the value of the ith field of the Tuple to f.
   */
  void set_field(int i, Field * f);

 private:
  /**
   * A TupleDesc that represents the tuple's schema.
   */
  TupleDesc td;

  /**
   * A pointer to a Field array that represents the tuple's contents.
   */
  Field ** fields;

  /**
   * Representation of the Tuple's location on disk.
   */
  RecordId * rid;
};
}
