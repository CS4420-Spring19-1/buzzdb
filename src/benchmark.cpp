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

std::pair<int, int> findFilterRange(int column_range){
	std::uniform_int_distribution<int> lower_bound(1,column_range/2);
	int min = lower_bound(generator);
	std::uniform_int_distribution<int> upper_bound(column_range/2+1, column_range);
	int max = upper_bound(generator);

	return std::make_pair(min, max);

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
// FILTERS
////////////////////////////////////////////////////////////////////////////////////////////

/*
int TupleFilter(int *farray){
  int minrange,maxrange;
  std::vector<int> foutarray;
  std::cout <<"Enter the min range:";
  std::cin>>minrange;
  std::cout<<"Enter max range:";
  std::cin>>maxrange;
  farray_size= farray.size();
  //Traverse over the vector
  for(int itr=0, itr<farray_size, itr++){
    //Find values in the range
    if(farray[itr]>minrange && farray[itr]<maxrange){
      foutarray.push_back(farray[itr]);
    }
  }
  return foutarray;
}

int ValueFilter(std::vector<K> & vec, std::map<K, V> mapOfElemen)
{
  std::vector<int> voutarray;
  int minrange,maxrange;
  std::cout <<"Enter the min range:";
  std::cin>>minrange;
  std::cout<<"Enter max range:";
  std::cin>>maxrange;
  auto vitr = mapOfElemen.find(minrange);
  // Iterate through the map
  while(vitr != mapOfElemen.find(maxrange))
  {
      voutarray.push_back(vitr->first);
    }
    // Go to next entry in map
    vitr++;
  }
  return voutarray;
}
*/


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
	std::vector<std::pair<int,int>> matches;

	// ALGORITHM 3: VALUE-CENTRIC JOIN (TWO INVERTED INDEXES)

	// Build tree for value-centric join
	auto tree_1 = BuildTree(column_1, column_1_size);
	auto tree_2 = BuildTree(column_2, column_2_size);

	auto start = Time::now();

	for(auto column_2_itr : tree_2){
		auto column_2_offsets = column_2_itr.second;

		auto column_1_entry = tree_1.find(column_2_itr.first);
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
	std::cout << "VALUE-CENTRIC JOIN (TWO INVERTED INDEXES): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);

}

void RunAlgorithm4(int* column_1, int column_1_size, int* column_2, int column_2_size){
	std::vector<std::pair<int,int>> matches;

	// ALGORITHM 4: VALUE-CENTRIC JOIN (TWO INVERTED INDEXES) (SORT-MERGE)

	// Build tree for value-centric join
	auto tree_1 = BuildTree(column_1, column_1_size);
	auto tree_2 = BuildTree(column_2, column_2_size);

	auto column_1_itr = tree_1.begin();
	auto column_2_itr = tree_2.begin();

	auto start = Time::now();

	while (column_1_itr != tree_1.end() && column_2_itr != tree_2.end()) {
		if (column_1_itr->first == column_2_itr->first) {
			auto column_1_offsets = column_1_itr->second;
			auto column_2_offsets = column_2_itr->second;
			for(auto column_2_offset: column_2_offsets){
				for(auto column_1_offset: column_1_offsets){
					matches.push_back(std::make_pair(column_1_offset, column_2_offset));
				}
			}
			column_1_itr++;
			column_2_itr++;
		} else if(column_1_itr->first < column_2_itr->first){
			column_1_itr++;
		} else {
			column_2_itr++;
		}
	}

	auto stop = Time::now();
	auto elapsed = stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "VALUE-CENTRIC JOIN (TWO INVERTED INDEXES) (SORT-MERGE): " << time_milliseconds.count() << " ms \n";

	PrintMatches(matches, column_1, false);
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
	std::vector<int> matches;

	auto tree = BuildTree(column_1, column_1_size);

	auto start = Time::now();

	//VALUE CENTRIC FILTER

	auto lower_bound = tree.lower_bound(range.first);
	auto upper_bound = tree.upper_bound(range.second);

	while (lower_bound != upper_bound) {
		auto column_1_offsets = lower_bound->second;
		for (auto column_1_offset: column_1_offsets) {
			matches.push_back(column_1_offset);
		}
		lower_bound++;
	}

	auto stop = Time::now();
	auto elapsed = stop - start;
	auto time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	std::cout << "VALUE CENTRIC FILTER : " << time_milliseconds.count() << " ms \n";
	std::cout << "MATCHES: " << matches.size() << std::endl;
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

	if (state.algorithm_type >=1 && state.algorithm_type <=4) {  //In order to reduce memory used
		// Load data into second column
		for(int column_2_itr = 0; column_2_itr < column_2_size; column_2_itr++){
			auto number = zipf2.GetNextNumber();
			column_2[column_2_itr] = number;
			column_2_set.insert(number);
			//std::cout << number << " ";
		}
		std::cout << "COLUMN 2 SET SIZE: " << column_2_set.size() << "\n";
	}

	std::pair<int, int> range = findFilterRange(state.range);
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
