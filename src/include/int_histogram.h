#pragma once

#include <vector>
#include "math.h"
#include <string>


namespace emerald {
class IntHistogram {
 public:

  enum OpType {
    EQUALS,
    NOT_EQUALS,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_OR_EQUAL,
    LESS_THAN_OR_EQUAL
  };
 
  IntHistogram(int bucketSize, int min, int max);

  ~IntHistogram();

  void addValue(int v);

  int getBucketIndex(int v);

  double estimateSelectivity(OpType op, int v);

  double b_partCalc(int v, OpType op);

 // std::string toString();


 
 private:
    int bucketsNum;
    int min;
    int max;
    int totalNum;
    double width;
    int* buckets;

};
}
