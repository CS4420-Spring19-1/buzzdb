#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;


struct RandomGenerator {
    int maxValue;
    RandomGenerator(int max) :
            maxValue(max) {
    }

    int operator()() {
        return rand() % maxValue;
    }
};

std::vector<int> generateData(unsigned int count){
    std:: vector<int> testvec;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis1(1, 10);
    unsigned int i;

    //for half the data, sample from 0-10
    for(i=0; i < count/2; i++){
      testvec.push_back(dis1(gen));
     }

    //for next half, sample from 10-100
    std::uniform_int_distribution<> dis2(11, 100);
    for(i=0; i<count; i++){
        testvec.push_back(dis2(gen));
    }
    for (int val: testvec)
       std::cout << val << std::endl;
    return testvec;
}


int main() {


    // Initialize 2 vectors with 1M ints
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> testvec1 = generateData(1000000);
    std::vector<int> testvec2 = generateData(1000000);
    auto stop = std::chrono::high_resolution_clock::now();

    //Initialize output into a csv file
    std::ofstream output_file;
    output_file.open("Output.csv"); //Open file
    output_file << " Random number generation , Joining \n";

    //Elapsed time
    std::chrono::duration<double> elapsed = stop - start;
    output_file << elapsed.count() << ","; //Output time to csv

    int j=0,k=0;

    //Find the required value
    std::vector<int>::iterator it1;
    std::vector<int>::iterator it2;

    int result1, result2;

    start = std::chrono::high_resolution_clock::now();
    for(j=0;j<1000000;j++)
    {
        it1 = find (testvec1.begin(), testvec1.end(),testvec1.at(j));
        for(k=0;k<1000000;k++)
        {
            it2 = find (testvec2.begin(), testvec2.end(),testvec2.at(j));
            if (testvec1.at(j) == testvec2.at(k))
            {
            result1= distance(testvec1.begin(), it1);
            result2= distance(testvec2.begin(), it2);
            std::cout << "<" << result1 << "," << result2 << "> \n";  //Position
            }
            else
            {
                break;
            }
        }
    }


    stop = std::chrono::high_resolution_clock::now();
    elapsed = stop - start;
    output_file << elapsed.count() << ",\n"; //Output time to csv
    output_file.close(); //Close file

    return 0;
}

