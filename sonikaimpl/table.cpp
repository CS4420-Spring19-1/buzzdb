#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#define SIZE 100
#define SKEW_SIZE 100
#define VALUE_SET 10000
#define PERCENT 0.5

//constructor
table::table(int size){
  table::cap = size;
  table::container = new int*[size];
  for(int i = 0; i < size; i ++){
    container[i] = new int[2];
    container[i][0] = i;
  }
  int value = 1;
  for (int i = 0; i < (size * PERCENT); i++){
    if(value > SKEW_SIZE){
      value = 1;
    }
    container[i][1] = value;
    value++;
  }
  //srand(time(NULL));
  srand(100);
  //std::default_random_engine r;
  //std::uniform_int_distrabution<int> dist (0, VALUE_SET);
  for (int i = (size*PERCENT); i <size; i++){
    int num = rand()%VALUE_SET + 1;
    //int num = dist(r) + 1;
    container[i][1] = num;
  }
}

//method to print the table
void table::printArray(){
  printf("[");
  for (int i = 0; i < cap-1; i++){
    printf(" [%d, %d],\n", container[i][0], container[i][1]);
  }
  printf(" [%d, %d]]\n", container[cap-1][0], container[cap-1][1]);
}

int table::getSize(){
  return cap;
}

/*int main(){
  table my_table(100);
  my_table.printArray();
  return 0;
}*/
