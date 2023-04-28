#include <mlpack/core.hpp>
#include <mlpack/methods/kmeans/allow_empty_clusters.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include "SilhouetteScore.h"

using namespace std;

class KMeansEC
{
public:

	KMeansEC(arma::mat data, int numberOfClusters, bool allowEmptyClusters);

	KMeansEC(arma::mat data, int numberOfClusters, arma::mat initialCentroids, bool allowEmptyClusters);

	KMeansEC(arma::mat data, int numberOfClusters, arma::mat initialCentroids, arma::Row<size_t> initialAssignments, bool allowEmptyClusters);

	size_t getNumberOfClusters();
	arma::mat getData();
	arma::mat getCentroids();
	arma::Row<size_t> getAssigments();

	void setNumberOfClusters(int newNumberOfClusters);
	void setData(arma::mat newData);

	double getOverallSilhouette();
	double getOverallSilhouette(string distanceMetric);

	arma::rowvec getIndividualSilhouette();
	arma::rowvec getIndividualSilhouette(string distanceMetric);

	arma::rowvec getClustersSilhouettes();
	arma::rowvec getNumberOfPointsPerCluster();


private:
	size_t numberOfclusters;
	arma::mat data, centroids;
	arma::Row<size_t> assignments;
	arma::rowvec clustersSilhouettes;
	arma::rowvec numberOfPointsPerCluster;
	arma::rowvec individualSilhouette;
	bool allowEmptyClusters;

	// ! It is possible to change the distance metric used for the algorithm here settng a param in KMeans<>
	// For example, to use Manhattan Distance, use KMeans<metric::ManhattanDistance>
	mlpack::KMeans<> mlpackKMeans;
	mlpack::KMeans<mlpack::EuclideanDistance, mlpack::SampleInitialization, mlpack::AllowEmptyClusters> mlpackKMeansAllowEmptyClusters;
	
	void calculateClustersMetrics();
	void calculateIndividualSilhouette();

	// Control flow attributes - one attribute per method (except for the constructor)
	// False indicates that the method is not currently running; true indicates that a prior call is running
	bool controlFlowGetNumberOfClusters;
	bool controlFlowGetData;
	bool controlFlowGetCentroids;
	bool controlFlowGetAssigments;
	bool controlFlowSetNumberOfClusters;
	bool controlFlowSetData;
	bool controlFlowGetOverallSilhouetteWithoutParameters;
	bool controlFlowGetOverallSilhouetteWithParameters;
	bool controlFlowGetIndividualSilhouetteWithoutParameters;
	bool controlFlowGetIndividualSilhouetteWithParameters;
	bool controlFlowGetClustersSilhouettes;
	bool controlFlowGetNumberOfPointsPerCluster;
	bool controlFlowCalculateClustersMetrics;
	bool controlFlowCalculateIndividualSihouette;

	// Control flow attributes for SilhouetteScoreSC
	bool controlFlowSilhouetteIndividuallyNoDistance;
	bool controlFlowSilhouetteOverallNoDistance;
	bool controlFlowSilhouetteIndividuallyWithDistance;
	bool controlFlowSilhouetteOverallWithDistance;
	bool controlFlowSilhouetteClusterSilhouetteNoPoints;
	bool controlFlowSilhouetteClusterSilhouetteWithPoints;
};

