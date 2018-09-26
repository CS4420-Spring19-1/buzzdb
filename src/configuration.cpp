// CONFIGURATION SOURCE

#include <algorithm>
#include <iomanip>
#include <memory>

#include "configuration.h"

namespace emerald {

void Usage() {
  std::cout <<
      "\n"
      "Command line options : machine <options>\n"
      "   -a --hierarchy_type                 :  hierarchy type\n"
      "   -f --file_name                      :  file name\n"
      "   -o --operation_count                :  operation count\n"
      "   -v --verbose                        :  verbose\n"
      ;
  exit(EXIT_FAILURE);
}

static struct option opts[] = {
    {"hierarchy_type", optional_argument, NULL, 'a'},
    {"file_name", optional_argument, NULL, 'f'},
    {"operation_count", optional_argument, NULL, 'o'},
    {"verbose", optional_argument, NULL, 'v'},
    {NULL, 0, NULL, 0}
};

static void ValidateHierarchyType(const configuration &state) {
  if (state.hierarchy_type < 1 || state.hierarchy_type > HIERARCHY_TYPE_MAX) {
    printf("Invalid hierarchy_type :: %d\n", state.hierarchy_type);
    exit(EXIT_FAILURE);
  }
  else {
    printf("%30s : %s\n", "hierarchy_type",
           HierarchyTypeToString(state.hierarchy_type).c_str());
  }
}

static void ValidateFileName(const configuration &state){
  printf("%30s : %s\n", "file_name", state.file_name.c_str());
}

static void ValidateOperationCount(const configuration &state){
  if(state.operation_count > 0) {
    printf("%30s : %lu\n", "operation_count", state.operation_count);
  }
}

void ParseArguments(int argc, char *argv[], configuration &state) {

  // Default Values
  state.verbose = false;

  state.hierarchy_type = HIERARCHY_TYPE_DRAM_NVM_DISK;
  state.file_name = "";
  state.operation_count = 0;

  // Parse args
  while (1) {
    int idx = 0;
    int c = getopt_long(argc, argv,
                        "a:f:o:v",
                        opts, &idx);

    if (c == -1) break;

    switch (c) {
      case 'a':
        state.hierarchy_type = (HierarchyType)atoi(optarg);
        break;
      case 'f':
        state.file_name = optarg;
        break;
      case 'o':
        state.operation_count = atoi(optarg);
        break;
      case 'v':
        state.verbose = atoi(optarg);
        break;
      case 'h':
        Usage();
        break;

      default:
        printf("Unknown option: -%c-\n", c);
        Usage();
    }
  }

  ValidateHierarchyType(state);
  ValidateFileName(state);
  ValidateOperationCount(state);

  printf("//===----------------------------------------------------------------------===//\n");

}

}  // namespace emerald
