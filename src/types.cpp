// TYPES SOURCE

#include "types.h"

namespace emerald {

std::string AlgorithmTypeToString(const AlgorithmType& algorithm_type){

  switch (algorithm_type) {
    case ALGORITHM_TYPE_TUPLE_CENTRIC_INVERTED_INDEX:
      return "TUPLE_CENTRIC_INVERTED_INDEX";
    case ALGORITHM_TYPE_VALUE_CENTRIC_SINGLE_INDEX:
      return "VALUE_CENTRIC_SINGLE_INDEX";
    case ALGORITHM_TYPE_VALUE_CENTRIC_TWO_INDEXES:
      return "VALUE_CENTRIC_TWO_INDEXES";
    case ALGORITHM_TYPE_VALUE_CENTRIC_TWO_INDEXES_SORT_MERGE:
      return "VALUE_CENTRIC_TWO_INDEXES_SORT_MERGE";
    default:
      return "INVALID ALGORITHM";
  }

}

}  // End engine emerald
