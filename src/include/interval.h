#pragma once
#include <functional>

namespace emerald
{
    class Interval {
        private:
            int start_;
            int end_;
            int size_;
        public:
            Interval();
            Interval(int start, int end);
            bool operator<(const Interval& interval) const;
            bool operator==(const Interval& interval) const;
            int get_start() const;
            void print() const;
            int get_end() const;
            int get_size() const;
    };
} // emerald

namespace std{
    template<> 
    struct hash<emerald::Interval>{
        std::size_t operator()(const emerald::Interval& interval) const {
            return std::hash<int>()(interval.get_start()) ^ (std::hash<int>()(interval.get_end()) << 1);
        }
    };
}


