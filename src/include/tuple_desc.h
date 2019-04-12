#pragma once

#include <string>
#include <vector>
#include "type.h"

namespace emerald {
class TupleDesc {
 public:
  /**
   * Default constructor of the TupleDesc class.
   */
  TupleDesc();

  /**
   * Constructor of the TupleDesc class.
   * Creates a new TupleDesc with fields of types specified by type_vector. The
   * fields will be unnamed.
   */
  TupleDesc(std::vector<Type> type_vector);

  /**
   * Constructor of the TupleDesc class.
   * Creates a new TupleDesc with fields of types specified by type_vector and
   * names specified by field_vector.
   */
  TupleDesc(std::vector<Type> type_vector, std::vector<std::string> field_vector);

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

  Type TupleDesc::get_field_type(int index) const;

  /**
   * Find the index of the field with a given name.
   * 
   * @param name
   *            name of the field.
   * @return the index of the field that is first to have the given name.
   * @throws NoSuchElementException
   *             if no field with a matching name is found.
   */
  int TupleDesc::FieldNameToIndex(std::string name);

  /**
   * Returns the size of the associated tuple in bytes.
   */
  int get_size() const;

  /**
   * Merge two TupleDescs into one with td1.num_fields + td2.num_fields fields.
   * The first fields will come from td1, followed by the fields from td2.
   */
  static TupleDesc Combine(TupleDesc * td1, TupleDesc * td2);

  /**
   * Overload of the equality operator.
   */
  bool operator==(TupleDesc & other);

 private:
  std::vector<Type> types;
  std::vector<std::string> names;
};
}
