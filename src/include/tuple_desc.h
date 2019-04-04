#pragma once

#include <string>
#include "type.h"

namespace emerald {
class TupleDesc {
 public:
  /**
   * Merge two TupleDescs into one with td1.num_fields + td2.num_fields fields.
   * The first fields will come from td1, followed by the fields from td2.
   */
  static TupleDesc combine(TupleDesc td1, TupleDesc td2);

  /**
   * Default constructor of the TupleDesc class.
   */
  TupleDesc();

  /**
   * Constructor of the TupleDesc class.
   * Creates a new TupleDesc with fields of types specified by type_array. The
   * fields will be unnamed.
   */
  TupleDesc(Type type_array[]);

  /**
   * Constructor of the TupleDesc class.
   * Creates a new TupleDesc with fields of types specified by type_array and
   * names specified by field_array.
   */
  TupleDesc(Type type_array[], std::string field_array[]);

  /**
   * Copy constructor of the TupleDesc class.
   */
  TupleDesc(const TupleDesc & other);

  /**
   * Returns the number of fields in the TupleDesc.
   */
  int get_number_fields() const;

  /**
   * Returns the name of the ith field in the TupleDesc.
   * The name can be null.
   */
  std::string get_field_name(int index) const;

  /**
   * Returns the index of the first field that has a matching name in the
   * TupleDesc.
   */
  int get_index(std::string name) const;

  /**
   * Returns the type of the ith field in the TupleDesc.
   */
  Type get_type(int index) const;

  /**
   * Returns the size of the associated tuple in bytes.
   */
  int get_size() const;

  /**
   * Overload of the equality operator.
   */
  bool operator==(TupleDesc other);

 private:
  Type * types;
  std::string * names;
};
}
