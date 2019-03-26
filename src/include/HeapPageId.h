#pragma once

#include "table_descriptor.h"
#include "tuple.h"
#include <unordered_map>

namespace emerald {
    class HeapPageId : public PageId{
        public:
            
            HeapPageId();

            HeapPageId(int table_id, int pageNo);

            virtual ~HeapPageId();

            int getTableId();

            int getPageNo();

            int getHashCode();

            bool equals(HeapPageId heapPageid);

            std::vector<int> serialize();

            
        private:
            int table_id;
            int pageNo;

    };
};