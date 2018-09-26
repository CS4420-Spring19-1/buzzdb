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
      "   -o --column_1_size                  :  column 1 size\n"
      "   -v --verbose                        :  verbose\n"
      ;
  exit(EXIT_FAILURE);
}

static struct option opts[] = {
    {"hierarchy_type", optional_argument, NULL, 'a'},
    {"file_name", optional_argument, NULL, 'f'},
    {"column_1_size", optional_argument, NULL, 'o'},
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

static void ValidateColumn1Size(const configuration &state){
  if(state.column_1_size > 0) {
    printf("%30s : %lu\n", "column_1_size", state.column_1_size);
  }
}

void ParseArguments(int argc, char *argv[], configuration &state) {

  // Default Values
  state.verbose = false;

  state.hierarchy_type = HIERARCHY_TYPE_DRAM_NVM_DISK;
  state.file_name = "";
  state.column_1_size = 1000 * 100;

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
        state.column_1_size = atoi(optarg);
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
  ValidateColumn1Size(state);

  printf("//===----------------------------------------------------------------------===//\n");

}

}  // namespace emerald
