#include "tuple_desc.h"

namespace emerald {
TupleDesc::TupleDesc() {
}

TupleDesc::TupleDesc(std::vector<Type> type_array) {
  std::vector<std::string> empty_string = new std::vector<std::string>(0);
  TupleDesc(type_array, empty_string);
}

TupleDesc::TupleDesc(std::vector<Type> type_array, std::vector<std::string> field_array) {
  types = new std::vector<Type>(type_array.size());
  // memcpy ?
  for (size_t i = 0; i < type_array.size(); i++) {
      types.push_back(type_array[i]);
  }
  
  names = new std::vector<std::string>(field_array.size());
  for (size_t i = 0; i < field_array.size(); i++) {
      names.push_back(field_array[i]);
  }
}

TupleDesc::TupleDesc(const TupleDesc & other) {
}

int TupleDesc::get_number_fields() const {
  return types.size();
}

std::string TupleDesc::get_field_name(int index) const {
  if (index < 0 || i >= types.size()) {
    // throw new NoSuchElementException("Index Out of Range."); 
  } else {
    return names[i];
  }
}

std::string TupleDesc::get_field_type(int index) const {
  if (index < 0 || i >= types.size()) {
    // throw new NoSuchElementException("Index Out of Range."); 
  } else {
    return types[i];
  }
}

int TupleDesc::FieldNameToIndex(std::string name) {
  if (name != NULL) {
    for (size_t i = 0; i < name.length(); i++) {
      if (name == names[i]) {
        return i;
      }
    }
  }
  // throw new NoSuchElementException("Unknown Field Name.");
}

int TupleDesc::get_size() const {
  int size = 0;
  for (size_t i = 0; i < types.size(); i++) {
    size += sizeof(types[i]);
  }
  return size;
}

TupleDesc::TupleDesc* TupleDesc::Combine(TupleDesc* td1, TupleDesc* td2) {
  std::vector<Type> types = new std::vector<Type>(td1->types.size() + td2->types.size());
  std::vector<std::string> names = new std::vector<std::string>(td1->names.size() + td2->names.size());
  int idx = 0;

  for (size_t i = 0; i < td1->types.size(); i++) {
    types[idx] = td1->types[i];
    names[idx++] = td1->types[i];
  }

  for (size_t i = 0; i < td2->types.size(); i++) {
    types[idx] = td2->types[i];
    names[idx++] = td2->types[i];
  }

  return new TupleDesc(types, names);
}

bool TupleDesc::operator==(TupleDesc& other) {
  if (!(dynamic_cast<TupleDesc*>(other) != nullptr)) {
    return false;
  } else {
    TupleDesc* o = dynamic_cast<TupleDesc*>(other);

    if (this->get_number_fields() != o->get_number_fields()) {
      return false;
    } else {
      int n = this->get_number_fields();

      for (size_t i = 0; i < n; i++) {
        if (o->get_field_name(i) == nullptr) {
          if (o->get_field_name(i) != nullptr) {
            return false;
          }
        }
        else if (this->get_field_name(i) == o->get_field_name(i)) {
          return false;
        }
        else if (this->get_field_type(i) != o->get_field_type(i)) {
          return false;
        }
      }
      return true;
    }
  }
}
} //emerald
