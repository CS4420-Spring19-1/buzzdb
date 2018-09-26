#include<iostream>
#include<unordered_map>
#include<vector>
#include<random>
#include <fstream>
#include <chrono>

#define MAX_ROWS 1000 * 10

struct eleIndex {
	int rowNum;
	struct eleIndex * next;
};

void buildIndex(std::vector<int> table, std::unordered_map<int, struct eleIndex *> &index){
	for (int i=0; i<MAX_ROWS; i++)
	{
		int value = table[i];
		try{
			struct eleIndex * tmp = index.at(value);
			struct eleIndex * row = (struct eleIndex *)malloc(sizeof(struct eleIndex));
			row->rowNum = i;
			row->next = tmp;
			index[value] = row;
		}catch(const std::out_of_range &e){
			struct eleIndex * row = (struct eleIndex *)malloc(sizeof(struct eleIndex));
			row->rowNum = i;
			row->next = NULL;
			index[value] = row;
		}
	}
}

std::vector<int> generateData(unsigned int count){
	std:: vector<int> table;
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis1(1, 10);
	unsigned int i;
	//for half the data, sample from 0-10
	for(i=0; i < count/2; i++){
		table.push_back(dis1(gen));
	}

	//for next half, sample from 10-100
	std::uniform_int_distribution<> dis2(1, 100);
	for(; i<count; i++){
		table.push_back(dis2(gen));
	}
	return table;
}

int main(int argc, char const *argv[])
{
	std::ofstream output_file;
	output_file.open("output.csv");
	output_file << "test no, index generation T1, index generation T2, Join\n";
	for(int i=0; i<3; i++){
		std::cout << "\nexecuting" <<std::endl;
		output_file << i << ",";

		std::vector<int> t1 = generateData(MAX_ROWS);
		std::vector<int> t2 = generateData(MAX_ROWS);

		std::unordered_map<int, struct eleIndex *> indexT1;
		std::unordered_map<int, struct eleIndex *> indexT2;	

		auto start = std::chrono::high_resolution_clock::now();
		buildIndex(t1, indexT1);
		auto stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = stop - start;
		output_file << elapsed.count() << ",";

		start = std::chrono::high_resolution_clock::now();
		buildIndex(t2, indexT2);
		stop = std::chrono::high_resolution_clock::now();
		elapsed = stop - start;
		output_file << elapsed.count() << ",";

		std::cout<< "\njoining" << std::endl;
		std::vector<std::pair<int,int>> matches;

		start = std::chrono::high_resolution_clock::now();
		for(auto &x:indexT1){
			unsigned int value = x.first;
			try{
				struct eleIndex * list2 = indexT2.at(value);
				struct eleIndex * list1 = x.second;

				struct eleIndex * tmp = list1;
				while(tmp!=NULL){
					struct eleIndex * tmp1 = list2;
					while(tmp1!=NULL){
						matches.push_back(std::make_pair(tmp->rowNum, tmp1->rowNum));
						tmp1=tmp1->next;
					}
					tmp = tmp->next;
				}

			}
			catch(const std::out_of_range &e){ //if that value is not present in T2
				continue;
			}
		}
		stop = std::chrono::high_resolution_clock::now();
		elapsed = stop - start;
		output_file << elapsed.count() << ",\n";

		std::cout << "MATCHES: " << matches.size();

	}
	output_file.close();
	return 0;
	
}
