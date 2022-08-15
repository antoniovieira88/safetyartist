#include "include/KMeans.h"
#include <mlpack/core.hpp>

using namespace mlpack;

KMeans::KMeans(arma::mat data, int numberOfClusters) {
	KMeans::data = data;
	KMeans::numberOfclusters = numberOfClusters;

	mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids);
}

KMeans::KMeans(arma::mat data, int numberOfClusters, arma::mat centroids) {
	KMeans::data = data;
	KMeans::numberOfclusters = numberOfClusters;
	KMeans::centroids = centroids;

	mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids, false, true);
}

KMeans::KMeans(arma::mat data, int numberOfClusters, Row<size_t> assignments, arma::mat centroids) {
	KMeans::data = data;
	KMeans::numberOfclusters = numberOfClusters;
	KMeans::centroids = centroids;
	KMeans::assignments = assignments;

	mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids, false, true);
}

size_t KMeans::getNumberOfClusters() {
	return numberOfclusters;
};

mat KMeans::getData() {
	return data;
}

mat KMeans::getCentroids() {
	return data;
}

Row<size_t> KMeans::getAssigments() {
	return assignments;
}

void KMeans::setNumberOfClusters(int newNumberOfClusters) {
	numberOfclusters = newNumberOfClusters;
	mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids);
};

void KMeans::setData(mat newData) {
	data = newData;
	mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids);
}

double KMeans::getOverallSilhouette() {
	return Silhouette.Overall(data, assignments);
}
double KMeans::getOverallSilhouette(std::string distanceMetric) {
	return Silhouette.Overall(data, assignments, distanceMetric);
}

rowvec KMeans::getIndividualSilhouette()
{
	return Silhouette.Individually(data, assignments);
};
rowvec KMeans::getIndividualSilhouette(std::string distanceMetric)
{
	return Silhouette.Individually(data, assignments, distanceMetric);
};