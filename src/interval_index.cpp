#include "interval_index.h"

namespace emerald
{
    IntervalIndex::IntervalIndex(){}

    std::map<Interval, std::vector<int>> IntervalIndex::get_index() const{
        return index_;
    }

    void IntervalIndex::append_index(std::map<Interval, std::vector<int>> index) {
        index_.insert(index.begin(), index.end());
    }
} // emerald
