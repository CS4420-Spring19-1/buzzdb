#pragma once

#include <unordered_map>

namespace emerald {

class heap_file_encoder {
 
 public:
  heap_file_encoder();

  virtual ~heap_file_encoder();

  static void convert(std::vector << std::vector<int>> tuples, FILE *outFile, int npagebytes, int numFields);

  static void convert(FILE *inFile, FILE *outFile, int npagebytes, int numFields);

  static void convert(FILE *inFile, FILE *outFile, int npagebytes, int numFields, types[] typeAr);

  static void convert(FILE *inFile, FILE *outFile, int npagebytes, int numFields, types[] typeAr, char fieldSeparator);

 private:
};
}