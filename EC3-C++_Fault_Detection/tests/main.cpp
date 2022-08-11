// Includes all relevant components of mlpack.
#include <mlpack/core.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>

// Convenience.
using namespace mlpack;
int main()
{
	// data is the matrix that represents the dataset on which we are clustering on.
	// centroids is the matrix that represents the position of each cluster's centroid.
	arma::mat data, centroids;
	data::Load("data/data.csv", data, true);
	data::Load("data/centroids.csv", centroids, true);

	std::cout << "KMeans started!";

	using namespace mlpack::kmeans;

	size_t clusters;
	KMeans<> k;
	arma::Row<size_t> assignments;

	clusters = 3;

	k.Cluster(data, clusters, assignments, centroids);

	data::Save("data/assignments.csv", assignments, true);
	data::Save("data/centroids.csv", centroids, true);

	std::cout << "KMeans finished!";

	return 0;
}