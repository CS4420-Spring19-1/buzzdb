#include "database.h"
#include "table.h"
#include "field.h"
#include "integer_field.h"
#include "string_field.h"
#include "double_field.h"
#include "date_field.h"
#include "row_store.h"
#include "tuple.h"
#include "utility.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "summary_list.h"
#include "column_store.h"

namespace emerald {
    HeapFileEncoder::HeapFileEncoder();

    static void HeapFileEncoder::convert(std::vector<<std::vector<int>> tuples, FILE* outFile, int npagebytes, int numFields){}

    static void HeapFileEncoder::convert(FILE* inFile, FILE* outFile, int npagebytes, int numFields){}

    static void HeapFileEncoder::convert(FILE* inFile, FILE* outFile, int npagebytes, int numFields, types[] typeAr){}

    static void HeapFileEncoder::convert(FILE* inFile, FILE* outFile, int npagebytes, int numFields, types[] typeAr, char fieldSeparator){}


} // emerald
