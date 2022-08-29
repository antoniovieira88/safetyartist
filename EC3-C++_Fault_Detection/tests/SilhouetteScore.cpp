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

void SilhouetteScore::ClustersSilhouette(Row<size_t> assigments, rowvec individualSilhouette, rowvec& clustersSilhouette) {
	int numberOfClusters = clustersSilhouette.n_cols;

	int clustersIterator = 0, numberOfPointsCluster = 0;

	double silhoutteScoreSumCluster = 0.0;

	for (clustersIterator = 0; clustersIterator < numberOfClusters; clustersIterator++) {
		Row<size_t> assignmentsTransformed = Row<size_t>(assigments);

		assignmentsTransformed.transform([clustersIterator](double label) {return (label == clustersIterator) ? 1 : 0; });

		numberOfPointsCluster = arma::sum(assignmentsTransformed);

		silhoutteScoreSumCluster = arma::dot(assignmentsTransformed, individualSilhouette);

		clustersSilhouette[clustersIterator] = silhoutteScoreSumCluster / numberOfPointsCluster;
	}


}

void SilhouetteScore::ClustersSilhouette(Row<size_t> assigments, rowvec individualSilhouette, rowvec& clustersSilhouette, rowvec& numberOfPointsPerCluster) {
	int numberOfClusters = clustersSilhouette.n_cols;

	int clustersIterator = 0, numberOfPointsCluster = 0;

	double silhoutteScoreSumCluster = 0.0;

	for (clustersIterator = 0; clustersIterator < numberOfClusters; clustersIterator++) {
		Row<size_t> assignmentsTransformed = Row<size_t>(assigments);

		assignmentsTransformed.transform([clustersIterator](double label) {return (label == clustersIterator) ? 1 : 0; });

		numberOfPointsCluster = arma::sum(assignmentsTransformed);

		silhoutteScoreSumCluster = arma::dot(assignmentsTransformed, individualSilhouette);

		clustersSilhouette[clustersIterator] = silhoutteScoreSumCluster / numberOfPointsCluster;
		numberOfPointsPerCluster[clustersIterator] = numberOfPointsCluster;
	}


}