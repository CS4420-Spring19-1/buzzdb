#include "key_vector.h"
#include <map>

namespace emerald{
  KeyVector::KeyVector():size(0){}
  KeyVector::KeyVector(int key):KeyVector(){
    addKey(key);
  }
  void KeyVector::addKey(int key){
    this->keys.push_back(key);
    this->size++;
  }
  bool KeyVector::operator==(const KeyVector& key_vector) const {
    if(key_vector.getKeySize()!=this->size){
      return false;
    }
    std::vector<int> key_1 = key_vector.getKeys();
    auto vector_size = key_vector.size;
    for (auto vector_itr=0; vector_itr < vector_size; vector_itr++) {
      if (key_1[vector_itr]!=this->keys[vector_itr]) {
        return false;
      }
    }
    return true;
  }
  bool KeyVector::operator<(const KeyVector& key_vector) const {
    if(key_vector.getKeySize()!=this->size){
      return false;
    }
    std::vector<int> key_1 = key_vector.getKeys();
    auto vector_size = key_vector.size;
    auto vector_itr=0;
    for (; vector_itr < vector_size; vector_itr++) {
      if (key_1[vector_itr]!=this->keys[vector_itr]) {
        break;
      }
    }
    return key_1[vector_itr] > this->keys[vector_itr];
  }
  std::vector<int> KeyVector::getKeys() const{
    return this->keys;
  }
  int KeyVector::getKeySize() const {
    return this->size;
  }
}
