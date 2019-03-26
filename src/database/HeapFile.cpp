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
#include "HeapFile.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "summary_list.h"
#include "column_store.h"
#include <math.h>       /* ceil */

namespace emerald {
    HeapFile::HeapFile(FILE* file, tuple_descriptor desc){
        this->file = file;
        this->desc = desc;
    }


    FILE* HeapFile::getFile(){
        return file;
    }

    uint32_t HeapFile::getId(){
        return reinterpret_cast<uint32_t>(file);
    }

    tuple_descriptor HeapFile::getTupleDesc(){
        return desc;
    }

    Page HeapFile::readPage(PageId pid){

    }

    void HeapFile::writePage(Page page){

    }

    int HeapFile::numPages(){
        return (int)ceil(ftell(file)/BufferPool.getPageSize());
    }

    std::vector<Page> HeapFile::addTuple(transactionid tid, tuple t){

    }

    Page HeapFile::deleteTuple(transactionid tid, tuple t){

    }

    DBFileIterator HeapFile::iterator(transactionid tid){
        DBFileIterator iterator = new HeapFileIterator(tid, this);
        return iterator;
    }


} // emerald
