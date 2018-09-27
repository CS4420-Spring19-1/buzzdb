// BENCHMARK DEFINITIONS

#include <math.h>
#include <random>
#include <unordered_map>
#include <map>
#include <chrono>
#include <set>

#include "benchmark.h"
#include "configuration.h"

namespace emerald{

configuration state;

typedef std::vector<std::pair<int,int>> matches_type;
typedef std::unordered_map<int,std::vector<int>> hash_table_type;
typedef std::map<int,std::vector<int>> tree_type;

typedef std::chrono::high_resolution_clock Time;

struct dictionary_entry {
	int value;
	std::vector<int> column_1_offset_array;
	std::vector<int> column_2_offset_array;
};

unsigned seed = 23;
std::default_random_engine generator (seed);
std::uniform_int_distribution<int> skew_distribution(1,10);
std::uniform_int_distribution<int> column_1_first_half_distribution(1,100);
std::uniform_int_distribution<int> column_1_second_half_distribution(100,1000000);
std::uniform_int_distribution<int> column_2_first_half_distribution(1,100000);
std::uniform_int_distribution<int> column_2_second_half_distribution(100000,1000000);

////////////////////////////////////////////////////////////////////////////////////////////
// GENERATORS
////////////////////////////////////////////////////////////////////////////////////////////

int GenerateNumberColumn1(){

	// first or second half?
	auto number = skew_distribution(generator);

	// generate number using distribution
	if(number < 2){
		return column_1_first_half_distribution(generator);
	}
	else {
		return column_1_second_half_distribution(generator);
	}

}

int GenerateNumberColumn2(){

	// first or second half?
	auto number = skew_distribution(generator);

	// generate number using distribution
	if(number < 5){
		return column_2_first_half_distribution(generator);
	}
	else {
		return column_2_second_half_distribution(generator);
	}

}

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

// Build dictionary for a given pair of columns
std::pair<std::vector<dictionary_entry>, std::vector<int>> BuildDictionary(int* array_1, int array_1_size, int* array_2, int array_2_size){

	std::vector<dictionary_entry> dictionary;
	int dictionary_itr = 0;
	std::map<int, int> dictionary_map;
	std::vector<int> dictionary_map_vector;

	// Process arrays data
	for(int array_1_itr = 0; array_1_itr < array_1_size; array_1_itr++){
		auto number = array_1[array_1_itr];

		// New entry
		if(dictionary_map.count(number) == 0){
			dictionary_map[number] = dictionary_itr;

			dictionary_entry e;
			e.value = number;
			e.column_1_offset_array.push_back(array_1_itr);

			dictionary.push_back(e);
			dictionary_itr++;
		}
		// Update existing entry
		else{
			auto entry_offset = dictionary_map[number];
			dictionary[entry_offset].column_1_offset_array.push_back(array_1_itr);
		}
	}

	for(int array_2_itr = 0; array_2_itr < array_2_size; array_2_itr++){
		auto number = array_2[array_2_itr];

		// New entry
		if(dictionary_map.count(number) == 0){
			dictionary_map[number] = dictionary_itr;

			dictionary_entry e;
			e.value = number;
			e.column_2_offset_array.push_back(array_2_itr);

			dictionary.push_back(e);
			dictionary_map_vector.push_back(dictionary_itr);
			dictionary_itr++;
		}
		// Update existing entry
		else{
			auto entry_offset = dictionary_map[number];
			dictionary[entry_offset].column_2_offset_array.push_back(array_2_itr);
			dictionary_map_vector.push_back(entry_offset);
		}

	}

	return std::make_pair(dictionary, dictionary_map_vector);
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

	// ALGORITHM 2: VALUE-CENTRIC JOIN (JOINT HASH TABLE) (TYPE 1)

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

void RunAlgorithm3(int* column_1, int column_1_size, int* column_2, int column_2_size){
	std::vector<std::pair<int,int>> matches;

	// ALGORITHM 3: TUPLE-CENTRIC JOIN (WITH INVERTED INDEX ON COLUMN_1)

	// Build tree for inverted index
	auto tree_1 = BuildTree(column_1, column_1_size);

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
	auto elapsed = stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "TUPLE-CENTRIC JOIN (WITH INVERTED INDEX ON COLUMN_1): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);

}

void RunAlgorithm4(int* column_1, int column_1_size, int* column_2, int column_2_size){
	std::vector<std::pair<int,int>> matches;

	// ALGORITHM 4: TUPLE-CENTRIC JOIN (WITH JOINT INDEX ON BOTH COLUMNS)

	// Build join tree
	auto join_tree = BuildJoinTree(column_1, column_1_size, column_2, column_2_size);

	//std::cout <<"JOIN TREE SIZE: " << join_tree.size() << "\n";

	auto start = Time::now();

	for(auto entry: join_tree){

		auto match_list = entry.second;

		for(auto pair_itr: match_list){
			matches.push_back(pair_itr);
		}

	}

	auto stop = Time::now();
	auto elapsed = stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	//std::cout << "TUPLE-CENTRIC JOIN (WITH JOINT INDEX ON BOTH COLUMNS): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);

}

void RunAlgorithm5(int* column_1, int column_1_size, int* column_2, int column_2_size){
	std::vector<std::pair<int,int>> matches;

	// ALGORITHM 5: VALUE-CENTRIC JOIN (SINGLE HASH TABLE) (TYPE 2)

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

void RunAlgorithm6(int* column_1, int column_1_size, int* column_2, int column_2_size){
	std::vector<std::pair<int,int>> matches;

	// ALGORITHM 6: VALUE-CENTRIC JOIN (DICTIONARY) (TYPE 1)

	// Build dictionary for value-centric join
	std::vector<dictionary_entry> dictionary;
	std::vector<int> dictionary_map_vector;
	std::tie(dictionary, dictionary_map_vector) = BuildDictionary(column_1, column_1_size, column_2, column_2_size);

	std::cout << "LIST SIZE: " << dictionary_map_vector.size() << "\n";

	auto start = Time::now();

	for(auto entry: dictionary){

		auto column_1_offsets = entry.column_1_offset_array;
		auto column_2_offsets = entry.column_2_offset_array;

		for(auto column_1_offset: column_1_offsets){
			for(auto column_2_offset: column_2_offsets){
				matches.push_back(std::make_pair(column_1_offset, column_2_offset));
			}
		}

	}

	auto stop = Time::now();
	auto elapsed = stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "VALUE-CENTRIC JOIN (DICTIONARY) (TYPE 1): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);

}

void RunAlgorithm7(int* column_1, int column_1_size, int* column_2, int column_2_size){
	std::vector<std::pair<int,int>> matches;

	// ALGORITHM 7: VALUE-CENTRIC JOIN (DICTIONARY) (TYPE 2)

	// Build dictionary for value-centric join
	std::vector<dictionary_entry> dictionary;
	std::vector<int> dictionary_map_vector;
	std::tie(dictionary, dictionary_map_vector) = BuildDictionary(column_1, column_1_size, column_2, column_2_size);

	std::cout << "LIST SIZE: " << dictionary_map_vector.size() << "\n";

	auto start = Time::now();

	for(int column_2_itr = 0; column_2_itr < column_2_size; column_2_itr++){

		auto dictionary_offset = dictionary_map_vector[column_2_itr];
		auto column_1_offsets = dictionary[dictionary_offset].column_1_offset_array;

		for(auto column_1_offset: column_1_offsets){
			matches.push_back(std::make_pair(column_1_offset, column_2_itr));
		}
	}

	auto stop = Time::now();
	auto elapsed = stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "VALUE-CENTRIC JOIN (DICTIONARY) (TYPE 2): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);
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

	std::set<int> column_1_set;
	std::set<int> column_2_set;

	// Load data into first column
	for(int column_1_itr = 0; column_1_itr < column_1_size; column_1_itr++){
		auto number = GenerateNumberColumn1();
		column_1[column_1_itr] = number;
		column_1_set.insert(number);
	}

	std::cout << "COLUMN 1 SET SIZE: " << column_1_set.size() << "\n";

	// Load data into second column
	for(int column_2_itr = 0; column_2_itr < column_2_size; column_2_itr++){
		auto number = GenerateNumberColumn2();
		column_2[column_2_itr] = number;
		column_2_set.insert(number);
	}

	std::cout << "COLUMN 2 SET SIZE: " << column_2_set.size() << "\n";

	// RUN ALGORITHMS

	//RunAlgorithm1(column_1, column_1_size, column_2, column_2_size);

	//RunAlgorithm2(column_1, column_1_size, column_2, column_2_size);

	RunAlgorithm3(column_1, column_1_size, column_2, column_2_size);

	//RunAlgorithm4(column_1, column_1_size, column_2, column_2_size);

	//RunAlgorithm5(column_1, column_1_size, column_2, column_2_size);

	RunAlgorithm6(column_1, column_1_size, column_2, column_2_size);

	RunAlgorithm7(column_1, column_1_size, column_2, column_2_size);

	// Clean up arrays
	delete[] column_1;
	delete[] column_2;

}

} // End namespace emerald
