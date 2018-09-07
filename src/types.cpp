// TYPES SOURCE

#include "types.h"

namespace engine {

std::string HierarchyTypeToString(const HierarchyType& hierarchy_type){

  switch (hierarchy_type) {
    case HIERARCHY_TYPE_NVM:
      return "NVM";
    case HIERARCHY_TYPE_DRAM_NVM:
      return "DRAM-NVM";
    case HIERARCHY_TYPE_DRAM_DISK:
      return "DRAM-DISK";
    case HIERARCHY_TYPE_NVM_DISK:
      return "NVM-DISK";
    case HIERARCHY_TYPE_DRAM_NVM_DISK:
      return "DRAM-NVM-DISK";
    default:
      return "INVALID";
  }

}

}  // End engine namespace

