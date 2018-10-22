// ZIPFIAN HEADER

#pragma once

#include <cstdint>

#include "fast_random.h"

namespace emerald {

class fast_random;

class ZipfDistribution{

public:

	ZipfDistribution(const uint64_t& n, const double& theta);

	int GenerateInteger(const int &min, const int &max);

	uint64_t GetNextNumber();

	uint64_t the_n;
	double zipf_theta;
	double denom;
	double zeta_2_theta;
	fast_random rand_generator;
};


}  // End emerald namespace
