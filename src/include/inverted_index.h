#pragma once

#include <map>
#include <vector>
#include "key_vector.h"

namespace emerald{
  class InvertedIndex{
    private:
      std::map<KeyVector, std::vector<std::vector<int>>> inverted_index;
    //  std::map<int, std::vector<std::vector<int>>> inverted_index;
    public:
      InvertedIndex(int * column, int columns_size);
      InvertedIndex();
      std::map<KeyVector, std::vector<std::vector<int>>> getInvertedIndex();
      void print();
      void insert(KeyVector key, std::vector<std::vector<int>> offsets);
      long size();
      long matches();
  };
}
