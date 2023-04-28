#include <mlpack/core.hpp>
#include "include/KMeans.h"

using namespace std;

KMeansEC::KMeansEC(arma::mat data, int numberOfClusters, bool allowEmptyClusters = false)
{
	// Initializes all control flow attributes with 'false'
	controlFlowGetNumberOfClusters = false;
	controlFlowGetData = false;
	controlFlowGetCentroids = false;
	controlFlowGetAssigments = false;
	controlFlowSetNumberOfClusters = false;
	controlFlowSetData = false;
	controlFlowGetOverallSilhouetteWithoutParameters = false;
	controlFlowGetOverallSilhouetteWithParameters = false;
	controlFlowGetIndividualSilhouetteWithoutParameters = false;
	controlFlowGetIndividualSilhouetteWithParameters = false;
	controlFlowGetClustersSilhouettes = false;
	controlFlowGetNumberOfPointsPerCluster = false;
	controlFlowCalculateClustersMetrics = false;
	controlFlowCalculateIndividualSihouette = false;

	// Control flow attributes for SilhouetteScoreSC
	controlFlowSilhouetteIndividuallyNoDistance = false;
	controlFlowSilhouetteOverallNoDistance = false;
	controlFlowSilhouetteIndividuallyWithDistance = false;
	controlFlowSilhouetteOverallWithDistance = false;
	controlFlowSilhouetteClusterSilhouetteNoPoints = false;
	controlFlowSilhouetteClusterSilhouetteWithPoints = false;
	
	KMeansEC::data = data;
	KMeansEC::numberOfclusters = numberOfClusters;
	KMeansEC::allowEmptyClusters = allowEmptyClusters;

	if (allowEmptyClusters) {
		mlpackKMeansAllowEmptyClusters.Cluster(data, numberOfclusters, assignments, centroids);
	}
	else {
		mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids);
	}
	clustersSilhouettes = arma::rowvec(numberOfClusters);
	numberOfPointsPerCluster = arma::rowvec(numberOfClusters);

	calculateClustersMetrics();

}

KMeansEC::KMeansEC(arma::mat data, int numberOfClusters, arma::mat initialCentroids, bool allowEmptyClusters = false)
{
	// Initializes all control flow attributes with 'false'
	controlFlowGetNumberOfClusters = false;
	controlFlowGetData = false;
	controlFlowGetCentroids = false;
	controlFlowGetAssigments = false;
	controlFlowSetNumberOfClusters = false;
	controlFlowSetData = false;
	controlFlowGetOverallSilhouetteWithoutParameters = false;
	controlFlowGetOverallSilhouetteWithParameters = false;
	controlFlowGetIndividualSilhouetteWithoutParameters = false;
	controlFlowGetIndividualSilhouetteWithParameters = false;
	controlFlowGetClustersSilhouettes = false;
	controlFlowGetNumberOfPointsPerCluster = false;
	controlFlowCalculateClustersMetrics = false;
	controlFlowCalculateIndividualSihouette = false;

	// Control flow attributes for SilhouetteScoreSC
	controlFlowSilhouetteIndividuallyNoDistance = false;
	controlFlowSilhouetteOverallNoDistance = false;
	controlFlowSilhouetteIndividuallyWithDistance = false;
	controlFlowSilhouetteOverallWithDistance = false;
	controlFlowSilhouetteClusterSilhouetteNoPoints = false;
	controlFlowSilhouetteClusterSilhouetteWithPoints = false;
	
	KMeansEC::data = data;
	KMeansEC::numberOfclusters = numberOfClusters;
	KMeansEC::allowEmptyClusters = allowEmptyClusters;

	centroids = initialCentroids;

	
	if (allowEmptyClusters) {
		mlpackKMeansAllowEmptyClusters.Cluster(data, numberOfclusters, assignments, centroids, false, true);
	}
	else {
		mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids, false, true);
	}

	clustersSilhouettes = arma::rowvec(numberOfClusters);
	numberOfPointsPerCluster = arma::rowvec(numberOfClusters);

	calculateClustersMetrics();
}

KMeansEC::KMeansEC(arma::mat data, int numberOfClusters, arma::mat initialCentroids, arma::Row<size_t> initialAssignments, bool allowEmptyClusters = false)
{
	// Initializes all control flow attributes with 'false'
	controlFlowGetNumberOfClusters = false;
	controlFlowGetData = false;
	controlFlowGetCentroids = false;
	controlFlowGetAssigments = false;
	controlFlowSetNumberOfClusters = false;
	controlFlowSetData = false;
	controlFlowGetOverallSilhouetteWithoutParameters = false;
	controlFlowGetOverallSilhouetteWithParameters = false;
	controlFlowGetIndividualSilhouetteWithoutParameters = false;
	controlFlowGetIndividualSilhouetteWithParameters = false;
	controlFlowGetClustersSilhouettes = false;
	controlFlowGetNumberOfPointsPerCluster = false;
	controlFlowCalculateClustersMetrics = false;
	controlFlowCalculateIndividualSihouette = false;

	// Control flow attributes for SilhouetteScoreSC
	controlFlowSilhouetteIndividuallyNoDistance = false;
	controlFlowSilhouetteOverallNoDistance = false;
	controlFlowSilhouetteIndividuallyWithDistance = false;
	controlFlowSilhouetteOverallWithDistance = false;
	controlFlowSilhouetteClusterSilhouetteNoPoints = false;
	controlFlowSilhouetteClusterSilhouetteWithPoints = false;

	KMeansEC::data = data;
	KMeansEC::numberOfclusters = numberOfClusters;
	KMeansEC::allowEmptyClusters = allowEmptyClusters;

	centroids = initialCentroids;
	assignments = initialAssignments;
	
	if (allowEmptyClusters) {
		mlpackKMeansAllowEmptyClusters.Cluster(data, numberOfclusters, assignments, centroids, true, true);
	}
	else {
		mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids, true, true);
	}

	clustersSilhouettes = arma::rowvec(numberOfClusters);
	numberOfPointsPerCluster = arma::rowvec(numberOfClusters);

	calculateClustersMetrics();
}

size_t KMeansEC::getNumberOfClusters() {
	return numberOfclusters;
};

arma::mat KMeansEC::getData() {
	return data;
}

arma::mat KMeansEC::getCentroids() {
	return centroids;
}

arma::Row<size_t> KMeansEC::getAssigments() {
	return assignments;
}

void KMeansEC::setNumberOfClusters(int newNumberOfClusters) {
	numberOfclusters = newNumberOfClusters;
	
	if (allowEmptyClusters) {
		mlpackKMeansAllowEmptyClusters.Cluster(data, numberOfclusters, assignments, centroids);
	}
	else {
		mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids);
	}

	mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids);
	calculateClustersMetrics();
};

void KMeansEC::setData(arma::mat newData) {
	data = newData;
	
	if (allowEmptyClusters) {
		mlpackKMeansAllowEmptyClusters.Cluster(data, numberOfclusters, assignments, centroids);
	}
	else {
		mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids);
	}

	calculateClustersMetrics();
}

double KMeansEC::getOverallSilhouette() {
	return SilhouetteScoreEC::Overall(data, assignments, &controlFlowSilhouetteOverallNoDistance);
}
double KMeansEC::getOverallSilhouette(std::string distanceMetric) {
	return SilhouetteScoreEC::Overall(data, assignments, distanceMetric, &controlFlowSilhouetteOverallWithDistance);
}


arma::rowvec KMeansEC::getIndividualSilhouette() {
	return individualSilhouette;
}
arma::rowvec KMeansEC::getIndividualSilhouette(std::string distanceMetric)
{
	return SilhouetteScoreEC::Individually(data, assignments, distanceMetric, &controlFlowSilhouetteIndividuallyWithDistance);
};

arma::rowvec KMeansEC::getClustersSilhouettes() {
	return clustersSilhouettes;
}

arma::rowvec KMeansEC::getNumberOfPointsPerCluster(){
	return numberOfPointsPerCluster;
}

void KMeansEC::calculateIndividualSilhouette()
{
	individualSilhouette = SilhouetteScoreEC::Individually(data, assignments, &controlFlowSilhouetteIndividuallyNoDistance);
}

void KMeansEC::calculateClustersMetrics()
{
	calculateIndividualSilhouette();
	SilhouetteScoreEC::ClustersSilhouette(assignments, individualSilhouette, clustersSilhouettes, numberOfPointsPerCluster, &controlFlowSilhouetteClusterSilhouetteWithPoints);
}
