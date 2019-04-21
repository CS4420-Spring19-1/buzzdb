#include "type.h"

namespace buzzdb {
int Type::get_length() {
  return 0; // not implemented
}

bool operator==(const Type & first, const Type & second) {
  return false;
}

bool Type::operator!=(const Type & other) {
  return ! (*this == other);
}
}
