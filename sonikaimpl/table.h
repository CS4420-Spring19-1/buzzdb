/*class to represent a table 
very basic right now (2D array) will 
be updated later?*/

#include <stdio.h>
#include <stdlib.h>
class table{
  
  private:
    int cap;
  public: 
    int** container;
    table(int size);
    void printArray();  
    int getSize();

};
