// BENCHMARK DEFINITIONS

#include <math.h>
#include <random>
#include <unordered_map>
#include <map>
#include <chrono>

#include "benchmark.h"
#include "configuration.h"

namespace emerald{

configuration state;

typedef std::vector<std::pair<int,int>> matches_type;
typedef std::unordered_map<int,std::vector<int>> hash_table_type;
typedef std::map<int,std::vector<int>> tree_type;

typedef std::chrono::high_resolution_clock Time;

unsigned seed = 23;
std::default_random_engine generator (seed);
std::uniform_int_distribution<int> boolean_distribution(0,1);
std::uniform_int_distribution<int> first_half_distribution(1,10);
std::uniform_int_distribution<int> second_half_distribution(10,100000);

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

// Build join tree for a given pair of columns
std::map<std::pair<int,int>,std::vector<std::pair<int,int>>> BuildJoinTree(int* array_1, int array_1_size, int* array_2, int array_2_size){

	std::map<std::pair<int,int>,std::vector<std::pair<int,int>>> join_tree;

	// Process arrays data
	for(int array_1_itr = 0; array_1_itr < array_1_size; array_1_itr++){
		for(int array_2_itr = 0; array_2_itr < array_2_size; array_2_itr++){
			auto value_1 = array_1[array_1_itr];
			auto value_2 = array_2[array_2_itr];

			if(value_1 == value_2){
				join_tree[std::make_pair(value_1, value_2)].push_back(std::make_pair(array_1_itr,array_2_itr));
			}
		}
	}

	return join_tree;
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

void RunJoinBenchmark(){

	// Each column contains an array of numbers (table 1 and table 2)
	// 1-D array is sufficient since we are focusing on a couple of columns for now
	int* column_1;
	int* column_2;

	// Column Sizes
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

	matches.clear();

	// ALGORITHM 2: VALUE-CENTRIC JOIN (JOINT HASH TABLE) (TYPE 1)

	// Build hash table for value-centric join
	auto join_hash_table = BuildJoinHashTable(column_1, column_1_size, column_2, column_2_size);

	start = Time::now();

	for(auto entry: join_hash_table){

		auto column_1_offsets = entry.second.first;
		auto column_2_offsets = entry.second.second;

		for(auto column_1_offset: column_1_offsets){
			for(auto column_2_offset: column_2_offsets){
				matches.push_back(std::make_pair(column_1_offset, column_2_offset));
			}
		}

	}

    stop = Time::now();
	elapsed = stop - start;
	time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "VALUE-CENTRIC JOIN (JOINT HASH TABLE) (TYPE 1): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);

	matches.clear();

	// ALGORITHM 3: TUPLE-CENTRIC JOIN (WITH INVERTED INDEX ON COLUMN_1)

	// Build tree for inverted index
	auto tree_1 = BuildTree(column_1, column_1_size);

	//PrintTree(tree_1);

	start = Time::now();

	for(int column_2_itr = 0; column_2_itr < column_2_size; column_2_itr++){
		auto value = column_2[column_2_itr];

		auto column_1_offsets = tree_1[value];

		for(auto column_1_offset: column_1_offsets){
			matches.push_back(std::make_pair(column_1_offset, column_2_itr));
		}
	}

    stop = Time::now();
	elapsed = stop - start;
	time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "TUPLE-CENTRIC JOIN (WITH INVERTED INDEX ON COLUMN_1): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);

	matches.clear();

	// ALGORITHM 4: TUPLE-CENTRIC JOIN (WITH JOINT INDEX ON BOTH COLUMNS)

	// Build join tree
	auto join_tree = BuildJoinTree(column_1, column_1_size, column_2, column_2_size);

	std::cout <<"JOIN TREE SIZE: " << join_tree.size() << "\n";

	//PrintTree(tree_1);

	start = Time::now();

	for(auto entry: join_tree){

		auto match_list = entry.second;

		for(auto pair_itr: match_list){
			matches.push_back(pair_itr);
		}

	}

    stop = Time::now();
	elapsed = stop - start;
	time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "TUPLE-CENTRIC JOIN (WITH JOINT INDEX ON BOTH COLUMNS): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);

	matches.clear();

	// ALGORITHM 5: VALUE-CENTRIC JOIN (SINGLE HASH TABLE) (TYPE 2)

	// Build hash table for value-centric join
	auto hash_table = BuildHashTable(column_1, column_1_size);

	start = Time::now();

	for(int column_2_itr = 0; column_2_itr < column_2_size; column_2_itr++){
		auto value = column_2[column_2_itr];

		auto column_1_offsets = hash_table[value];

		for(auto column_1_offset: column_1_offsets){
			matches.push_back(std::make_pair(column_1_offset, column_2_itr));
		}
	}

    stop = Time::now();
	elapsed = stop - start;
	time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "VALUE-CENTRIC JOIN (SINGLE HASH TABLE) (TYPE 2): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);

	matches.clear();


	// Clean up arrays
	delete column_1;
	delete column_2;

}

} // End namespace emerald
