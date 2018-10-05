// ENGINE SOURCE

#include <iostream>
#include <fstream>
#include <chrono>

#include <gtest/gtest.h>
#include <glog/logging.h>

#include "benchmark.h"
#include "macros.h"
#include "configuration.h"

namespace emerald {

extern configuration state;

// Main Entry Point
void RunBenchmark() {

	RunJoinBenchmark();

}

}  // namespace engine

int main(int argc, char **argv) {

  // Initialize Google's logging library.
  google::InitGoogleLogging(argv[0]);

  emerald::ParseArguments(
      argc, argv, emerald::state);

  emerald::RunBenchmark();

  exit(0);
}
