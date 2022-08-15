#pragma once
#include <mlpack/core.hpp>

#include <string>

using namespace arma;

class SilhouetteScore
{
public:

	static rowvec Individually(mat data, u64_rowvec assignments);

	static double Overall(mat data, u64_rowvec assignments);

	static rowvec Individually(mat data, u64_rowvec assignments, std::string distanceMetric);

	static double Overall(mat data, u64_rowvec assignments, std::string distanceMetric);

};

