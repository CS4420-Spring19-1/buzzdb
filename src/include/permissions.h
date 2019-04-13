#pragma once

namespace emerald {
class Permissions {
 public:
  Permissions(int perm_level);

  const static int READ_ONLY = 1;
  const static int READ_WRITE = 0;
  
 private:
  int perm_level;
};
}