// BENCHMARK DEFINITIONS

#include <math.h>
#include <random>

#include "benchmark.h"
#include "configuration.h"

namespace emerald{

configuration state;

unsigned seed = 23;
std::default_random_engine generator (seed);
std::uniform_int_distribution<int> boolean_distribution(0,1);
std::uniform_int_distribution<int> first_half_distribution(1,10);
std::uniform_int_distribution<int> second_half_distribution(10,100);

int generate_number(){

	// first or second half?
	bool first_half = boolean_distribution(generator);

	// generate number using distribution
	if(first_half == true){
		return first_half_distribution(generator);
	}
	else {
		return second_half_distribution(generator);
	}

}

void RunJoinBenchmark(){

	int* column_1;
	int* column_2;
	int column_1_size = 50;
	int column_2_size = column_1_size/5;

	// Initialize arrays
	column_1 = new int[column_1_size];
	column_2 = new int[column_2_size];

	// Load data
	for(int column_1_itr = 0; column_1_itr < column_1_size; column_1_itr++){
		auto number = generate_number();
		column_1[column_1_itr] = number;
		std::cout << column_1[column_1_itr] << " ";
	}
	std::cout << "\n";

	for(int column_2_itr = 0; column_2_itr < column_2_size; column_2_itr++){
		auto number = generate_number();
		column_2[column_2_itr] = number;
		std::cout << column_2[column_2_itr] << " ";
	}
	std::cout << "\n";

	std::vector<std::pair<int,int>> matches;

	// NESTED LOOP JOIN
	for(int column_1_itr = 0; column_1_itr < column_1_size; column_1_itr++){
		auto column_1_number = column_1[column_1_itr];

		for(int column_2_itr = 0; column_2_itr < column_2_size; column_2_itr++){
			auto column_2_number = column_2[column_2_itr];

			// Check if numbers match
			if(column_1_number == column_2_number){
				// Add to match list
				matches.push_back(std::make_pair(column_1_itr, column_2_itr));
			}
		}
	}

	std::cout << "MATCHES: \n";
	for(auto match: matches){
		std::cout << column_1[match.first] << " :: " << match.first << " " << match.second << "\n";
	}
	std::cout << "\n";

	// Clean up arrays
	delete column_1;
	delete column_2;

}

} // End namespace emerald
