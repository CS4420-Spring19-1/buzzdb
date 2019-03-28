#pragma once 
#include "interval.h"
#include <map>
#include <vector>

namespace emerald
{
    class IntervalIndex {
        private:
            std::map<Interval, std::vector<int>> index_;
        public:
            IntervalIndex();
            std::map<Interval, std::vector<int>> get_index() const;
            void append_index(std::map<Interval, std::vector<int>> index);
    };
} // emerald
