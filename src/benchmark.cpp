// BENCHMARK DEFINITIONS

#include <math.h>
#include <random>
#include <unordered_map>
#include <chrono>

#include "benchmark.h"
#include "configuration.h"

namespace emerald{

configuration state;

typedef std::vector<std::pair<int,int>> matches_type;
typedef std::unordered_map<int,std::vector<int>> map_type;

typedef std::chrono::high_resolution_clock Time;

unsigned seed = 23;
std::default_random_engine generator (seed);
std::uniform_int_distribution<int> boolean_distribution(0,1);
std::uniform_int_distribution<int> first_half_distribution(1,10);
std::uniform_int_distribution<int> second_half_distribution(10,100);

int GenerateNumber(){

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

// Build hash table for a given column
std::unordered_map<int,std::vector<int>> GenerateHashTable(int* array, int array_size){

	std::unordered_map<int,std::vector<int>> map;

	// Process array data
	for(int array_itr = 0; array_itr < array_size; array_itr++){
		auto number = array[array_itr];
		map[number].push_back(array_itr);
	}

	return map;
}

// Print the matches
void PrintMatches(const matches_type& matches, int* array, bool verbose){

	std::cout << "MATCHES: ";
	std::cout << matches.size();
	std::cout << "\n";

	// Print all matches
	if(verbose == true){
		for(auto match: matches){
			std::cout << array[match.first] << " :: " << match.first << " " << match.second << "\n";
		}
		std::cout << "\n";
	}

}

// Print the contents of the map
void PrintMap(const map_type& map){

	for(auto entry: map){
		std::cout << entry.first << " :: ";
		for(auto offset: entry.second){
			std::cout << offset << " ";
		}
		std::cout << "\n";
	}

}

// Print the contents of the array
void PrintArray(int* array, int array_size){

	for(int array_itr = 0; array_itr < array_size; array_itr++){
		std::cout << array[array_itr] << " ";
	}
	std::cout << "\n";

}

void RunJoinBenchmark(){

	// Each column contains an array of numbers (table 1 and table 2)
	// 1-D array is sufficient since we are focusing on a couple of columns for now
	int* column_1;
	int* column_2;

	// TODO: Make it a runtime parameter
	int column_1_size = state.column_1_size;
	int column_2_size = column_1_size/5;

	// Initialize arrays
	column_1 = new int[column_1_size];
	column_2 = new int[column_2_size];

	// Load data into first column
	for(int column_1_itr = 0; column_1_itr < column_1_size; column_1_itr++){
		auto number = GenerateNumber();
		column_1[column_1_itr] = number;
	}

	// Print array
	//PrintArray(column_1, column_1_size);

	// Load data into second column
	for(int column_2_itr = 0; column_2_itr < column_2_size; column_2_itr++){
		auto number = GenerateNumber();
		column_2[column_2_itr] = number;
	}

	// Print array
	//PrintArray(column_2, column_2_size);

	std::vector<std::pair<int,int>> matches;

	auto start = Time::now();

	// TUPLE-CENTRIC JOIN
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

    auto stop = Time::now();
	std::chrono::duration<double> elapsed = stop - start;
	std::chrono::milliseconds time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "TUPLE-CENTRIC JOIN: " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);

	// Build hash tables for value-centric join
	auto map_1 = GenerateHashTable(column_1, column_1_size);
	auto map_2 = GenerateHashTable(column_2, column_2_size);

	//PrintMap(map_1);

	matches.clear();

	start = Time::now();

	// VALUE-CENTRIC JOIN
	for(auto entry: map_1){

		auto value = entry.first;
		auto column_1_offsets = entry.second;

		auto column_2_offsets = map_2[value];

		for(auto column_1_offset: column_1_offsets){
			for(auto column_2_offset: column_2_offsets){
				matches.push_back(std::make_pair(column_1_offset, column_2_offset));
			}
		}

	}

    stop = Time::now();
	elapsed = stop - start;
	time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "VALUE-CENTRIC JOIN: " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);

	// Clean up arrays
	delete column_1;
	delete column_2;

}

} // End namespace emerald
