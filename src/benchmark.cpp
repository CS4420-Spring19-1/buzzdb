// BENCHMARK DEFINITIONS

#include <math.h>
#include <random>
#include <unordered_map>
#include <map>
#include <chrono>
#include <set>
#include <climits>
#include <fstream>
#include <iostream>

#include "benchmark.h"
#include "configuration.h"
#include "zipfian.h"

namespace emerald{

configuration state;

typedef std::vector<std::pair<int,int>> matches_type;
typedef std::unordered_map<int,std::vector<int>> hash_table_type;
typedef std::map<int,std::vector<int>> tree_type;

typedef std::chrono::high_resolution_clock Time;

unsigned seed = 23;
std::default_random_engine generator (seed);
std::uniform_real_distribution<double> distribution(0.0, 1.0);

////////////////////////////////////////////////////////////////////////////////////////////
// BUILDERS
////////////////////////////////////////////////////////////////////////////////////////////


// Build hash table for one columns
std::unordered_map<int,std::vector<int>> BuildHashTable(int* array_1, int array_1_size){

	std::unordered_map<int,std::vector<int>> hash_table;

	// Process array data
	for(int array_1_itr = 0; array_1_itr < array_1_size; array_1_itr++){
		auto number = array_1[array_1_itr];
		hash_table[number].push_back(array_1_itr);
	}

	return hash_table;
}

// Build tree for a given column
std::map<int,std::vector<int>> BuildTree(int* array, int array_size){

	std::map<int,std::vector<int>> tree;

	// Process array data
	for(int array_itr = 0; array_itr < array_size; array_itr++){
		auto value = array[array_itr];
		tree[value].push_back(array_itr);
	}

	return tree;
}

// Build hash table for both columns
std::unordered_map<int,std::pair<std::vector<int>,std::vector<int>>> BuildJoinHashTable(int* array_1, int array_1_size, int* array_2, int array_2_size){

	std::unordered_map<int,std::pair<std::vector<int>,std::vector<int>>> join_hash_table;

	// Process array data
	for(int array_1_itr = 0; array_1_itr < array_1_size; array_1_itr++){
		auto number = array_1[array_1_itr];
		join_hash_table[number].first.push_back(array_1_itr);
	}

	for(int array_2_itr = 0; array_2_itr < array_2_size; array_2_itr++){
		auto number = array_2[array_2_itr];
		join_hash_table[number].second.push_back(array_2_itr);
	}

	return join_hash_table;
}


////////////////////////////////////////////////////////////////////////////////////////////
// PRINTERS
////////////////////////////////////////////////////////////////////////////////////////////

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

// Print the contents of the hash table
void PrintMap(const hash_table_type& hash_table){

	for(auto entry: hash_table){
		std::cout << entry.first << " :: ";
		for(auto offset: entry.second){
			std::cout << offset << " ";
		}
		std::cout << "\n";
	}

}

// Print the contents of the tree
void PrintTree(const tree_type& tree){

	for(auto entry: tree){
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

////////////////////////////////////////////////////////////////////////////////////////////
// ALGORITHMS
////////////////////////////////////////////////////////////////////////////////////////////

void RunAlgorithm1(int* column_1, int column_1_size, int* column_2, int column_2_size){

	std::vector<std::pair<int,int>> matches;

	// ALGORITHM 1: TUPLE-CENTRIC JOIN (NO INDEX)

	auto start = Time::now();

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
	std::cout << "TUPLE-CENTRIC JOIN (NO INDEX): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);

}

void RunAlgorithm2(int* column_1, int column_1_size, int* column_2, int column_2_size){
	std::vector<std::pair<int,int>> matches;

	// ALGORITHM 2: TUPLE-CENTRIC JOIN (WITH INVERTED INDEX ON COLUMN_1)

	// Build tree for inverted index
	auto tree_1 = BuildTree(column_1, column_1_size);

	std::chrono::duration<double> elapsed;

	//PrintTree(tree_1);
	auto start = Time::now();

	for(int column_2_itr = 0; column_2_itr < column_2_size; column_2_itr++){
		auto value = column_2[column_2_itr];

		auto column_1_offsets = tree_1[value];

		for(auto column_1_offset: column_1_offsets){
			matches.push_back(std::make_pair(column_1_offset, column_2_itr));
		}

	}

	auto stop = Time::now();
	elapsed += stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);

	std::cout << "TUPLE-CENTRIC JOIN (WITH INVERTED INDEX ON COLUMN_1): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);

}

void RunAlgorithm3(int* column_1, int column_1_size, int* column_2, int column_2_size){
	std::vector<std::pair<int,int>> matches;

	// ALGORITHM 3: VALUE-CENTRIC JOIN (JOINT HASH TABLE) (TYPE 1)

	// Build hash table for value-centric join
	auto join_hash_table = BuildJoinHashTable(column_1, column_1_size, column_2, column_2_size);

	auto start = Time::now();

	for(auto entry: join_hash_table){

		auto column_1_offsets = entry.second.first;
		auto column_2_offsets = entry.second.second;

		for(auto column_1_offset: column_1_offsets){
			for(auto column_2_offset: column_2_offsets){
				matches.push_back(std::make_pair(column_1_offset, column_2_offset));
			}
		}

	}

	auto stop = Time::now();
	auto elapsed = stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "VALUE-CENTRIC JOIN (JOINT HASH TABLE) (TYPE 1): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);

}

void RunAlgorithm4(int* column_1, int column_1_size, int* column_2, int column_2_size){
	std::vector<std::pair<int,int>> matches;

	// ALGORITHM 4: VALUE-CENTRIC JOIN (SINGLE HASH TABLE) (TYPE 2)

	// Build hash table for value-centric join
	auto hash_table = BuildHashTable(column_1, column_1_size);

	auto start = Time::now();

	for(int column_2_itr = 0; column_2_itr < column_2_size; column_2_itr++){
		auto value = column_2[column_2_itr];

		auto column_1_offsets = hash_table[value];

		for(auto column_1_offset: column_1_offsets){
			matches.push_back(std::make_pair(column_1_offset, column_2_itr));
		}
	}

	auto stop = Time::now();
	auto elapsed = stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "VALUE-CENTRIC JOIN (SINGLE HASH TABLE) (TYPE 2): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);

}

//ALGORITHM 5 - 2 SEPERATE HASH TABLE
void RunAlgorithm5(int* column_1, int column_1_size, int* column_2, int column_2_size){
        std::vector<std::pair<int,int>> matches;

        // Build hash table for value-centric join
        auto hash_table_1 = BuildHashTable(column_1, column_1_size);
	auto hash_table_2 = BuildHashTable(column_2, column_2_size);

        auto start = Time::now();
        for(auto column_2_itr = hash_table_2.begin(); column_2_itr != hash_table_2.end(); ++column_2_itr){
		auto column_2_offsets = hash_table_2[column_2_itr->first];
        	try{
			auto column_1_offsets = hash_table_1.at(column_2_itr->first);
			for(auto column_2_offset: column_2_offsets){
				for(auto column_1_offset: column_1_offsets){
                			matches.push_back(std::make_pair(column_1_offset, column_2_offset));
				}
                	}
		} catch (const std::out_of_range &e) {

			//do nothing
		}

        }

        auto stop = Time::now();
        auto elapsed = stop - start;
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "VALUE-CENTRIC JOIN (SEPERATE HASH TABLES): " << time_milliseconds.count() << " ms \n";

        PrintMatches(matches, column_1, false);

}

//ALGORITHM 6 - 2 SEPERATE TREES
void RunAlgorithm6(int* column_1, int column_1_size, int* column_2, int column_2_size){
        std::vector<std::pair<int,int>> matches;

        // Build tree for value-centric join
        auto tree_1 = BuildTree(column_1, column_1_size);
        auto tree_2 = BuildTree(column_2, column_2_size);

        auto start = Time::now();
        for(auto column_2_itr = tree_2.begin(); column_2_itr != tree_2.end(); ++column_2_itr){
                auto column_2_offsets = column_2_itr->second;

                        auto column_1_entry = tree_1.find(column_2_itr->first);
												if ( column_1_entry!= tree_1.end()) {
													auto column_1_offsets = column_1_entry->second;
													for(auto column_2_offset: column_2_offsets){
	                                for(auto column_1_offset: column_1_offsets){
	                                        matches.push_back(std::make_pair(column_1_offset, column_2_offset));
	                                }
	                        }
												}

        }

        auto stop = Time::now();
        auto elapsed = stop - start;
        auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        std::cout << "VALUE-CENTRIC JOIN (SEPERATE TREES): " << time_milliseconds.count() << " ms \n";

        PrintMatches(matches, column_1, false);

}

void RunJoinBenchmark(){

	// Each column contains an array of numbers (table 1 and table 2)
	// 1-D array is sufficient since we are focusing on a couple of columns for now
	int* column_1;
	int* column_2;

	// Column Sizes
	int column_1_size = state.column_1_size;
	int column_2_size = column_1_size * state.size_factor;

	// Initialize arrays
	column_1 = new int[column_1_size];
	column_2 = new int[column_2_size];

	std::set<int> column_1_set;
	std::set<int> column_2_set;

	ZipfDistribution zipf1(state.range, 0.9);
	ZipfDistribution zipf2(10000000, state.join_selectivity_threshold);

	// Load data into first column
	for(int column_1_itr = 0; column_1_itr < column_1_size; column_1_itr++){
		auto number = zipf1.GetNextNumber();
		column_1[column_1_itr] = number;
		column_1_set.insert(number);
		//std::cout << number << " ";
	}

	std::cout << "COLUMN 1 SET SIZE: " << column_1_set.size() << "\n";

	// Load data into second column
	for(int column_2_itr = 0; column_2_itr < column_2_size; column_2_itr++){
		auto number = zipf2.GetNextNumber();
		column_2[column_2_itr] = number;
		column_2_set.insert(number);
		//std::cout << number << " ";
	}

	std::cout << "COLUMN 2 SET SIZE: " << column_2_set.size() << "\n";

	// RUN ALGORITHMS

	//RunAlgorithm1(column_1, column_1_size, column_2, column_2_size);

	switch (state.algorithm_type) {
	case ALGORITHM_TYPE_TUPLE_CENTRIC_INVERTED_INDEX: {
		RunAlgorithm2(column_1, column_1_size, column_2, column_2_size);
		break;
	}
	case ALGORITHM_TYPE_VALUE_CENTRIC_JOIN_1: {
		RunAlgorithm3(column_1, column_1_size, column_2, column_2_size);
		break;
	}
	case ALGORITHM_TYPE_VALUE_CENTRIC_JOIN_2: {
		RunAlgorithm4(column_1, column_1_size, column_2, column_2_size);
		break;
	}
  case ALGORITHM_TYPE_VALUE_CENTRIC_JOIN_3: {
		RunAlgorithm5(column_1, column_1_size, column_2, column_2_size);
		break;
  	}
	case ALGORITHM_TYPE_VALUE_CENTRIC_JOIN_4:{
		RunAlgorithm6(column_1, column_1_size, column_2, column_2_size);
		break;
	}
	default: {
		std::cout << "Invalid algorithm: " << state.algorithm_type << "\n";
		break;
	}
	}
	printf("//===----------------------------------------------------------------------===//\n");
	// Clean up arrays
	delete[] column_1;
	delete[] column_2;

}

} // End namespace emerald
