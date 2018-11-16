#include "key_vector.h"
#include <map>

namespace emerald{
  KeyVector::KeyVector():size(0){}
  void KeyVector::addKey(int key){
    this->keys.push_back(key);
    this->size++;
  }
  bool KeyVector::operator<(const KeyVector& key_vector) const {
    auto vector_itr =0;
    std::vector<int> keys = key_vector.getKeys();
    while (vector_itr < key_vector.getKeySize() && keys[vector_itr] == this->keys[vector_itr]) {
      vector_itr++;
    }
    if(vector_itr==key_vector.getKeySize()){
      return false;
    }
    return keys[vector_itr] < this->keys[vector_itr];
  }
  std::vector<int> KeyVector::getKeys() const{
    return this->keys;
  }
  int KeyVector::getKeySize() const {
    return this->size;
  }
}
