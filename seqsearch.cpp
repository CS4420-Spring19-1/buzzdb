#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;


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
    std::vector<int> testvec1 = generateData(100000);
    std::vector<int> testvec2 = generateData(100000);
    auto stop = std::chrono::high_resolution_clock::now();

    //Initialize output into a csv file
    std::ofstream output_file;
    output_file.open("Output.csv"); //Open file
    output_file << " Random number generation , Joining \n";

    //Elapsed time
    std::chrono::duration<double> elapsed = stop - start;
    output_file << elapsed.count() << ","; //Output time to csv

    int j=0,k=0;

    start = std::chrono::high_resolution_clock::now();
    for(j=0;j<100000;j++)
    {
        for(k=0;k<100000;k++)
        {
            if (testvec1[j] == testvec2[k])
            {
            std::cout << "<" << j << "," << k << "> \n";  //Position
            }
            else
            {
                continue;
            }
        }
    }


    stop = std::chrono::high_resolution_clock::now();
    elapsed = stop - start;
    output_file << elapsed.count() << ",\n"; //Output time to csv
    output_file.close(); //Close file

    return 0;
}

