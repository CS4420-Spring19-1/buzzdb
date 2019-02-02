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
			"   -a --algorithm_type                 :  algorithm type\n"
			"   -f --file_name                      :  file name\n"
			"   -j --join_selectivity_threshold     :  join selectivity threshold\n"
			"   -o --column_1_size                  :  column 1 size\n"
			"   -v --verbose                        :  verbose\n"
      "   -r --range                          :  range\n"
			"   -s --size_factor                    :  column 2 size factor\n"
			;
	exit(EXIT_FAILURE);
}

static struct option opts[] = {
		{"algorithm_type", optional_argument, NULL, 'a'},
		{"file_name", optional_argument, NULL, 'f'},
		{"join_selectivity_threshold", optional_argument, NULL, 'j'},
		{"column_1_size", optional_argument, NULL, 'o'},
		{"verbose", optional_argument, NULL, 'v'},
    {"range", optional_argument, NULL, 'r'},
		{"size_factor", optional_argument, NULL, 's'},
		{NULL, 0, NULL, 0}
};

static void ValidateAlgorithmType(const configuration &state) {
	if (state.algorithm_type < 1 || state.algorithm_type > ALGORITHM_TYPE_MAX) {
		printf("Invalid hierarchy_type :: %d\n", state.algorithm_type);
		exit(EXIT_FAILURE);
	}
	else {
		printf("%30s : %s\n", "algorithm_type",
				AlgorithmTypeToString(state.algorithm_type).c_str());
	}
}

static void ValidateColumn1Size(const configuration &state){
	if(state.column_1_size <= 0) {
		printf("Invalid column_1_size :: %lu\n", state.column_1_size);
		exit(EXIT_FAILURE);
	}
	else{
		printf("%30s : %lu\n", "column_1_size", state.column_1_size);
	}
}

static void ValidateJoinSelectivityThreshold(const configuration &state){
	if(state.join_selectivity_threshold <= 0 || state.join_selectivity_threshold > 1) {
		printf("Invalid join_selectivity_threshold :: %f\n", state.join_selectivity_threshold);
		exit(EXIT_FAILURE);
	}
	else{
		printf("%30s : %f\n", "join_selectivity_threshold", state.join_selectivity_threshold);
	}
}


void ParseArguments(int argc, char *argv[], configuration &state) {

	// Default Values
	state.verbose = false;

	state.algorithm_type = ALGORITHM_TYPE_TUPLE_CENTRIC_INVERTED_INDEX;
	state.file_name = "";
	state.column_1_size = 1000 * 100;
	state.join_selectivity_threshold = 1;
    state.range = 10000;
	state.size_factor = 0.2;
	state.data_dir="";

	// Parse args
	while (1) {
		int idx = 0;
		int c = getopt_long(argc, argv,
				"a:f:o:j:v:r:s:d:",
				opts, &idx);

		if (c == -1) break;

		switch (c) {
		case 'a':
			state.algorithm_type = (AlgorithmType)atoi(optarg);
			break;
		case 'f':
			state.file_name = optarg;
			break;
		case 'j':
			state.join_selectivity_threshold = atof(optarg);
			break;
		case 'o':
			state.column_1_size = atoi(optarg);
			break;
		case 'v':
			state.verbose = atoi(optarg);
			break;
    	case 'r':
      		state.range = atoi(optarg);
      		break;
		case 's':
			state.size_factor = atof(optarg);
			break;
		case 'h':
			Usage();
			break;
		case 'd':
			state.data_dir = optarg;
			break;
		default:
			printf("Unknown option: -%c-\n", c);
			Usage();
		}
	}
	printf("//===----------------------------------------------------------------------===//\n");
	ValidateAlgorithmType(state);
	ValidateColumn1Size(state);
	ValidateJoinSelectivityThreshold(state);
 	printf("%30s : %f\n", "column 2 size factor", state.size_factor);



}

}  // namespace emerald
