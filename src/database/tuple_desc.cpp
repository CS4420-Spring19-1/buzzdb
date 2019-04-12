#include <stdexcept>
#include "tuple_desc.h"

namespace emerald {
/**
 * Implementation needs to be tweaked to provide guarantees
 */
TupleDesc::TupleDesc() {
}

TupleDesc::TupleDesc(std::vector<Type> type_vector) {
  std::vector<std::string> empty_string = std::vector<std::string>(0);
  TupleDesc(type_vector, empty_string);
}

TupleDesc::TupleDesc(std::vector<Type> type_vector, std::vector<std::string> field_vector) {
  types = std::vector<Type>(type_vector.size());
  // memcpy ?
  for (size_t i = 0; i < type_vector.size(); i++) {
      types.push_back(type_vector[i]);
  }
  
  names = std::vector<std::string>(field_vector.size());
  for (size_t i = 0; i < field_vector.size(); i++) {
      names.push_back(field_vector[i]);
  }
}

TupleDesc::TupleDesc(const TupleDesc & other) {
  // this might need to be modified if underlying representation is changed
  this->types = other.types;
  this->names = other.names;
}

int TupleDesc::get_number_fields() const {
  return types.size();
}

std::string TupleDesc::get_field_name(int index) const {
  if (index < 0 || index >= types.size()) {
    throw std::out_of_range("Index out of range");
  } else {
    return names[index];
  }
}

Type TupleDesc::get_field_type(int index) const {
  if (index < 0 || index >= types.size()) {
    throw std::out_of_range("Index out of range");
  } else {
    return types[index];
  }
}

int TupleDesc::FieldNameToIndex(std::string name) {
  if (&name == nullptr) {
    // throw new NoSuchElementException("Unknown Field Name.");
  }
  for (size_t i = 0; i < name.length(); i++) {
    if (name == names[i]) {
      return i;
    }
  }
}

int TupleDesc::get_size() const {
  // inefficient implementation?
  int size = 0;
  for (size_t i = 0; i < types.size(); i++) {
    size += sizeof(types[i]);
  }
  return size;
}

TupleDesc::TupleDesc TupleDesc::Combine(TupleDesc * td1, TupleDesc * td2) {
  std::vector<Type> types = std::vector<Type>(td1->types.size() + td2->types.size());
  std::vector<std::string> names = std::vector<std::string>(td1->names.size() + td2->names.size());
  int idx = 0;

  for (size_t i = 0; i < td1->types.size(); i++) {
    types[idx] = td1->types[i];
    names[idx++] = td1->names[i];
  }

  for (size_t i = 0; i < td2->types.size(); i++) {
    types[idx] = td2->types[i];
    names[idx++] = td2->names[i];
  }

  return TupleDesc(types, names);
}

bool TupleDesc::operator==(TupleDesc & other) {
  int n = this->get_number_fields();

  if (other.get_number_fields() != n) {
    return false;
  }

  for (size_t i = 0; i < n; i++) {
    if ((& other.get_field_name(i)) == nullptr) {
      if ((& other.get_field_name(i)) != nullptr) {
        return false;
      }
    } else if (this->get_field_name(i) == other.get_field_name(i)) {
      return false;
    } else if (this->get_field_type(i) != other.get_field_type(i)) {
      return false;
    }
  }

  return true;
}
}
