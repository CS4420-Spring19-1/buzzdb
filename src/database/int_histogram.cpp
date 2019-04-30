
#include "int_histogram.h"


namespace emerald {

    IntHistogram::IntHistogram(int bucketSize, int min, int max) {
        this->bucketsNum = bucketSize;
        this->min = min;
        this->max = max;
        this->buckets = new int[this->bucketsNum];
        for(int i=0;i<this->bucketsNum;i++){
            this->buckets[i] = 0;
        }
        
        this->width = ((double)(this->max-this->min))/this->bucketsNum;
        this->totalNum = 0;
    }


    void IntHistogram::addValue(int v) {
    	this->buckets[getBucketIndex(v)] += 1;
    	this->totalNum += 1;
    }

    int IntHistogram::getBucketIndex(int v){
    	if(v>=this->max)  return this->bucketsNum-1;
    	else if(v<this->min)  return 0;
    	
    	double bucketIndexD = ((double)(v-this->min))/this->width;
    	int bucketIndex = (int)bucketIndexD;
    	return bucketIndex;
    }
   
    double IntHistogram::estimateSelectivity(OpType op, int v) {
    	if(op==EQUALS){
    		if(v>this->max || v<this->min)  return 0.0;
    		return (double)buckets[getBucketIndex(v)]/width/totalNum;
    	}
    	else if(op==NOT_EQUALS){
    		if(v>this->max || v<this->min) return 1.0;
    		return 1-(double)buckets[getBucketIndex(v)]/width/totalNum;
    	}
    	else if(op==GREATER_THAN || op==GREATER_THAN_OR_EQUAL ){
    		if(v>this->max) return 0.0;
    		else if(v<=this->min) return 1.0; 
    		
    		double selectivity = 0;
    		
    		double b_part = b_partCalc(v,op);
    		double b_f = (double)buckets[getBucketIndex(v)]/totalNum;
    		selectivity += b_part * b_f;
    		
    		int count = 0;
    		for(int i=getBucketIndex(v)+1;i<bucketsNum;i++){
    			count += buckets[i];
    		}
    		selectivity += (double)count/totalNum;
    		return selectivity;
    	}
    	else if(op==LESS_THAN || op==LESS_THAN_OR_EQUAL ){
    		if(v<this->min)  return 0.0;
    		else if(v>=this->max)  return 1.0; 
    		
    		double selectivity = 0;
    		
    		double b_part = b_partCalc(v,op);
    		
    		double b_f = (double)buckets[getBucketIndex(v)]/totalNum;
    		selectivity += b_part * b_f;
    		
    		int count = 0;
    		for(int i=getBucketIndex(v)-1;i>=0;i--){
    			count += buckets[i];
            }
    		selectivity += (double)count/totalNum;
    		return selectivity;
    	}

        return -1.0;

    }
    
    double IntHistogram::b_partCalc(int v, OpType op){
    	double lower = min + getBucketIndex(v)*width;
		double upper = lower + width;
		
		double totalInt = floor(upper)-ceil(lower)+1;
		double coveredInt = 0;
		
    	if(op==LESS_THAN_OR_EQUAL)
    		coveredInt = v-ceil(lower)+1;
    	else if(op==LESS_THAN)
    		coveredInt = v-ceil(lower);
    	else if(op==GREATER_THAN)
    		coveredInt = floor(upper)-v;
    	else if(op==GREATER_THAN_OR_EQUAL)
    		coveredInt = floor(upper)-v+1;
    	
    	return coveredInt/totalInt;
    }
   
    /**
     * @return A string describing this histogram, for debugging purposes
     */
    // std::string IntHistogram::toString() {
    //     std::string desc = "bucketsNum: " + bucketsNum + ", min: " + min + ", max: " + max;
    //     return desc;
    // }

}