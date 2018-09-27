#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include "table.h"
using namespace std;

class map{
  
  public:
    map(table input);
    std::unordered_map<int, std::vector<int> > container;
    void printMap();
};
