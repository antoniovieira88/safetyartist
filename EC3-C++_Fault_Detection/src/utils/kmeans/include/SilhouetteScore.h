#pragma once
#include <mlpack/core.hpp>
#include <string>

using namespace std;

class SilhouetteScoreEC
{
public:

	static arma::rowvec Individually(arma::mat data, arma::u64_rowvec assignments);

	static double Overall(arma::mat data, arma::u64_rowvec assignments);

	static arma::rowvec Individually(arma::mat data, arma::u64_rowvec assignments, string distanceMetric);

	static double Overall(arma::mat data, arma::u64_rowvec assignments, string distanceMetric);

	static void ClustersSilhouette(arma::Row<size_t> assigments, arma::rowvec individualSilhouette, arma::rowvec& clustersSilhouette);
	static void ClustersSilhouette(arma::Row<size_t> assigments, arma::rowvec individualSilhouette, arma::rowvec& clustersSilhouette, arma::rowvec& numberOfPointsPerCluster);
};

