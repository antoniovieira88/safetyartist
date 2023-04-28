#include <mlpack/core.hpp>
#include "include/KMeans.h"

using namespace std;

KMeansEC::KMeansEC(arma::mat data, int numberOfClusters, bool allowEmptyClusters = false)
{
	// Initializes all control flow attributes with 'false'
	controlFlowkMeansMain = false;
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

	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowkMeansMain == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> KMeansEC (main without empty clusters and standard centroids)");
	}

	else
	{
		controlFlowkMeansMain = true;

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
		

		// Releases controlFlowkMeansMain after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowkMeansMain == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> KMeansEC (main without empty clusters and standard centroids)");
		}

		else
		{
			controlFlowkMeansMain = false;
		}
	}
}

KMeansEC::KMeansEC(arma::mat data, int numberOfClusters, arma::mat initialCentroids, bool allowEmptyClusters = false)
{
	// Initializes all control flow attributes with 'false'
	controlFlowkMeansMain = false;
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
	
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowkMeansMain == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> KMeansEC (main without empty clusters and custom centroids)");
	}

	else
	{
		controlFlowkMeansMain = true;

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


		// Releases controlFlowkMeansMain after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowkMeansMain == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> KMeansEC (main without empty clusters and custom centroids)");
		}

		else
		{
			controlFlowkMeansMain = false;
		}
	}
}

KMeansEC::KMeansEC(arma::mat data, int numberOfClusters, arma::mat initialCentroids, arma::Row<size_t> initialAssignments, bool allowEmptyClusters = false)
{
	// Initializes all control flow attributes with 'false'
	controlFlowkMeansMain = false;
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

	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowkMeansMain == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> KMeansEC (main with empty clusters and custom centroids)");
	}

	else
	{
		controlFlowkMeansMain = true;

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


		// Releases controlFlowkMeansMain after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowkMeansMain == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> KMeansEC (main with empty clusters and custom centroids)");
		}

		else
		{
			controlFlowkMeansMain = false;
		}
	}
}

size_t KMeansEC::getNumberOfClusters()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetNumberOfClusters == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getNumberOfClusters");
	}

	else
	{
		controlFlowGetNumberOfClusters = true;

		// Releases controlFlowGetNumberOfClusters after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetNumberOfClusters == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getNumberOfClusters");
		}

		else
		{
			controlFlowGetNumberOfClusters = false;
			return numberOfclusters;
		}
	}
}

arma::mat KMeansEC::getData()
{
	
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetData == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getData");
	}

	else
	{
		controlFlowGetData = true;

		// Releases controlFlowGetData after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetData == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getData");
		}

		else
		{
			controlFlowGetData = false;
			return data;
		}
	}
}

arma::mat KMeansEC::getCentroids()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetCentroids == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getCentroids");
	}

	else
	{
		controlFlowGetCentroids = true;

		// Releases controlFlowGetCentroids after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetCentroids == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getCentroids");
		}

		else
		{
			controlFlowGetCentroids = false;
			return centroids;
		}
	}
}

arma::Row<size_t> KMeansEC::getAssigments()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetAssigments == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getAssigments");
	}

	else
	{
		controlFlowGetAssigments = true;

		// Releases controlFlowGetAssigments after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetAssigments == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getAssigments");
		}

		else
		{
			controlFlowGetAssigments = false;
			return assignments;
		}
	}
}

void KMeansEC::setNumberOfClusters(int newNumberOfClusters)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowSetNumberOfClusters == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> setNumberOfClusters");
	}

	else
	{
		controlFlowSetNumberOfClusters = true;

		numberOfclusters = newNumberOfClusters;

		if (allowEmptyClusters) {
			mlpackKMeansAllowEmptyClusters.Cluster(data, numberOfclusters, assignments, centroids);
		}
		else {
			mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids);
		}

		mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids);
		calculateClustersMetrics();

		// Releases controlFlowSetNumberOfClusters after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowSetNumberOfClusters == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> setNumberOfClusters");
		}

		else
		{
			controlFlowSetNumberOfClusters = false;
		}
	}	
};

void KMeansEC::setData(arma::mat newData)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowSetData == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> setData");
	}

	else
	{
		controlFlowSetData = true;

		data = newData;

		if (allowEmptyClusters) {
			mlpackKMeansAllowEmptyClusters.Cluster(data, numberOfclusters, assignments, centroids);
		}
		else {
			mlpackKMeans.Cluster(data, numberOfclusters, assignments, centroids);
		}

		calculateClustersMetrics();

		// Releases controlFlowSetData after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowSetData == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> setData");
		}

		else
		{
			controlFlowSetData = false;
		}
	}
}

double KMeansEC::getOverallSilhouette()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetOverallSilhouetteWithoutParameters == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getOverallSilhouette (without parameters)");
	}

	else
	{
		controlFlowGetOverallSilhouetteWithoutParameters = true;

		// Releases controlFlowGetOverallSilhouetteWithoutParameters after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetOverallSilhouetteWithoutParameters == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getOverallSilhouette (without parameters)");
		}

		else
		{
			controlFlowGetOverallSilhouetteWithoutParameters = false;
			return SilhouetteScoreEC::Overall(data, assignments, &controlFlowSilhouetteOverallNoDistance);
		}
	}
}

double KMeansEC::getOverallSilhouette(std::string distanceMetric)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetOverallSilhouetteWithParameters == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getOverallSilhouette (with parameters)");
	}

	else
	{
		controlFlowGetOverallSilhouetteWithParameters = true;

		// Releases controlFlowGetOverallSilhouetteWithParameters after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetOverallSilhouetteWithParameters == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getOverallSilhouette (with parameters)");
		}

		else
		{
			controlFlowGetOverallSilhouetteWithParameters = false;
			return SilhouetteScoreEC::Overall(data, assignments, distanceMetric, &controlFlowSilhouetteOverallWithDistance);
		}
	}
}


arma::rowvec KMeansEC::getIndividualSilhouette()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetIndividualSilhouetteWithoutParameters == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getIndividualSilhouette (without parameters)");
	}

	else
	{
		controlFlowGetIndividualSilhouetteWithoutParameters = true;

		// Releases controlFlowGetOverallSilhouetteWithoutParameters after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetIndividualSilhouetteWithoutParameters == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getIndividualSilhouette (without parameters)");
		}

		else
		{
			controlFlowGetIndividualSilhouetteWithoutParameters = false;
			return individualSilhouette;
		}
	}
}
arma::rowvec KMeansEC::getIndividualSilhouette(std::string distanceMetric)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetIndividualSilhouetteWithParameters == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getIndividualSilhouette (with parameters)");
	}

	else
	{
		controlFlowGetIndividualSilhouetteWithParameters = true;

		// Releases controlFlowGetIndividualSilhouetteWithParameters after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetIndividualSilhouetteWithParameters == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getIndividualSilhouette (with parameters)");
		}

		else
		{
			controlFlowGetIndividualSilhouetteWithParameters = false;
			return SilhouetteScoreEC::Individually(data, assignments, distanceMetric, &controlFlowSilhouetteIndividuallyWithDistance);
		}
	}	
};

arma::rowvec KMeansEC::getClustersSilhouettes()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetClustersSilhouettes == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getClustersSilhouettes");
	}

	else
	{
		controlFlowGetClustersSilhouettes = true;

		// Releases controlFlowGetClustersSilhouettes after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetClustersSilhouettes == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getClustersSilhouettes");
		}

		else
		{
			controlFlowGetClustersSilhouettes = false;
			return clustersSilhouettes;
		}
	}
}

arma::rowvec KMeansEC::getNumberOfPointsPerCluster()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetNumberOfPointsPerCluster == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getNumberOfPointsPerCluster");
	}

	else
	{
		controlFlowGetNumberOfPointsPerCluster = true;

		// Releases controlFlowGetNumberOfPointsPerCluster after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetNumberOfPointsPerCluster == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> getNumberOfPointsPerCluster");
		}

		else
		{
			controlFlowGetNumberOfPointsPerCluster = false;
			return numberOfPointsPerCluster;
		}
	}
}

void KMeansEC::calculateIndividualSilhouette()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowCalculateIndividualSihouette == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> calculateIndividualSilhouette");
	}

	else
	{
		controlFlowCalculateIndividualSihouette = true;

		individualSilhouette = SilhouetteScoreEC::Individually(data, assignments, &controlFlowSilhouetteIndividuallyNoDistance);

		// Releases controlFlowCalculateIndividualSihouette after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowCalculateIndividualSihouette == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> calculateIndividualSilhouette");
		}

		else
		{
			controlFlowCalculateIndividualSihouette = false;
		}
	}
}

void KMeansEC::calculateClustersMetrics()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowCalculateClustersMetrics == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> calculateClustersMetrics");
	}

	else
	{
		controlFlowCalculateClustersMetrics = true;

		calculateIndividualSilhouette();
		SilhouetteScoreEC::ClustersSilhouette(assignments, individualSilhouette, clustersSilhouettes, numberOfPointsPerCluster, &controlFlowSilhouetteClusterSilhouetteWithPoints);

		// Releases controlFlowCalculateClustersMetrics after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowCalculateClustersMetrics == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "KMeansEC ==> calculateClustersMetrics");
		}

		else
		{
			controlFlowCalculateClustersMetrics = false;
		}
	}	
}