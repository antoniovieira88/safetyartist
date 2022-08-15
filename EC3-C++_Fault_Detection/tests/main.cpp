// Includes all relevant components of mlpack.
#include <mlpack/core.hpp>
#include "./include/KMeans.h"

// Convenience.
using namespace mlpack;
int main()
{
	// data is the matrix that represents the dataset on which we are clustering on.
	// centroids is the matrix that represents the position of each cluster's centroid.
	arma::mat data, centroids;
	data::Load("data/data.csv", data, true);
	//data::Load("data/centroids.csv", centroids, true);

	std::cout << "KMeans started!" << endl;

	KMeans KClusters(data, 3);

	std::cout << "Number of clusters: " << KClusters.getNumberOfClusters() << endl;

	std::cout << "Overall Silhouette Score - Euclidian Distance: " << KClusters.getOverallSilhouette() << endl;
	std::cout << "Overall Silhouette Score - Manhattan Distance: " << KClusters.getOverallSilhouette("manhattan") << endl;
	std::cout << "Overall Silhouette Score - Squared Euclidian Distance: " << KClusters.getOverallSilhouette("squared") << endl;


	data::Save("data/assignments.csv", KClusters.getAssigments(), true);
	data::Save("data/centroids.csv", KClusters.getCentroids(), true);
	data::Save("data/SilhouetteIndividually.csv", KClusters.getIndividualSilhouette(), true);

	std::cout << "KMeans finished!";

	return 0;
}