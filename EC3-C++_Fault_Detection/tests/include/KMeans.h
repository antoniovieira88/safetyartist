#include <mlpack/core.hpp>
#include <mlpack/methods/kmeans/allow_empty_clusters.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include "SilhouetteScore.h"

using namespace mlpack;

class KMeans
{
public:

	KMeans(mat data, int numberOfClusters, bool allowEmptyClusters);

	KMeans(mat data, int numberOfClusters, mat initialCentroids, bool allowEmptyClusters);

	KMeans(mat data, int numberOfClusters, mat initialCentroids, Row<size_t> initialAssignments, bool allowEmptyClusters);

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
	bool allowEmptyClusters;

	// ! It is possible to change the distance metric used for the algorithm here settng a param in KMeans<>
	// For example, to use Manhattan Distance, use KMeans<metric::ManhattanDistance>
	kmeans::KMeans<> mlpackKMeans;
	kmeans::KMeans<metric::EuclideanDistance, kmeans::SampleInitialization, mlpack::kmeans::AllowEmptyClusters> mlpackKMeansAllowEmptyClusters;
	
	void calculateClustersMetrics();
	void calculateIndividualSilhouette();
};

