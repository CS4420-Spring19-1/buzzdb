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
#include "inverted_index.h"

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

std::pair<int, int> findFilterRange(int column_range){
	std::uniform_int_distribution<int> lower_bound(1,column_range/2);
	//int min = lower_bound(generator);
	//std::uniform_int_distribution<int> upper_bound(column_range/2+1, column_range);
	//int max = upper_bound(generator);

	return std::make_pair(1000, 2000);

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

	// ALGORITHM 2: VALUE-CENTRIC JOIN (SINGLE INVERTED INDEX)

	// Build tree for value-centric join
	auto tree = BuildTree(column_1, column_1_size);

	auto start = Time::now();

	for(int column_2_itr = 0; column_2_itr < column_2_size; column_2_itr++){
		auto value = column_2[column_2_itr];

		auto column_1_entry = tree.find(value);
		if (column_1_entry!= tree.end()) {
			auto column_1_offsets = column_1_entry->second;
			for(auto column_1_offset: column_1_offsets){
				matches.push_back(std::make_pair(column_1_offset, column_2_itr));
			}
		}
	}

	auto stop = Time::now();
	auto elapsed = stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "VALUE-CENTRIC JOIN (SINGLE INVERTED INDEX): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);
}

void RunAlgorithm3(int* column_1, int column_1_size, int* column_2, int column_2_size){

	// ALGORITHM 3: VALUE-CENTRIC JOIN (TWO INVERTED INDEXES)

	InvertedIndex *inverted_index_1 = new InvertedIndex(column_1, column_1_size);
	InvertedIndex *inverted_index_2 = new InvertedIndex(column_2, column_2_size);

	auto index_1 = inverted_index_1->getInvertedIndex();
	auto index_2 = inverted_index_2->getInvertedIndex();

		auto start = Time::now();

		InvertedIndex *result_index = new InvertedIndex();

		for(auto column_2_itr : index_2){
			auto column_2_offsets = column_2_itr.second;

			auto column_1_entry = index_1.find(column_2_itr.first);
			if ( column_1_entry!= index_1.end()) {
				auto column_1_offsets = column_1_entry->second;

				std::vector<std::vector<int>> matched_offsets;
				for(auto column_2_offset: column_2_offsets){
					for(auto column_1_offset: column_1_offsets){
						std::vector<int> match;
						match.insert(match.end(), column_2_offset.begin(), column_2_offset.end());
						match.insert(match.end(), column_1_offset.begin(), column_1_offset.end());
						matched_offsets.push_back(match);
					}
				}
				KeyVector key_vector;
				key_vector.append(column_2_itr.first);
				key_vector.append(column_1_entry->first);
				result_index->insert(key_vector, matched_offsets);
			}
		}

		auto stop = Time::now();
		auto elapsed = stop - start;
		auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
		std::cout << "VALUE-CENTRIC JOIN (TWO INVERTED INDEXES): " << time_milliseconds.count() << " ms \n";
		std::cout << "MATCHES: " << result_index->matches() << " \n";


}

void RunAlgorithm4(int* column_1, int column_1_size, int* column_2, int column_2_size){

	// ALGORITHM 4: VALUE-CENTRIC JOIN (TWO INVERTED INDEXES) (SORT-MERGE)

	InvertedIndex *inverted_index_1 = new InvertedIndex(column_1, column_1_size);
	InvertedIndex *inverted_index_2 = new InvertedIndex(column_2, column_2_size);

	auto index_1 = inverted_index_1->getInvertedIndex();
	auto index_2 = inverted_index_2->getInvertedIndex();

	auto index_1_itr = index_1.begin();
	auto index_2_itr = index_2.begin();

	auto start = Time::now();
	InvertedIndex *result_index = new InvertedIndex();
	while (index_1_itr != index_1.end() && index_2_itr != index_2.end()) {
		if (index_1_itr->first == index_2_itr->first) {
			auto column_1_offsets = index_1_itr->second;
			auto column_2_offsets = index_2_itr->second;
			std::vector<std::vector<int>> matched_offsets;
			for(auto column_2_offset: column_2_offsets){
				for(auto column_1_offset: column_1_offsets){
					std::vector<int> match;
					match.insert(match.end(), column_2_offset.begin(), column_2_offset.end());
					match.insert(match.end(), column_1_offset.begin(), column_1_offset.end());
					matched_offsets.push_back(match);
				}
			}
			KeyVector key_vector;
			key_vector.append(index_1_itr->first);
			key_vector.append(index_2_itr->first);
			result_index->insert(key_vector, matched_offsets);
			index_1_itr++;
			index_2_itr++;
		} else if(index_1_itr->first < index_2_itr->first){
			index_1_itr++;
		} else {
			index_2_itr++;
		}
	}

	auto stop = Time::now();
	auto elapsed = stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "VALUE-CENTRIC JOIN (TWO INVERTED INDEXES) (SORT-MERGE): " << time_milliseconds.count() << " ms \n";
	std::cout << "MATCHES: " << result_index->matches() << " \n";

}

void RunAlgorithm5(int * column_1, int column_1_size, std::pair<int, int> range){
	std::vector<int> matches;
	auto start = Time::now();
	//TUPLE CENTRIC FILTER
	for (auto column_1_itr = 0; column_1_itr < column_1_size; column_1_itr++) {
		if(column_1[column_1_itr]>=range.first && column_1[column_1_itr]<=range.second){
			matches.push_back(column_1_itr);
		}
	}
	auto stop = Time::now();
	auto elapsed = stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "TUPLE CENTRIC FILTER : " << time_milliseconds.count() << " ms \n";
	std::cout << "MATCHES: " << matches.size() << std::endl;
}

void RunAlgorithm6(int * column_1, int column_1_size, std::pair<int, int> range){
	/*std::vector<int> matches;

	auto tree = BuildTree(column_1, column_1_size);

	//VALUE CENTRIC FILTER
	auto start = Time::now();
	auto lower_bound = tree.lower_bound(range.first);
	auto upper_bound = tree.upper_bound(range.second);

	while (lower_bound != upper_bound) {
		auto column_1_offsets = lower_bound->second;
		matches.insert(matches.end(), column_1_offsets.begin(), column_1_offsets.end());
		lower_bound++;
	}

	auto stop = Time::now();
	auto elapsed = stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "VALUE CENTRIC FILTER : " << time_milliseconds.count() << " ms \n";
	std::cout << "MATCHES: " << matches.size() << std::endl;*/

	InvertedIndex* inverted_index = new InvertedIndex(column_1, column_1_size);
	std::map<KeyVector, std::vector<std::vector<int>>> index = inverted_index->getInvertedIndex();
	//inverted_index->print();

	auto start = Time::now();

	InvertedIndex* result_index = new InvertedIndex();

	KeyVector lower_bound_key(range.first);
	KeyVector upper_bound_key(range.second);
	auto lower_bound = index.lower_bound(lower_bound_key);
	auto upper_bound = index.upper_bound(upper_bound_key);

	while (lower_bound != upper_bound) {
		auto column_1_offsets = lower_bound->second;
		result_index->insert(lower_bound->first, lower_bound->second);
		lower_bound++;
	}

	auto stop = Time::now();
	auto elapsed = stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "VALUE CENTRIC FILTER : " << time_milliseconds.count() << " ms \n";
	//result_index->print();
	std::cout << "MATCHES: " << result_index->matches() << std::endl;
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

	//frequency maps
	std::map<int, int>column_1_freq_map;
	std::map<int, int>column_2_freq_map;

	// Load data into first column--without selectivity for algo 1-4

  	if(state.algorithm_type >= 1 && state.algorithm_type <= 4){
			for(int column_1_itr = 0; column_1_itr < column_1_size; column_1_itr++){
		  		auto number = zipf1.GetNextNumber();
				column_1[column_1_itr] = number;
				column_1_set.insert(number);
				//std::cout << number << " ";

				//calculate frequencies
	                	if(column_1_freq_map.count(number)){
					column_1_freq_map[number]++;
				}else{
					column_1_freq_map[number] = 1;
				}
			}

			std::cout << "COLUMN 1 SET SIZE: " << column_1_set.size() << "\n";

			//calculate number of matches with selectivity formula -- may be wrong
			int num_matches = state.join_selectivity_threshold * (column_1_size + column_2_size);
	        	std::default_random_engine generator(seed);
			std::uniform_int_distribution<int> picking_column_2_num(0, column_1_set.size());
			int cur_matches = 0;
	        	//save column 1's set in an array
	        	int index = 0;
	        	int values_col_1[column_1_set.size()];
			std::set<int>::iterator itr;
	        	for(itr = column_1_set.begin(); itr != column_1_set.end(); ++itr){
				values_col_1[index] = *itr;
				index++;
	        	}
			int column_2_index = 0;
	        	while((cur_matches < num_matches) && (column_2_index < column_2_size)){
		 		auto index = picking_column_2_num(generator);
				int value = values_col_1[index];
				column_2[column_2_index] = values_col_1[index];
				cur_matches += column_1_freq_map[value];
				column_2_index++;
	 			column_2_set.insert(value);
			}
			for(int column_2_itr = column_2_index; column_2_itr < column_2_size; column_2_itr++){
				auto number = zipf2.GetNextNumber();
				while(column_1_set.find(number) != column_1_set.end()){ // can this every be infinite?
					number = zipf2.GetNextNumber();
				}
				column_2[column_2_itr] = number;
				column_2_set.insert(number);
				// Load data into second column
			}
			std::cout << "COLUMN 2 SET SIZE: " << column_2_set.size() << "\n";
	}


	std::pair<int, int> range = findFilterRange(state.range);

	if(state.algorithm_type >= 5){
		int num_matches = state.join_selectivity_threshold * (column_1_size);
		for(int column_1_itr = 0; column_1_itr < num_matches; column_1_itr++){
			int number = zipf1.GetNextNumber();
			while(number < range.first || number > range.second){
				number = zipf1.GetNextNumber();
  			}
			column_1[column_1_itr] = number;
			column_1_set.insert(number);
		}
		for(int column_1_itr = num_matches; column_1_itr < column_1_size; column_1_itr++){
		        int number = zipf1.GetNextNumber();
                        while(number >= range.first &&  number <= range.second){
                                number = zipf1.GetNextNumber();
                        }
                        column_1[column_1_itr] = number;
                        column_1_set.insert(number);
		}
		std::cout << "COLUMN 1 SET SIZE: " << column_1_set.size() << "\n";
	//	PrintArray(column_1, column_1_size);
	}

	// RUN ALGORITHMS

	//RunAlgorithm1(column_1, column_1_size, column_2, column_2_size);

	switch (state.algorithm_type) {
	case ALGORITHM_TYPE_TUPLE_CENTRIC_INVERTED_INDEX: {
		RunAlgorithm1(column_1, column_1_size, column_2, column_2_size);
		break;
	}
	case ALGORITHM_TYPE_VALUE_CENTRIC_SINGLE_INDEX: {
		RunAlgorithm2(column_1, column_1_size, column_2, column_2_size);
		break;
	}
	case ALGORITHM_TYPE_VALUE_CENTRIC_TWO_INDEXES:{
		RunAlgorithm3(column_1, column_1_size, column_2, column_2_size);
		break;
	}
	case ALGORITHM_TYPE_VALUE_CENTRIC_TWO_INDEXES_SORT_MERGE:{
		RunAlgorithm4(column_1, column_1_size, column_2, column_2_size);
		break;
	}
	case ALGORITHM_TYPE_TUPLE_CENTRIC_FILTER:{
		RunAlgorithm5(column_1, column_1_size, range);
		break;
	}
	case ALGORITHM_TYPE_VALUE_CENTRIC_FILTER:{
		RunAlgorithm6(column_1, column_1_size, range);
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
