#pragma once

#include "table_descriptor.h"
#include "tuple.h"
#include <unordered_map>

namespace emerald {
    class HeapFile : public DBFile{
        public:
            HeapFile();

            HeapFile(FILE* file, tuple_descriptor desc);

            virtual ~HeapFile();

            FILE* getFile();

            uint32_t getId();

            tuple_descriptor getTupleDesc();

            Page readPage(PageId pid);

            void writePage(Page page);

            int numPages();

            std::vector<Page> addTuple(transactionid tid, tuple t);

            Page deleteTuple(transactionid tid, tuple t);

            DBFileIterator iterator(transactionid tid);



        private:
            FILE* file;
            tuple_descriptor desc;     
    };
};