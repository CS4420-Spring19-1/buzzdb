// CONFIGURATION HEADER

#pragma once

#include <getopt.h>
#include <sys/time.h>
#include <iostream>
#include <string>
#include <vector>

#include "types.h"

namespace emerald {

static const int generator_seed = 50;

class configuration {
 public:

  // hierarchy type
  HierarchyType hierarchy_type;

  // file name
  std::string file_name;

  // operation count
  size_t operation_count;

  // Verbose output
  bool verbose;

};

void Usage(FILE *out);

void ParseArguments(int argc, char *argv[], configuration &state);

}  // namespace emerald
