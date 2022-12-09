#include <mlpack/core.hpp>
#include "include/KMeans.h"

using namespace mlpack;

KMeans::KMeans(mat data, int numberOfClusters, bool allowEmptyClusters = false) {
	KMeans::data = data;
	KMeans::numberOfclusters = numberOfClusters;
	KMeans::allowEmptyClusters = allowEmptyClusters;

	if (allowEmptyClusters) {
		mlpackKMeansAllowEmptyClusters.Cluster(data, numberOfclusters, assignments, centroids);
	}
	else {
		mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids);
	}
	clustersSilhouettes = rowvec(numberOfClusters);
	numberOfPointsPerCluster = rowvec(numberOfClusters);

	calculateClustersMetrics();

}
KMeans::KMeans(mat data, int numberOfClusters, mat initialCentroids, bool allowEmptyClusters = false) {
	KMeans::data = data;
	KMeans::numberOfclusters = numberOfClusters;
	KMeans::allowEmptyClusters = allowEmptyClusters;

	centroids = initialCentroids;

	
	if (allowEmptyClusters) {
		mlpackKMeansAllowEmptyClusters.Cluster(data, numberOfclusters, assignments, centroids, false, true);
	}
	else {
		mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids, false, true);
	}

	clustersSilhouettes = rowvec(numberOfClusters);
	numberOfPointsPerCluster = rowvec(numberOfClusters);

	calculateClustersMetrics();
}
KMeans::KMeans(mat data, int numberOfClusters, mat initialCentroids, Row<size_t> initialAssignments, bool allowEmptyClusters = false)
{
	KMeans::data = data;
	KMeans::numberOfclusters = numberOfClusters;
	KMeans::allowEmptyClusters = allowEmptyClusters;

	centroids = initialCentroids;
	assignments = initialAssignments;
	
	if (allowEmptyClusters) {
		mlpackKMeansAllowEmptyClusters.Cluster(data, numberOfclusters, assignments, centroids, true, true);
	}
	else {
		mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids, true, true);
	}

	clustersSilhouettes = rowvec(numberOfClusters);
	numberOfPointsPerCluster = rowvec(numberOfClusters);

	calculateClustersMetrics();
}

size_t KMeans::getNumberOfClusters() {
	return numberOfclusters;
};

mat KMeans::getData() {
	return data;
}

mat KMeans::getCentroids() {
	return centroids;
}

Row<size_t> KMeans::getAssigments() {
	return assignments;
}

void KMeans::setNumberOfClusters(int newNumberOfClusters) {
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

void KMeans::setData(mat newData) {
	data = newData;
	
	if (allowEmptyClusters) {
		mlpackKMeansAllowEmptyClusters.Cluster(data, numberOfclusters, assignments, centroids);
	}
	else {
		mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids);
	}

	calculateClustersMetrics();
}

double KMeans::getOverallSilhouette() {
	return SilhouetteScore::Overall(data, assignments);
}
double KMeans::getOverallSilhouette(std::string distanceMetric) {
	return SilhouetteScore::Overall(data, assignments, distanceMetric);
}


rowvec KMeans::getIndividualSilhouette() {
	return individualSilhouette;
}
rowvec KMeans::getIndividualSilhouette(std::string distanceMetric)
{
	return SilhouetteScore::Individually(data, assignments, distanceMetric);
};

rowvec KMeans::getClustersSilhouettes() {
	return clustersSilhouettes;
}

rowvec KMeans::getNumberOfPointsPerCluster(){
	return numberOfPointsPerCluster;
}

void KMeans::calculateIndividualSilhouette()
{
	individualSilhouette = SilhouetteScore::Individually(data, assignments);
}

void KMeans::calculateClustersMetrics()
{
	calculateIndividualSilhouette();
	SilhouetteScore::ClustersSilhouette(assignments, individualSilhouette, clustersSilhouettes, numberOfPointsPerCluster);
}
