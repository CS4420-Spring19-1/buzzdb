// ENGINE SOURCE

#include <iostream>
#include <fstream>

#include <gtest/gtest.h>
#include <glog/logging.h>

#include "macros.h"
#include "engine.h"
#include "configuration.h"

namespace engine {

extern configuration state;

// Main Entry Point
void RunBenchmark() {

}

}  // namespace engine

int main(int argc, char **argv) {

  // Initialize Google's logging library.
  google::InitGoogleLogging(argv[0]);

  engine::ParseArguments(
      argc, argv, engine::state);

  engine::RunBenchmark();

  return 0;
}
