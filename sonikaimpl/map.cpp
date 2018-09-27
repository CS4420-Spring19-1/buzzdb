#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include <vector>
using namespace std;

map::map(table input){
 for (int i = 0; i < input.getSize(); i++){
   auto found = container.find(input.container[i][1]); 
   if( found!= container.end()){
     found->second.push_back(input.container[i][0]);
   }
   else{
     std::vector<int> values;
     values.push_back(input.container[i][0]);
     container.insert({input.container[i][1], values});
   }
  }
}

//helper method used by printMap to print the vector of values
void print_vector(std::vector<int>  input){
  for(int i = 0; i < input.size(); i++){
      printf("%d ", input[i]);
  }
}

//method to print a representation of the map
void map::printMap(){
  for(auto& pair: container){
     printf("%d =>", pair.first);
     print_vector(pair.second);
     printf("\n");
  }
}


/*int main(){
  table bob(10);
  bob.printArray();
  map bobjr(bob);
  bobjr.printMap();
return 0;

}*/
