// BENCHMARK DEFINITIONS

#include <math.h>
#include <random>
#include <unordered_map>
#include <map>
#include <chrono>
#include <set>
#include <climits>

#include "benchmark.h"
#include "configuration.h"

namespace emerald{

configuration state;

typedef std::vector<std::pair<int,int>> matches_type;
typedef std::unordered_map<int,std::vector<int>> hash_table_type;
typedef std::map<int,std::vector<int>> tree_type;

typedef std::chrono::high_resolution_clock Time;

struct offset_entry{
	int offset = INT_MAX;
	offset_entry* next = nullptr;
};

struct dictionary_entry {
	int value = INT_MAX;
	offset_entry* column_1_offset_array = nullptr;
	offset_entry* column_2_offset_array = nullptr;
	dictionary_entry* next = nullptr;
};

struct offset_batch_entry{
	int offsets[4] = {-1};
	int offset_batch_size = 4;
	int next_position = 0;
	offset_batch_entry* next = nullptr;
};

struct dictionary_batch_entry {
	int values[4] = {0};
	int dictionary_batch_size = 4;
	int next_position = 0;
	offset_batch_entry* column_1_offset_array[4] = {nullptr};
	offset_batch_entry* column_2_offset_array[4] = {nullptr};
	dictionary_batch_entry* next = nullptr;
};

unsigned seed = 23;
std::default_random_engine generator (seed);
std::uniform_int_distribution<int> skew_distribution(1,10);
std::uniform_int_distribution<int> column_1_first_half_distribution(1,1000);
std::uniform_int_distribution<int> column_1_second_half_distribution(1000,100000);
std::uniform_int_distribution<int> column_2_first_half_distribution(1,100000);
std::uniform_int_distribution<int> column_2_second_half_distribution(100000,1000000);

////////////////////////////////////////////////////////////////////////////////////////////
// GENERATORS
////////////////////////////////////////////////////////////////////////////////////////////

int GenerateNumberColumn1(){

	// first or second half?
	auto number = skew_distribution(generator);

	// generate number using distribution
	if(number < 5){
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

void PrintDictionary(dictionary_entry* dictionary){

	dictionary_entry* dictionary_itr = dictionary;
	auto itr = 0;
	while(dictionary_itr != nullptr){
		std::cout << itr++ << " :: " << dictionary_itr->value << " :: ";

		auto column_1_offset_array = dictionary_itr->column_1_offset_array;
		auto column_1_itr = column_1_offset_array;
		while(column_1_itr != nullptr){
			std::cout << column_1_itr->offset << " ";
			column_1_itr = column_1_itr->next;
		}

		std::cout << " --- ";

		auto column_2_offset_array = dictionary_itr->column_2_offset_array;
		auto column_2_itr = column_2_offset_array;
		while(column_2_itr != nullptr){
			std::cout << column_2_itr->offset << " ";
			column_2_itr = column_2_itr->next;
		}

		std::cout << "\n";

		dictionary_itr = dictionary_itr->next;
	}

	std::cout << "--------------------------------------------\n\n";
}



// Build dictionary for a given pair of columns
dictionary_entry* BuildDictionary(int* array_1, int array_1_size, int* array_2, int array_2_size){

	dictionary_entry* dictionary = nullptr;
	dictionary_entry* dictionary_last_entry = nullptr;
	int value_offset_itr = 0;
	std::map<int, int> value_to_offset_map;

	// Process arrays data
	for(int array_1_itr = 0; array_1_itr < array_1_size; array_1_itr++){
		auto number = array_1[array_1_itr];

		// New entry
		if(value_to_offset_map.count(number) == 0){
			value_to_offset_map[number] = value_offset_itr;

			dictionary_entry* e = new dictionary_entry();
			e->value = number;
			offset_entry* o = new offset_entry();
			o->offset = array_1_itr;
			e->column_1_offset_array = o;

			if(dictionary_last_entry != nullptr){
				dictionary_last_entry->next = e;
				dictionary_last_entry = e;
			}
			else{
				dictionary_last_entry = e;
				dictionary = e;
			}

			value_offset_itr++;
		}
		// Update existing entry
		else{
			dictionary_entry* dictionary_itr = dictionary;

			offset_entry* o = new offset_entry();
			o->offset = array_1_itr;

			while(dictionary_itr != nullptr){
				if(dictionary_itr->value == number){
					break;
				}
				dictionary_itr = dictionary_itr->next;
			}

			if(dictionary_itr->column_1_offset_array == nullptr){
				dictionary_itr->column_1_offset_array = o;
			}
			else{
				offset_entry* offset_itr = dictionary_itr->column_1_offset_array;
				while(offset_itr != nullptr){
					if(offset_itr->next == nullptr){
						break;
					}
					offset_itr = offset_itr->next;
				}
				offset_itr->next = o;
			}
		}
	}

	// Process arrays data
	for(int array_2_itr = 0; array_2_itr < array_2_size; array_2_itr++){
		auto number = array_2[array_2_itr];

		// New entry
		if(value_to_offset_map.count(number) == 0){
			value_to_offset_map[number] = value_offset_itr;

			dictionary_entry* e = new dictionary_entry();
			e->value = number;
			offset_entry* o = new offset_entry();
			o->offset = array_2_itr;
			e->column_2_offset_array = o;

			if(dictionary_last_entry != nullptr){
				dictionary_last_entry->next = e;
				dictionary_last_entry = e;
			}
			else{
				dictionary_last_entry = e;
				dictionary = e;
			}

			value_offset_itr++;
		}
		// Update existing entry
		else{
			dictionary_entry* dictionary_itr = dictionary;

			offset_entry* o = new offset_entry();
			o->offset = array_2_itr;

			while(dictionary_itr != nullptr){
				if(dictionary_itr->value == number){
					break;
				}
				dictionary_itr = dictionary_itr->next;
			}

			if(dictionary_itr->column_2_offset_array == nullptr){
				dictionary_itr->column_2_offset_array = o;
			}
			else{
				offset_entry* offset_itr = dictionary_itr->column_2_offset_array;
				while(offset_itr != nullptr){
					if(offset_itr->next == nullptr){
						break;
					}
					offset_itr = offset_itr->next;
				}
				offset_itr->next = o;
			}
		}
	}

	//PrintDictionary(dictionary);

	return dictionary;
}


dictionary_batch_entry* BuildDictionaryWithBatchEntries(int* array_1, int array_1_size, int* array_2, int array_2_size){
	dictionary_batch_entry* dictionary = nullptr;
	dictionary_batch_entry* dictionary_last_entry = nullptr;
	int value_offset_itr = 1;
	std::map<int, int> value_to_offset_map;

	// Process array 1 data
	for(int array_1_itr = 0; array_1_itr < array_1_size; array_1_itr++){
		auto number = array_1[array_1_itr];

		// New entry
		if(value_to_offset_map.count(number) == 0){ //number is not present in dictionary
			value_to_offset_map[number] = value_offset_itr;

			if(dictionary_last_entry != nullptr){ //check if last entry in the dicitonary has an empty slot

				if(dictionary_last_entry->next_position!=dictionary_last_entry->dictionary_batch_size){
					//there is an empty slot in the last dictionary entry
					dictionary_last_entry->values[dictionary_last_entry->next_position] = number;
					offset_batch_entry* o = new offset_batch_entry();
					o->offsets[o->next_position] = array_1_itr;
					o->next_position++;
					dictionary_last_entry->column_1_offset_array[dictionary_last_entry->next_position] = o;
					dictionary_last_entry->next_position++;
				} else {
					//no empty slot in last dictionary entry, so create a new entry

					dictionary_batch_entry* e = new dictionary_batch_entry();
					e->values[e->next_position] = number;
					offset_batch_entry* o = new offset_batch_entry();
					o->offsets[o->next_position] = array_1_itr;
					o->next_position++;
					e->column_1_offset_array[e->next_position] = o;
					e->next_position++;

					//update the last entry pointer
					dictionary_last_entry->next = e;
					dictionary_last_entry = e;

				}
			} else {
				//there is nothing in the dictionary, so create a new Entry
				dictionary_batch_entry* e = new dictionary_batch_entry();
				e->values[e->next_position] = number;
				offset_batch_entry* o = new offset_batch_entry();
				o->offsets[o->next_position] = array_1_itr;
				o->next_position++;
				e->column_1_offset_array[e->next_position] = o;
				e->next_position++;
				dictionary_last_entry = e;
				dictionary = e;
			}

			value_offset_itr++;
		}
		// Update existing entry
		else{
			dictionary_batch_entry* dictionary_itr = dictionary;

			int offset_in_value_batch = -1;
			while(dictionary_itr != nullptr){
				for (auto value_batch_itr = 0; value_batch_itr < dictionary_itr->dictionary_batch_size; value_batch_itr++) {
					if(dictionary_itr->values[value_batch_itr] == number){
						offset_in_value_batch = value_batch_itr;
						break;
					}
				}
				if(offset_in_value_batch!=-1){
					break;
				}
				dictionary_itr = dictionary_itr->next;
			}

				offset_batch_entry* offset_itr = dictionary_itr->column_1_offset_array[offset_in_value_batch];
				//find an empty slot in the offsets list
				while(offset_itr->next!=nullptr){
					if(offset_itr->next_position!=offset_itr->offset_batch_size){
						break;
					}
					offset_itr = offset_itr->next;
				}
				if(offset_itr->next_position != offset_itr->offset_batch_size){
					//we found an offset node with space in the array
					offset_itr->offsets[offset_itr->next_position] = array_1_itr;
					offset_itr->next_position++;
				} else {
					//create a new node
					offset_batch_entry* o = new offset_batch_entry();
					o->offsets[o->next_position] = array_1_itr;
					o->next_position++;
					offset_itr->next = o;
				}
		}
	}


	// Process array 2 data
	for(int array_2_itr = 0; array_2_itr < array_2_size; array_2_itr++){
		auto number = array_2[array_2_itr];
		// New entry
		if(value_to_offset_map.count(number) == 0){ //number is not present in dictionary

			value_to_offset_map[number] = value_offset_itr;
			if(dictionary_last_entry != nullptr){ //check if last entry in the dicitonary has an empty slot

				if(dictionary_last_entry->next_position!=dictionary_last_entry->dictionary_batch_size){
					//there is an empty slot in the last dictionary entry
					dictionary_last_entry->values[dictionary_last_entry->next_position] = number;
					offset_batch_entry* o = new offset_batch_entry();
					o->offsets[o->next_position] = array_2_itr;
					o->next_position++;
					dictionary_last_entry->column_2_offset_array[dictionary_last_entry->next_position] = o;
					dictionary_last_entry->next_position++;

				} else {
					//no empty slot in last dictionary entry, so create a new entry
					dictionary_batch_entry* e = new dictionary_batch_entry();
					e->values[e->next_position] = number;
					offset_batch_entry* o = new offset_batch_entry();
					o->offsets[o->next_position] = array_2_itr;
					o->next_position++;
					e->column_2_offset_array[e->next_position] = o;
					e->next_position++;

					//update the last entry pointer
					dictionary_last_entry->next = e;
					dictionary_last_entry = e;

				}
			} 
			value_offset_itr++;
		}
		// Update existing entry
		else{
			dictionary_batch_entry* dictionary_itr = dictionary;

			int offset_in_value_batch = -1;

			while(dictionary_itr != nullptr){
				for (auto value_batch_itr = 0; value_batch_itr < dictionary_itr->dictionary_batch_size; value_batch_itr++) {
					if(dictionary_itr->values[value_batch_itr] == number){
						offset_in_value_batch = value_batch_itr;
						break;
					}
				}
				if(offset_in_value_batch!=-1){
					break;
				}
				dictionary_itr = dictionary_itr->next;
			}

			if(dictionary_itr->column_2_offset_array[offset_in_value_batch] == nullptr){ //value was added from array 1
				offset_batch_entry* o = new offset_batch_entry();
				o->offsets[o->next_position] = array_2_itr;
				o->next_position++;
				dictionary_itr->column_2_offset_array[offset_in_value_batch] = o;
			}
			else{

				offset_batch_entry* offset_itr = dictionary_itr->column_2_offset_array[offset_in_value_batch];
				//find an empty slot in the offsets list
				while(offset_itr->next!=nullptr){
					if(offset_itr->next_position!=offset_itr->offset_batch_size){
						break;
					}
					offset_itr = offset_itr->next;
				}
				if(offset_itr->next_position != offset_itr->offset_batch_size){
					//we found an offset node with space in the array
					offset_itr->offsets[offset_itr->next_position] = array_2_itr;
					offset_itr->next_position++;
				} else {
					//create a new node
					offset_batch_entry* o = new offset_batch_entry();
					o->offsets[o->next_position] = array_2_itr;
					o->next_position++;
					offset_itr->next = o;
				}
			}
		}

	}
	return dictionary;
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

//print contents of dictionary which contain batch ENTRIES
void PrintDictionaryWithBatchEntries(dictionary_batch_entry* dictionary){
	 dictionary_batch_entry* dictionary_itr = dictionary;
	 while(dictionary_itr!=nullptr){
		 auto number_of_values = dictionary_itr->dictionary_batch_size == dictionary_itr->next_position? dictionary_itr->dictionary_batch_size : dictionary_itr-> next_position;
		 for (auto value_itr = 0; value_itr < number_of_values; value_itr++) {
			 if (dictionary_itr->column_1_offset_array[value_itr]==nullptr) {
				 	std::cout << "Value is not present in column 1" << std::endl;
			 } else {
				 std::cout << "Printing column 1 offsets for value " << dictionary_itr->values[value_itr] << std::endl;
				 offset_batch_entry* offset_itr = dictionary_itr->column_1_offset_array[value_itr];
				 while(offset_itr!=nullptr){
					 for (auto offset_array_itr = 0; offset_array_itr < (offset_itr->next_position < offset_itr->offset_batch_size ? offset_itr->next_position : offset_itr->offset_batch_size); offset_array_itr++) {
						 std::cout << offset_itr->offsets[offset_array_itr] << " ";
					 }
					 offset_itr=offset_itr->next;
				 }
				 std::cout << std::endl;
			 }

			 if (dictionary_itr->column_2_offset_array[value_itr]==nullptr) {
			 	 std::cout << "Value is not present in column 2" << std::endl;
			 } else {
				 std::cout << "Printing column 2 offsets for value " << dictionary_itr->values[value_itr] << std::endl;
 				offset_batch_entry* offset_itr = dictionary_itr->column_2_offset_array[value_itr];
 				while(offset_itr!=nullptr){
 					for (auto offset_array_itr = 0; offset_array_itr < (offset_itr->next_position < offset_itr->offset_batch_size ? offset_itr->next_position : offset_itr->offset_batch_size); offset_array_itr++) {
 						std::cout << offset_itr->offsets[offset_array_itr] << " ";
 					}
 					offset_itr=offset_itr->next;
 				}
 				std::cout << std::endl;
			 }

		 }

		 dictionary_itr = dictionary_itr->next;
	 }
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

void RunAlgorithm3(int* column_1, int column_1_size, int* column_2, int column_2_size){
	std::vector<std::pair<int,int>> matches;

	// ALGORITHM 3: TUPLE-CENTRIC JOIN (WITH INVERTED INDEX ON COLUMN_1)

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
	dictionary_entry* dictionary = BuildDictionary(column_1, column_1_size, column_2, column_2_size);
	dictionary_entry* dictionary_itr = dictionary;
	offset_entry* column_1_offset_itr = nullptr;
	offset_entry* column_2_offset_itr = nullptr;

	auto start = Time::now();

	while(dictionary_itr != nullptr){

		column_1_offset_itr = dictionary_itr->column_1_offset_array;
		while(column_1_offset_itr != nullptr){

			column_2_offset_itr = dictionary_itr->column_2_offset_array;
			while(column_2_offset_itr != nullptr){

				matches.push_back(std::make_pair(column_1_offset_itr->offset, column_2_offset_itr->offset));

				column_2_offset_itr = column_2_offset_itr->next;
			}
			column_1_offset_itr = column_1_offset_itr->next;
		}

		dictionary_itr = dictionary_itr->next;
	}

	auto stop = Time::now();
	auto elapsed = stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "VALUE-CENTRIC JOIN (DICTIONARY) (TYPE 1): " << time_milliseconds.count() << " ms \n";

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

	RunAlgorithm3(column_1, column_1_size, column_2, column_2_size);

	RunAlgorithm5(column_1, column_1_size, column_2, column_2_size);

	RunAlgorithm6(column_1, column_1_size, column_2, column_2_size);

	// Clean up arrays
	delete[] column_1;
	delete[] column_2;

}

} // End namespace emerald
