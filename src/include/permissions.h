#pragma once

namespace emerald {
class Permissions {
 public:
  Permissions(int perm_level);

  const static Permissions READ_ONLY;
  const static Permissions READ_WRITE;
  
 private:
  int perm_level;
};
}