// TYPES HEADER

#pragma once

#include <string>

namespace emerald {

enum HierarchyType {
  HIERARCHY_TYPE_INVALID = 0,

  HIERARCHY_TYPE_NVM = 1,
  HIERARCHY_TYPE_DRAM_NVM = 2,
  HIERARCHY_TYPE_DRAM_DISK = 3,
  HIERARCHY_TYPE_NVM_DISK = 4,
  HIERARCHY_TYPE_DRAM_NVM_DISK = 5,

  HIERARCHY_TYPE_MAX = 5
};

std::string HierarchyTypeToString(const HierarchyType& hierarchy_type);

}  // End emerald namespace
