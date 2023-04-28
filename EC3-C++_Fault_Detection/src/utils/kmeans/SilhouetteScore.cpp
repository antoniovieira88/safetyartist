#include "./include/SilhouetteScore.h"
#include <mlpack/core.hpp>
#include <mlpack/core/cv/metrics/silhouette_score.hpp>
#include <string>

using namespace std;

arma::rowvec SilhouetteScoreEC::Individually(arma::mat data, arma::u64_rowvec assignments, bool *controlFlow) {
	
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (*controlFlow == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "SilhouetteScoreEC ==> Individually (no distance)");
	}

	else
	{
		*controlFlow = true;

		mlpack::EuclideanDistance EuclideanD;

		// Releases *controlFlow after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (*controlFlow == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "SilhouetteScoreEC ==> Individually (no distance)");
		}

		else
		{
			*controlFlow = false;
			return mlpack::SilhouetteScore::SamplesScore(data, assignments, EuclideanD);
		}
	}
}

arma::rowvec SilhouetteScoreEC::Individually(arma::mat data, arma::u64_rowvec assignments, string distanceMetric, bool *controlFlow)
{
	
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (*controlFlow == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "SilhouetteScoreEC ==> Individually (with distance)");
	}

	else
	{
		*controlFlow = true;

		mlpack::ManhattanDistance manhattanD;
		mlpack::SquaredEuclideanDistance sqEuclideanD;
		mlpack::EuclideanDistance EuclideanD;

		arma::rowvec result;

		if (distanceMetric == "manhattan") {
			result = mlpack::SilhouetteScore::SamplesScore(data, assignments, manhattanD);
		}

		else if (distanceMetric == "squared") {
			result = mlpack::SilhouetteScore::SamplesScore(data, assignments, sqEuclideanD);
		}

		else {
			result = mlpack::SilhouetteScore::SamplesScore(data, assignments, EuclideanD);
		}

		// Releases *controlFlow after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (*controlFlow == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "SilhouetteScoreEC ==> Individually (with distance)");
		}

		else
		{
			*controlFlow = false;
			return result;			
		}
	}
}

double SilhouetteScoreEC::Overall(arma::mat data, arma::u64_rowvec assignments, bool *controlFlow)
{
	
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (*controlFlow == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "SilhouetteScoreEC ==> Overall (no distance)");
	}

	else
	{
		*controlFlow = true;

		mlpack::EuclideanDistance EuclideanD;

		// Releases *controlFlow after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (*controlFlow == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "SilhouetteScoreEC ==> Overall (no distance)");
		}

		else
		{
			*controlFlow = false;
			return mlpack::SilhouetteScore::Overall(data, assignments, EuclideanD);
		}
	}
}

double SilhouetteScoreEC::Overall(arma::mat data, arma::u64_rowvec assignments, string distanceMetric, bool *controlFlow)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (*controlFlow == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "SilhouetteScoreEC ==> Overall (with distance)");
	}

	else
	{
		*controlFlow = true;

		mlpack::ManhattanDistance manhattanD;
		mlpack::SquaredEuclideanDistance sqEuclideanD;
		mlpack::EuclideanDistance EuclideanD;

		double result;

		if (distanceMetric == "manhattan") {
			result = mlpack::SilhouetteScore::Overall(data, assignments, manhattanD);
		}

		else if (distanceMetric == "squared") {
			result = mlpack::SilhouetteScore::Overall(data, assignments, sqEuclideanD);
		}

		else {
			result = mlpack::SilhouetteScore::Overall(data, assignments, EuclideanD);
		}

		// Releases *controlFlow after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (*controlFlow == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "SilhouetteScoreEC ==> Overall (with distance)");
		}

		else
		{
			*controlFlow = false;
			return result;
		}
	}
}

void SilhouetteScoreEC::ClustersSilhouette(arma::Row<size_t> assigments, arma::rowvec individualSilhouette, arma::rowvec& clustersSilhouette, bool *controlFlow)
{	
	
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (*controlFlow == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "SilhouetteScoreEC ==> ClustersSilhouette (no numberOfPoints)");
	}

	else
	{
		*controlFlow = true;

		int numberOfClusters = clustersSilhouette.n_cols;

		int clustersIterator = 0, numberOfPointsCluster = 0;

		double silhoutteScoreSumCluster = 0.0;

		for (clustersIterator = 0; clustersIterator < numberOfClusters; clustersIterator++)
		{
			arma::Row<size_t> assignmentsTransformed = arma::Row<size_t>(assigments);

			assignmentsTransformed.transform([clustersIterator](double label) {return (label == clustersIterator) ? 1 : 0; });

			numberOfPointsCluster = arma::sum(assignmentsTransformed);

			silhoutteScoreSumCluster = arma::dot(assignmentsTransformed, individualSilhouette);

			clustersSilhouette[clustersIterator] = silhoutteScoreSumCluster / numberOfPointsCluster;
		}

		// Releases *controlFlow after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (*controlFlow == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "SilhouetteScoreEC ==> ClustersSilhouette (no numberOfPoints)");
		}

		else
		{
			*controlFlow = false;
		}
	}
}

void SilhouetteScoreEC::ClustersSilhouette(arma::Row<size_t> assigments, arma::rowvec individualSilhouette, arma::rowvec& clustersSilhouette, arma::rowvec& numberOfPointsPerCluster, bool *controlFlow)
{
	
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (*controlFlow == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "SilhouetteScoreEC ==> ClustersSilhouette (with numberOfPoints)");
	}

	else
	{
		*controlFlow = true;

		int numberOfClusters = clustersSilhouette.n_cols;

		int clustersIterator = 0, numberOfPointsCluster = 0;

		double silhoutteScoreSumCluster = 0.0;

		for (clustersIterator = 0; clustersIterator < numberOfClusters; clustersIterator++)
		{
			arma::Row<size_t> assignmentsTransformed = arma::Row<size_t>(assigments);

			assignmentsTransformed.transform([clustersIterator](double label) {return (label == clustersIterator) ? 1 : 0; });

			numberOfPointsCluster = arma::sum(assignmentsTransformed);

			silhoutteScoreSumCluster = arma::dot(assignmentsTransformed, individualSilhouette);

			clustersSilhouette[clustersIterator] = silhoutteScoreSumCluster / numberOfPointsCluster;

			numberOfPointsPerCluster[clustersIterator] = numberOfPointsCluster;
		}

		// Releases *controlFlow after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (*controlFlow == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "SilhouetteScoreEC ==> ClustersSilhouette (with numberOfPoints)");
		}

		else
		{
			*controlFlow = false;
		}
	}	
}