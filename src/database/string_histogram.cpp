
#include "string_histogram.h"
#include <string>

namespace emerald {
    StringHistogram::StringHistogram(int buckets) {
        hist = new IntHistogram(buckets, minVal(), maxVal());
    }

    /** Convert a string to an integer, with the property that 
        if the return value(s1) < return value(s2), then s1 < s2
    */
    int StringHistogram::stringToInt(std::string s) {
        int i ;
        int v = 0;
        for (i = 3; i >= 0;i--) {
            if (s.length() > 3-i) {
                int ci = (int)s.at(3-i);
                v += (ci) << (i * 8);
            } 
        }
        
        // XXX: hack to avoid getting wrong results for
        // strings which don't output in the range min to max
        if (!((s== "") || s == "zzzz")) {
	        if (v < minVal()) {
	        	v = minVal();
	        } 
	        
	        if (v > maxVal()) {
	        	v = maxVal();
	        }
        }
        
        return v;
    }

    /** @return the maximum value indexed by the histogram */
    int StringHistogram::maxVal() {
        return stringToInt("zzzz");
    }

    /** @return the minimum value indexed by the histogram */
    int StringHistogram::minVal() {
        return stringToInt("");
    }

    /** Add a new value to thte histogram */
    void StringHistogram::addValue(std::string s) {
        int val = stringToInt(s);
        hist->addValue(val);
    }

    /** Estimate the selectivity (as a double between 0 and 1) of the specified predicate over the specified string 
        @param op The operation being applied
        @param s The string to apply op to 
    */
    double StringHistogram::estimateSelectivity(IntHistogram::OpType op, std::string s) {
        int val = stringToInt(s);
        return hist->estimateSelectivity(op, val);
    }
}
