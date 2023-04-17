#include "../include/AnalysisUnit.h"

using namespace mlpack;

AnalysisUnit::AnalysisUnit(int numberOfClusters)
{
	AnalysisUnit::numberOfClusters = numberOfClusters;

	totalNumberOfPoints = 0;
	overallSilhouette = 0.0;
	clusterSilhouettes = rowvec(2, fill::zeros);
	numberOfPointsPerCluster = rowvec(2, fill::zeros);
	newMetrics = colvec(5, fill::zeros);
	initialCentroids = mat();
	overallSilhouette = 0.0;

	// Initializes all control flow attributes with 'false'
	controlFlowCluster = false;
	controlFlowGetNewMetricsEmptyAttributes = false;
	controlFlowGetNewMetricsWithAttributes = false;
	controlFlowGetCentroids = false;
	controlFlowGetAssignments = false;
	controlFlowGetTotalNumberOfPoints = false;
	controlFlowGetNumberOfClusters = false;
	controlFlowAppendMetric = false;
}

void AnalysisUnit::cluster(mat& dataToCluster, mat& initialCentroids, bool allowEmptyClusters) {
	
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowCluster == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> cluster");
	}

	else
	{
		controlFlowCluster = true;

		KMeansEC KClusters(dataToCluster, numberOfClusters, initialCentroids, allowEmptyClusters);

		AnalysisUnit::totalNumberOfPoints = KClusters.getData().n_cols;
		AnalysisUnit::overallSilhouette = KClusters.getOverallSilhouette();
		AnalysisUnit::clusterSilhouettes = KClusters.getClustersSilhouettes();
		AnalysisUnit::assignments = KClusters.getAssigments();
		AnalysisUnit::centroids = KClusters.getCentroids();
		AnalysisUnit::numberOfPointsPerCluster = KClusters.getNumberOfPointsPerCluster();

		// Redudant clustering to check for consistency of the clustering results.
		KMeansEC RedundantKClusters(dataToCluster, numberOfClusters, initialCentroids, allowEmptyClusters);
		int redundantTotalNumberOfPoints = RedundantKClusters.getData().n_cols;
		double redundantOverallSilhouette = RedundantKClusters.getOverallSilhouette();
		arma::rowvec redundantClusterSilhouettes = RedundantKClusters.getClustersSilhouettes();
		arma::u64_rowvec redundantAssignments = RedundantKClusters.getAssigments();
		arma::mat redundantCentroids = RedundantKClusters.getCentroids();
		arma::rowvec redundantNumberOfPointsPerCluster = RedundantKClusters.getNumberOfPointsPerCluster();

		// Check if the results of both KMeansEC instances are the same
		bool sameTotalNumberOfPoints = totalNumberOfPoints == redundantTotalNumberOfPoints;
		bool sameOverallSilhouette = overallSilhouette == redundantOverallSilhouette;
		bool sameClusterSilhouettes = arma::approx_equal(clusterSilhouettes, redundantClusterSilhouettes, "absdiff", 0.000001);
		bool sameAssignments = arma::approx_equal(assignments, redundantAssignments, "absdiff", 0.000001);
		bool sameCentroids = arma::approx_equal(centroids, redundantCentroids, "absdiff", 0.000001);
		bool sameNumberOfPointsPerCluster = arma::approx_equal(numberOfPointsPerCluster, redundantNumberOfPointsPerCluster, "absdiff", 0.000001);

		// If any of the results is not the same, indicates that an error has been detected and ceases the simulation.
		if (sameTotalNumberOfPoints && sameOverallSilhouette && sameClusterSilhouettes &&
			sameAssignments && sameCentroids && sameNumberOfPointsPerCluster == false)
		{
			throw SimulatorFailureExcep("Redundant clustering with incompatible results", "Supervisor ==> AnalysisUnit ==> cluster");
		}

		// If all the results are correct, releases controlFlowCluster after the method is finished with correct execution.
		// Throws exception if the current execution has not begun from the start.
		else
		{
			if (controlFlowCluster == false)
			{
				throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> cluster");
			}

			else
			{
				controlFlowCluster = false;
			}
		}		
	}		
}

/*   | Column Position | Meaning | Data Type |
	| --------------- | ------------ - | ------------ - |
	| 0 | iteration | double |
	| 1 | silhouette of cluster 1 | double |
	| 2 | silhouette of cluster 2 | double|
	| 3 | number of points in cluster 1 | double |
	| 4 | number of points in cluster 2 | double |
	| 5 | overall silhouette | double |
*/

colvec AnalysisUnit::getNewMetrics() {
	
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetNewMetricsEmptyAttributes == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> getNewMetrics (empty attributes version)");
	}

	else
	{
		controlFlowGetNewMetricsEmptyAttributes = true;
	
		rowvec newMetricsTransposed = join_rows(clusterSilhouettes, numberOfPointsPerCluster);
		newMetricsTransposed.reshape(1, 5);
		newMetricsTransposed[4] = overallSilhouette;

		newMetrics = trans(newMetricsTransposed);

		// Releases controlFlowGetNewMetricsEmptyAttributes after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetNewMetricsEmptyAttributes == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> getNewMetrics (empty attributes version)");
		}

		else
		{
			controlFlowGetNewMetricsEmptyAttributes = false;
			return newMetrics;
		}
	}	
}

colvec AnalysisUnit::getNewMetrics(bool metricsToAnalyse[5])
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetNewMetricsWithAttributes == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> getNewMetrics (version with attributes)");
	}

	else
	{
		controlFlowGetNewMetricsWithAttributes = true;

		colvec newMetrics;

		if (metricsToAnalyse[metrics::silhouetteCluster1]) appendMetric(newMetrics, clusterSilhouettes[0]);

		if (metricsToAnalyse[metrics::silhouetteCluster2]) appendMetric(newMetrics, clusterSilhouettes[1]);

		if (metricsToAnalyse[metrics::numPointsCluster1]) appendMetric(newMetrics, numberOfPointsPerCluster[0]);

		if (metricsToAnalyse[metrics::numPointsCluster2]) appendMetric(newMetrics, numberOfPointsPerCluster[1]);

		if (metricsToAnalyse[metrics::overallSilhouette]) appendMetric(newMetrics, overallSilhouette);

		// Releases controlFlowGetNewMetricsWithAttributes after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetNewMetricsWithAttributes == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> getNewMetrics (version with attributes)");
		}

		else
		{
			controlFlowGetNewMetricsWithAttributes = false;
			return newMetrics;
		}
	}
}

int AnalysisUnit::getTotalNumberOfPoints()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetTotalNumberOfPoints == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> getTotalNumberOfPoints");
	}

	else
	{
		controlFlowGetTotalNumberOfPoints = true;

		// Releases controlFlowGetTotalNumberOfPoints after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetTotalNumberOfPoints == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> getTotalNumberOfPoints");
		}

		else
		{
			controlFlowGetTotalNumberOfPoints = false;
			return totalNumberOfPoints;
		}
	}
}

int AnalysisUnit::getNumberOfClusters()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetNumberOfClusters == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> getNumberOfClusters");
	}

	else
	{
		controlFlowGetNumberOfClusters = true;

		// Releases controlFlowGetNumberOfClusters after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetNumberOfClusters == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> getNumberOfClusters");
		}

		else
		{
			controlFlowGetNumberOfClusters = false;
			return numberOfClusters;
		}
	}
}

void AnalysisUnit::appendMetric(colvec& newMetrics, double metric)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowAppendMetric == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> appendMetric");
	}

	else
	{
		controlFlowAppendMetric = true;

		// Appends metrics
		int rows_size = newMetrics.n_rows;
		newMetrics.reshape(rows_size + 1, 1);
		newMetrics[rows_size] = metric;

		// Releases controlFlowAppendMetric after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowAppendMetric == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> appendMetric");
		}

		else
		{
			controlFlowAppendMetric = false;
		}
	}
	
	
}

mat AnalysisUnit::getCentroids()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetCentroids == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> getCentroids");
	}

	else
	{
		controlFlowGetCentroids = true;

		// Releases controlFlowGetCentroids after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetCentroids == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> getCentroids");
		}

		else
		{
			controlFlowGetCentroids = false;
			return centroids;
		}
	}
}

Row<size_t> AnalysisUnit::getAssignments()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetAssignments == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> getAssignments");
	}

	else
	{
		controlFlowGetAssignments = true;

		// Releases controlFlowGetAssignments after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetAssignments == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> AnalysisUnit ==> getAssignments");
		}

		else
		{
			controlFlowGetAssignments = false;
			return assignments;
		}
	}
}