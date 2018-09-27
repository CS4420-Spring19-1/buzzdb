#include <vector>
#include "map.h"
#include <chrono>
#include <iostream>


std::vector<std::pair<int, int> > basic_join(table alice, table bob){
  std::vector<std::pair<int, int> > result;
  for (int i = 0; i < alice.getSize(); i++){
    int value_one = alice.container[i][1];
    for (int j = 0; j < bob.getSize(); j++){
      std::pair<int, int> pair_to_add;
      int value_two = bob.container[j][1];
      if(value_one == value_two){
         pair_to_add.first = alice.container[i][0];
         pair_to_add.second = bob.container[j][0];
         result.push_back(pair_to_add);
      }
    }
  }
  return result;
}

void print_vector(std::vector<std::pair<int, int> > input){
  for(int i = 0; i < input.size(); i++){
      printf("%d, %d \n", input[i].first, input[i].second);
  }
}

void print_vector2(std::vector<int>  input){
  for(int i = 0; i < input.size(); i++){
      printf("%d ", input[i]);
  }
}

void map_join_helper(map alice, map bob){
     for (auto& pair: alice.container){
       auto found = bob.container.find(pair.first);
       if(found!= bob.container.end()){
         /*printf("%d => ",pair.first); 
         print_vector2(pair.second); 
         print_vector2(found->second);
         printf("\n");*/
       }
     }
}

void map_join (map alice, map bob){
  if(alice.container.size() <= bob.container.size()){
    map_join_helper(alice, bob);
  }
  else{
    map_join_helper(bob, alice);
  }
}

int main(){
  table alice(100000);
  table bob (100000);
  //alice.printArray();
  //bob.printArray();
  //print_vector
  auto time1 = std::chrono::high_resolution_clock::now();
  for(int i=0; i < 10; i ++){
   (basic_join(alice, bob));
  } 
  auto time2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> seconds = time2-time1;
  std::cout << "Elapsed time for basic nested loop join: " << seconds.count()/10 << "s\n";
  
  map bobjr(bob);
  map alicejr(alice);
  auto time3 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 10; i++){
    map_join(alicejr, bobjr);
  }
  auto time4 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> seconds2 = time4-time3;
  std::cout << "Elapsed time for map join (no pairs made): " << seconds2.count()/10 << "s\n"; 
  return 0;
}
