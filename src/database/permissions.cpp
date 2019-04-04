#include "permissions.h"

namespace emerald {
Permissions::Permissions(int perm_level) {
  this->perm_level = perm_level;
}

Permissions::READ_ONLY = Permissions(1);
Permissions::READ_WRITE = Permissions(0);
}