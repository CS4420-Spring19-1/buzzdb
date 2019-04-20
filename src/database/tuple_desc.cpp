#include "tuple_desc.h"
#include <stdexcept>
#include "no_such_element_exception.h"

namespace buzzdb {
TupleDesc::TupleDesc() {
  types = std::vector<Field::Type>(0);
  names = std::vector<std::string>(0);
}

TupleDesc::TupleDesc(std::vector<Field::Type> type_vector) {
  int vector_size = type_vector.size();
  TupleDesc(type_vector, std::vector<std::string>(vector_size));
}

TupleDesc::TupleDesc(std::vector<Field::Type> type_vector,
                     std::vector<std::string> name_vector) {
  if (type_vector.size() != name_vector.size()) {
    throw std::invalid_argument(
        "Pre-condition violation: Type vector and name vector differ in size");
  }
  types = type_vector;
  names = name_vector; 
}

TupleDesc::TupleDesc(const TupleDesc & original) {
  this->types = original.types;
  this->names = original.names;
}

int TupleDesc::get_number_fields() const {
  return types.size();
}

int TupleDesc::get_size() const {
  int size = 0;
  for (size_t i = 0; i < types.size(); i++) {
    Field::Type type = types[i];
    size += Field::get_length(type);
  }
  return size;
}

const Field::Type & TupleDesc::get_field_type(int i) const {
  if (i < 0) {
    throw std::domain_error("Index cannot be negative.");
  }

  unsigned int unsigned_index = i;
  if (unsigned_index >= types.size()) {
    throw std::out_of_range("Index is out of range.");
  }
  return types[unsigned_index];
}

const std::string & TupleDesc::get_field_name(int i) const {
  if (i < 0) {
    throw std::domain_error("Index cannot be negative.");
  }

  unsigned int unsigned_index = i;
  if (unsigned_index >= names.size()) {
    throw std::out_of_range("Index is out of range.");
  }
  return names[unsigned_index];
}

int TupleDesc::get_index_of_named_field(std::string & name) const {
  for (size_t i = 0; i < name.length(); i++) {
    if (name == names[i]) {
      return i;
    }
  }
  throw NoSuchElementException("Field name not found.");
}

TupleDesc TupleDesc::Combine(TupleDesc & td1, TupleDesc & td2) {
  size_t td1_size = td1.get_size();
  size_t td2_size = td2.get_size();
  std::vector<Field::Type> combined_types;
  std::vector<std::string> combined_names;

  // firstly populating combined vectors with the elements from td1
  for (size_t i = 0; i < td1_size; i++) {
    combined_types.push_back(td1.types.at(i));
    combined_names.push_back(td1.names.at(i));
  }

  // then populating combined vectors with the elements from td2
  for (size_t i = td1_size; i < td2_size; i++) {
    combined_types.push_back(td2.types.at(i));
    combined_names.push_back(td2.names.at(i));
  }

  return TupleDesc(combined_types, combined_names);
}

bool TupleDesc::operator==(const TupleDesc & other) {
  return types == other.types && names == other.names;
}

bool TupleDesc::operator!=(const TupleDesc & other) {
  return !(*this == other);
}
}
