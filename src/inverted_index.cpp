#include "inverted_index.h"
#include "key_vector.h"
#include <map>
#include <iostream>

namespace emerald {
  InvertedIndex::InvertedIndex(int * column, int column_size){
    for(int column_itr = 0; column_itr < column_size; column_itr++){
      std::vector<int> offset;
      auto value = column[column_itr];
      offset.push_back(column_itr);
  		this->inverted_index[value].push_back(offset);
  	}
  }
  InvertedIndex::InvertedIndex(){}
  std::map<int, std::vector<std::vector<int>>> InvertedIndex::getInvertedIndex(){
    return this->inverted_index;
  }
  void InvertedIndex::print(){
    for (auto it1 = this->inverted_index.begin(); it1 != this->inverted_index.end(); ++it1) {
  		int key = it1->first;
  		std::cout << key << std::endl;
  		std::vector<std::vector<int>> offsets = it1->second;
  		for (auto offset_vector : offsets) {
  			for (auto offset : offset_vector) {
  				std::cout << offset;
  			}
  			std::cout << std::endl;
  		}
  	}
  }
  //this function will insert the key if not already present
  // if key is already present, the offsets will be appended
  void InvertedIndex::addToIndex(int key, std::vector<std::vector<int>> offsets){
    this->inverted_index[key].insert(this->inverted_index[key].begin(), offsets.begin(), offsets.end());
  }
  long InvertedIndex::size(){
    return this->inverted_index.size();
  }
  long InvertedIndex::matches(){
    //since one entry will have multiple vectors, to know all the matches we need to add up the size of the vectors
    long count=0;
    for (auto it1 = this->inverted_index.begin(); it1 != this->inverted_index.end(); ++it1) {
      count += it1->second.size();
    }
    return count;
  }
}
