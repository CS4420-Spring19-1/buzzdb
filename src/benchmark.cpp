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

	std::vector<int> column_1;
	std::vector<int> column_2;
	int column_1_size = 50;
	int column_2_size = column_1_size/10;

	// Load data
	for(int column_1_itr = 0; column_1_itr < column_1_size; column_1_itr++){
		auto number = generate_number();
		column_1.push_back(number);
		std::cout << number << " ";
	}
	std::cout << "\n";

	for(int column_2_itr = 0; column_2_itr < column_2_size; column_2_itr++){
		auto number = generate_number();
		column_2.push_back(number);
		std::cout << number << " ";
	}
	std::cout << "\n";


}

} // End namespace emerald
