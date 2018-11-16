#pragma once
#include <map>
#include <vector>

namespace emerald{
  class KeyVector{
    private:
      std::vector<int> keys;
      int size;
    public:
      KeyVector();
      KeyVector(int key);
      void addKey(int key);
      bool operator==(const KeyVector& key_vector) const;
      bool operator<(const KeyVector& key_vector) const;
      std::vector<int> getKeys() const;
      int getKeySize() const;
  };
}
