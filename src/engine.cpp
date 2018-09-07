/* A simple program that computes the square root of a number*/
#include <math.h>

#include "engine.h"
#include "configuration.h"

namespace engine{

configuration state;

double square_root(double input_number){
    return sqrt(input_number);
}

} // End namespace engine
