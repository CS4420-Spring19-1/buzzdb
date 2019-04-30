#pragma once

#include <vector>
#include "math.h"
#include "int_histogram.h"

namespace emerald {
class StringHistogram {
 public:

  StringHistogram(int buckets);

  ~StringHistogram();

  int stringToInt(std::string s);

  int maxVal();

  int minVal();

  void addValue(std::string s);

  double estimateSelectivity(IntHistogram::OpType op, std::string s);

 
 private:
  IntHistogram* hist;

};
}
