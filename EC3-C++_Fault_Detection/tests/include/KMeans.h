#pragma once
#include <mlpack/core.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include "SilhouetteScore.h"

using namespace mlpack;
class KMeans
{
public:

	KMeans(mat data, int numberOfClusters);
	KMeans(arma::mat data, int numberOfClusters, arma::mat initialCentroids);

	KMeans(mat data, int numberOfClusters, mat initialCentroids, Row<size_t> initialAssignments);

	size_t getNumberOfClusters();
	mat getData();
	mat getCentroids();
	Row<size_t> getAssigments();

	void setNumberOfClusters(int newNumberOfClusters);
	void setData(mat newData);

	double getOverallSilhouette();
	double getOverallSilhouette(std::string distanceMetric);

	rowvec getIndividualSilhouette();
	rowvec getIndividualSilhouette(std::string distanceMetric);

	rowvec getClustersSilhouettes();
	rowvec getNumberOfPointsPerCluster();


private:
	size_t numberOfclusters;
	mat data, centroids;
	Row<size_t> assignments;
	rowvec clustersSilhouettes;
	rowvec numberOfPointsPerCluster;
	rowvec individualSilhouette;

	// ! It is possible to change the distance metric used for the algorithm here settng a param in KMeans<>
	// For example, to use Manhattan Distance, use KMeans<metric::ManhattanDistance>
	kmeans::KMeans<> mlpackKMeans;
	
	void calculateClustersMetrics();
	void calculateIndividualSilhouette();
};

