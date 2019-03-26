#pragma once

#include "table_descriptor.h"
#include "tuple.h"
#include <unordered_map>

namespace emerald {
    class HeapFileEncoder {
        public:
            HeapFileEncoder();

            virtual ~HeapFileEncoder();

            static void convert(std::vector<<std::vector<int>> tuples, FILE* outFile, int npagebytes, int numFields);

            static void convert(FILE* inFile, FILE* outFile, int npagebytes, int numFields);

            static void convert(FILE* inFile, FILE* outFile, int npagebytes, int numFields, types[] typeAr);

            static void convert(FILE* inFile, FILE* outFile, int npagebytes, int numFields, types[] typeAr, char fieldSeparator);



        private:


    };
};