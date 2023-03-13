#include "./include/SilhouetteScore.h"
#include <mlpack/core.hpp>
#include <mlpack/core/cv/metrics/silhouette_score.hpp>
#include <string>

using namespace std;

arma::rowvec SilhouetteScoreEC::Individually(arma::mat data, arma::u64_rowvec assignments) {
	mlpack::EuclideanDistance EuclideanD;

	return mlpack::SilhouetteScore::SamplesScore(data, assignments, EuclideanD);
}

arma::rowvec SilhouetteScoreEC::Individually(arma::mat data, arma::u64_rowvec assignments, string distanceMetric)
{
	mlpack::ManhattanDistance manhattanD;
	mlpack::SquaredEuclideanDistance sqEuclideanD;

	if (distanceMetric == "manhattan") {
		return mlpack::SilhouetteScore::SamplesScore(data, assignments, manhattanD);
	}

	else if (distanceMetric == "squared") {
		return mlpack::SilhouetteScore::SamplesScore(data, assignments, sqEuclideanD);
	}

	return Individually(data, assignments);
}

double SilhouetteScoreEC::Overall(arma::mat data, arma::u64_rowvec assignments) {
	mlpack::EuclideanDistance EuclideanD;

	return mlpack::SilhouetteScore::Overall(data, assignments, EuclideanD);
}

double SilhouetteScoreEC::Overall(arma::mat data, arma::u64_rowvec assignments, string distanceMetric)
{
	mlpack::ManhattanDistance manhattanD;
	mlpack::SquaredEuclideanDistance sqEuclideanD;

	if (distanceMetric == "manhattan") {
		return mlpack::SilhouetteScore::Overall(data, assignments, manhattanD);
	}

	else if (distanceMetric == "squared") {
		return mlpack::SilhouetteScore::Overall(data, assignments, sqEuclideanD);
	}

	return Overall(data, assignments);
}

void SilhouetteScoreEC::ClustersSilhouette(arma::Row<size_t> assigments, arma::rowvec individualSilhouette, arma::rowvec& clustersSilhouette) {
	int numberOfClusters = clustersSilhouette.n_cols;

	int clustersIterator = 0, numberOfPointsCluster = 0;

	double silhoutteScoreSumCluster = 0.0;

	for (clustersIterator = 0; clustersIterator < numberOfClusters; clustersIterator++) {
		arma::Row<size_t> assignmentsTransformed = arma::Row<size_t>(assigments);

		assignmentsTransformed.transform([clustersIterator](double label) {return (label == clustersIterator) ? 1 : 0; });

		numberOfPointsCluster = arma::sum(assignmentsTransformed);

		silhoutteScoreSumCluster = arma::dot(assignmentsTransformed, individualSilhouette);

		clustersSilhouette[clustersIterator] = silhoutteScoreSumCluster / numberOfPointsCluster;
	}


}

void SilhouetteScoreEC::ClustersSilhouette(arma::Row<size_t> assigments, arma::rowvec individualSilhouette, arma::rowvec& clustersSilhouette, arma::rowvec& numberOfPointsPerCluster) {
	int numberOfClusters = clustersSilhouette.n_cols;

	int clustersIterator = 0, numberOfPointsCluster = 0;

	double silhoutteScoreSumCluster = 0.0;

	for (clustersIterator = 0; clustersIterator < numberOfClusters; clustersIterator++) {
		arma::Row<size_t> assignmentsTransformed = arma::Row<size_t>(assigments);

		assignmentsTransformed.transform([clustersIterator](double label) {return (label == clustersIterator) ? 1 : 0; });

		numberOfPointsCluster = arma::sum(assignmentsTransformed);

		silhoutteScoreSumCluster = arma::dot(assignmentsTransformed, individualSilhouette);

		clustersSilhouette[clustersIterator] = silhoutteScoreSumCluster / numberOfPointsCluster;
		numberOfPointsPerCluster[clustersIterator] = numberOfPointsCluster;
	}


}