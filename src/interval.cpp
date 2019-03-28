#include "interval.h"
#include <iostream>

namespace emerald
{
    Interval::Interval(int start, int end){
        start_ = start;
        end_ = end;
        size_ = end-start+1;
    }

    bool Interval::operator<(const Interval& interval) const{
        if(size_ != interval.get_size()){
            return size_ < interval.get_size();
        } else if(start_ != interval.get_start()){
            return start_ < interval.get_start();
        } else {
            return end_ < interval.get_end();
        }
        
    }

    int Interval::get_start() const {
        return start_;
    }

    int Interval::get_end() const {
        return end_;
    }

    void Interval::print() const{
        std::cout << "Start=" << start_ << ", End=" << end_;
    }

    bool Interval::operator==(const Interval& interval) const{
        return start_==interval.get_start() && end_==interval.get_end();
    }

    int Interval::get_size() const {
        return size_;
    }

} // emerald
