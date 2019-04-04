#pragma once

#include <vector>
#include "type.h"

namespace emerald {
class HeapFileEncoder {
 public:
  HeapFileEncoder();

  virtual ~HeapFileEncoder();

  static void Convert(std::vector<<std::vector<int>> tuples, FILE *out_file,
                      int n_page_bytes, int num_fields);

  static void Convert(FILE * in_file, FILE * out_file, int n_page_bytes,
                      int num_fields);

  static void Convert(FILE * in_file, FILE * out_file, int n_page_bytes,
                      int num_fields, Type type_ar[]);

  static void Convert(FILE *in_file, FILE *out_file, int n_page_bytes,
                      int num_fields, Type type_ar[], char field_separator);

 private:
};
}