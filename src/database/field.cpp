#include "field.h"
#include <stdexcept>

namespace buzzdb {
Field::~Field() = default;

int Field::get_length(Type type) {
  switch (type) {
    case INTEGER:
      return integer_length_in_bytes;
    case STRING:
      return string_length_in_bytes + 4;
    default:
      throw std::invalid_argument("Field type is not defined.");
  }
}
}
