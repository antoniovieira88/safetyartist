#include "./include/SilhouetteScore.h"
#include <mlpack/core.hpp>
#include <mlpack/core/cv/metrics/silhouette_score.hpp>
#include <string>

using namespace mlpack;
rowvec SilhouetteScore::Individually(arma::mat data, arma::u64_rowvec assignments) {
	metric::EuclideanDistance EuclideanD;

	return cv::SilhouetteScore::SamplesScore(data, assignments, EuclideanD);
}

rowvec SilhouetteScore::Individually(mat data, u64_rowvec assignments, std::string distanceMetric)
{
	metric::ManhattanDistance manhattanD;
	metric::SquaredEuclideanDistance sqEuclideanD;

	if (distanceMetric == "manhattan") {
		return cv::SilhouetteScore::SamplesScore(data, assignments, manhattanD);
	}

	else if (distanceMetric == "squared") {
		return cv::SilhouetteScore::SamplesScore(data, assignments, sqEuclideanD);
	}

	return Individually(data, assignments);
}

double SilhouetteScore::Overall(arma::mat data, arma::u64_rowvec assignments) {
	metric::EuclideanDistance EuclideanD;

	return cv::SilhouetteScore::Overall(data, assignments, EuclideanD);
}

double SilhouetteScore::Overall(mat data, u64_rowvec assignments, std::string distanceMetric)
{
	metric::ManhattanDistance manhattanD;
	metric::SquaredEuclideanDistance sqEuclideanD;

	if (distanceMetric == "manhattan") {
		return cv::SilhouetteScore::Overall(data, assignments, manhattanD);
	}

	else if (distanceMetric == "squared") {
		return cv::SilhouetteScore::Overall(data, assignments, sqEuclideanD);
	}

	return Overall(data, assignments);
}

