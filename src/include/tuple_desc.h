#pragma once

#include <string>
#include <vector>
#include <field.h>

namespace buzzdb {
/**
 * The TupleDesc class represents the schema of a tuple.
 * - The values of a TupleDesc object cannot be mutated after creation.
 * - It is not necessary for field names to be distinct.
 * - The type_vector and name_vector of a TupleDesc object are guaranteed to
 *   have the same length after construction. 
 */
class TupleDesc {
 public:
  /**
   * Default constructor.
   * Creates a new TupleDesc with no fields.
   * Should only be used to represent the schema of an empty Tuple.
   */
  TupleDesc();

  /**
   * Constructor.
   * Creates a new TupleDesc with field types specified by type_vector.
   * The fields will be unnamed.
   */
  TupleDesc(std::vector<Field::Type> type_vector);

  /**
   * Constructor.
   * Creates a new TupleDesc with field types specified by type_vector and
   * names specified by name_vector.
   * 
   * Throws:
   * - std::invalid_argument: If type_vector and name_vector have different
   *   lengths.
   */
  TupleDesc(std::vector<Field::Type> type_vector,
            std::vector<std::string> name_vector);

  /**
   * Destructor.
   */
  ~TupleDesc() = default;

  /**
   * Copy constructor.
   */
  TupleDesc(const TupleDesc & original);

  /**
   * Returns the number of fields.
   */
  int get_number_fields() const;

  /**
   * Returns the size of the associated tuple in bytes.
   */
  int get_size() const;

  /**
   * Returns the type of the i-th field, where i is given by index.
   * 
   * Throws:
   * - std::invalid_argument: If index < 0. 
   * - std::out_of_range: If index >= number of fields. 
   */
  const Field::Type & get_field_type(int index) const;

  /**
   * Returns the name of the i-th field, where i is given by index.
   * 
   * Throws:
   * - std::invalid_argument: If index < 0. 
   * - std::out_of_range: If index >= number of fields. 
   */
  const std::string & get_field_name(int index) const;

  /**
   * Returns the index of the first field with a given name.
   * 
   * Throws:
   * - NoSuchElementException: If no field with a matching name is found.
   */
  int get_index_of_named_field(std::string & name) const;

  /**
   * Merge two TupleDescs into one TupleDesc.
   * The first fields will come from td1, followed by the fields from td2.
   */
  static TupleDesc Combine(TupleDesc & td1, TupleDesc & td2);

  bool operator==(const TupleDesc & other);

  bool operator!=(const TupleDesc & other);

 private:
  std::vector<Field::Type> types;
  std::vector<std::string> names;
};
}
