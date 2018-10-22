// TYPES HEADER

#pragma once

#include <string>

namespace emerald {

enum AlgorithmType {
  ALGORITHM_TYPE_INVALID = 0,

  ALGORITHM_TYPE_TUPLE_CENTRIC_INVERTED_INDEX = 1,
  ALGORITHM_TYPE_VALUE_CENTRIC_JOIN_1 = 2,
  ALGORITHM_TYPE_VALUE_CENTRIC_JOIN_2 = 3,

  ALGORITHM_TYPE_MAX = 4   // for checking out of bounds
};

std::string AlgorithmTypeToString(const AlgorithmType& algorithm_type);

}  // End emerald namespace
