#include "tuple.h"

/**
 * This implementation needs an overhaul.
 */
namespace emerald {
Tuple::Tuple() {
}

Tuple::Tuple(TupleDesc td) : td(td), rid(nullptr) {
  this->fields = new Field * [td.get_number_fields()];
}

Tuple::~Tuple() {
  for (int i = 0; i < td.get_number_fields(); i++) {
    delete fields[i];
  }
  delete fields;
  delete rid;
}

Tuple::Tuple(Tuple & tuple) {
  Field ** new_fields;

  this->td = tuple.get_tuple_desc();
  this->rid = tuple.get_record_id();
  tuple.get_fields(new_fields);
}

TupleDesc::TupleDesc Tuple::get_tuple_desc() const {
  return td;
}

RecordId::RecordId * Tuple::get_record_id() const {
  return rid;
}

void Tuple::set_record_id(RecordId * rid) {
  this->rid = rid;
}

void Tuple::get_fields(Field ** fields) {
  fields = this->fields;
}

Field::Field * Tuple::get_field(int i) const {
  return fields[i];
}

void Tuple::set_field(int i, Field * f) {
  fields[i] = f;
}
}
