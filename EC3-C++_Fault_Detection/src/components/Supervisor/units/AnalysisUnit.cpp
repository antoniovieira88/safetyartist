#include "../include/AnalysisUnit.h"

using namespace mlpack;

AnalysisUnit::AnalysisUnit(int numberOfClusters, mat& initialCentroids)
	: initialCentroids(initialCentroids)
{
	AnalysisUnit::numberOfClusters = numberOfClusters;

	totalNumberOfPoints = 0;
	overallSilhouette = 0.0;
	clusterSilhouettes = rowvec(2, fill::zeros);
	numberOfPointsPerCluster = rowvec(2, fill::zeros);
	newMetrics = colvec(5, fill::zeros);
	overallSilhouette = 0.0;
}

void AnalysisUnit::setDataToCluster(mat dataToCluster) {
	AnalysisUnit::dataToCluster = dataToCluster;
}

void AnalysisUnit::cluster(bool allowEmptyClusters) {
	KMeansEC KClusters(dataToCluster, numberOfClusters, initialCentroids, allowEmptyClusters);

	AnalysisUnit::totalNumberOfPoints = KClusters.getData().n_cols;
	AnalysisUnit::overallSilhouette = KClusters.getOverallSilhouette();
	AnalysisUnit::clusterSilhouettes = KClusters.getClustersSilhouettes();
	AnalysisUnit::assignments = KClusters.getAssigments();
	AnalysisUnit::centroids = KClusters.getCentroids();
	AnalysisUnit::numberOfPointsPerCluster = KClusters.getNumberOfPointsPerCluster();
}

void AnalysisUnit::cluster() {
	KMeansEC KClusters(dataToCluster, numberOfClusters, initialCentroids, true);

	AnalysisUnit::totalNumberOfPoints = KClusters.getData().n_cols;
	AnalysisUnit::overallSilhouette = KClusters.getOverallSilhouette();
	AnalysisUnit::clusterSilhouettes = KClusters.getClustersSilhouettes();
	AnalysisUnit::assignments = KClusters.getAssigments();
	AnalysisUnit::centroids = KClusters.getCentroids();
	AnalysisUnit::numberOfPointsPerCluster = KClusters.getNumberOfPointsPerCluster();
}

/*   | Column Position | Meaning | Data Type |
	| --------------- | ------------ - | ------------ - |
	| 0 | iteration | double |
	| 1 | silhouette of cluster 1 | double |
	| 2 | silhouette of cluster 2 | double|
	| 3 | number of points in cluster 1 | double |
	| 4 | number of points in cluster 2 | double |
	| 5 | overall silhouette | double|
*/

colvec AnalysisUnit::getNewMetrics() {
	rowvec newMetricsTransposed = join_rows(clusterSilhouettes, numberOfPointsPerCluster);
	newMetricsTransposed.reshape(1, 5);
	newMetricsTransposed[4] = overallSilhouette;

	newMetrics = trans(newMetricsTransposed);

	return newMetrics;
}

colvec AnalysisUnit::getNewMetrics(bool metricsToAnalyse[5])
{
	colvec newMetrics;

	if (metricsToAnalyse[metrics::silhouetteCluster1]) appendMetric(newMetrics, clusterSilhouettes[0]);

	if (metricsToAnalyse[metrics::silhouetteCluster2]) appendMetric(newMetrics, clusterSilhouettes[1]);

	if (metricsToAnalyse[metrics::numPointsCluster1]) appendMetric(newMetrics, numberOfPointsPerCluster[0]);

	if (metricsToAnalyse[metrics::numPointsCluster2]) appendMetric(newMetrics, numberOfPointsPerCluster[1]);

	if (metricsToAnalyse[metrics::overallSilhouette]) appendMetric(newMetrics, overallSilhouette);

	return newMetrics;
}

int AnalysisUnit::getTotalNumberOfPoints()
{
	return totalNumberOfPoints;
}

int AnalysisUnit::getNumberOfClusters() {
	return numberOfClusters;
}

void AnalysisUnit::appendMetric(colvec& newMetrics, double metric)
{
	int rows_size = newMetrics.n_rows;
	newMetrics.reshape(rows_size + 1, 1);
	newMetrics[rows_size] = metric;
}

mat AnalysisUnit::getCentroids() {
	return centroids;
}

Row<size_t> AnalysisUnit::getAssignments() {
	return assignments;
}