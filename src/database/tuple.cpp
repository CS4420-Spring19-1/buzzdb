#include "tuple.h"
#include <stdexcept>
#include "field.h"

namespace buzzdb {
Tuple::Tuple()
    : fields(std::vector<Field *>(0)), td(TupleDesc()), rid(nullptr) {
}

Tuple::Tuple(TupleDesc td) : td(td), rid(nullptr) {
  int number_of_fields = td.get_number_fields();
  this->fields = std::vector<Field *>(number_of_fields);
  // initialize each field to null
  for (int i = 0; i < number_of_fields; i++) {
    this->fields.at(i) = nullptr;
  }
}

Tuple::~Tuple() {
  for (int i = 0; i < td.get_number_fields(); i++) {
    delete fields.at(i);
  }
  delete rid;
}

Tuple::Tuple(const Tuple & original) {
  /**
   * Implementation needs to ensure that a deep copy of the Tuple is made.
   * - There is no use case for an "exact" copy of a Tuple.
   * - A copy can have the same Field values and schema as its original but
   *   should not point to the same Field objects and RecordId as its original.
   * - Every Field * in this->fields cannot point to the same object as a
   *   Field * in other->fields. Failure to enforce this constraint can lead to
   *   dangling pointers if a particular Tuple is copied and then deleted.
   * - The copy of the Tuple cannot have the same RecordId as its original.
   *   Again, failure to enforce this constraint can lead to dangling pointers.
   */
}

const std::vector<Field *> & Tuple::get_fields() const {
  return fields;
}

Field * Tuple::get_field(int index) const {
  if (index < 0) {
    throw std::invalid_argument("Index cannot be negative.");
  }

  unsigned int unsigned_index = index;
  if (unsigned_index >= fields.size()) {
    throw std::out_of_range("Index is out of range.");
  }
  return fields[unsigned_index];
}

const TupleDesc & Tuple::get_tuple_desc() const {
  return td;
}

const RecordId * Tuple::get_record_id() const {
  return rid;
}

void Tuple::set_field(int index, Field * f) {
  if (index < 0) {
    throw std::invalid_argument("Index cannot be negative.");
  }

  unsigned int unsigned_index = index;
  if (unsigned_index >= fields.size()) {
    throw std::out_of_range("Index is out of range.");
  }

  // type check is yet to be implemented.
  if (false) {
    throw std::invalid_argument("Type of *f is incorrect.");
  };
  fields.at(unsigned_index) = f;
}

void Tuple::set_record_id(RecordId * rid) {
  this->rid = rid;
}

bool Tuple::operator==(const Tuple & other) {
  return fields == other.fields
      && td == other.td
      && rid == other.rid;
}

bool Tuple::operator!=(const Tuple & other) {
  return !(*this == other);
}
}
