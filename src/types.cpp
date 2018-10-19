// TYPES SOURCE

#include "types.h"

namespace emerald {

std::string AlgorithmTypeToString(const AlgorithmType& algorithm_type){

  switch (algorithm_type) {
    case ALGORITHM_TYPE_TUPLE_CENTRIC_INVERTED_INDEX:
      return "TUPLE_CENTRIC_INVERTED_INDEX";
    case ALGORITHM_TYPE_VALUE_CENTRIC_JOIN_1:
      return "VALUE_CENTRIC_JOIN_1";
    case ALGORITHM_TYPE_VALUE_CENTRIC_JOIN_2:
      return "VALUE_CENTRIC_JOIN_2";
    default:
      return "INVALID ALGORITHM";
  }

}

}  // End engine emerald

