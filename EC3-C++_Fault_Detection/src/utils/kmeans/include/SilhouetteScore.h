#pragma once
#include <mlpack/core.hpp>
#include <string>
#include "../../../utils/exceptions/include/SimulatorFailureExcep.h"

using namespace std;

class SilhouetteScoreEC
{
public:

	static arma::rowvec Individually(arma::mat data, arma::u64_rowvec assignments, bool *controlFlow);

	static double Overall(arma::mat data, arma::u64_rowvec assignments, bool *controlFlow);

	static arma::rowvec Individually(arma::mat data, arma::u64_rowvec assignments, string distanceMetric, bool *controlFlow);

	static double Overall(arma::mat data, arma::u64_rowvec assignments, string distanceMetric, bool *controlFlow);

	static void ClustersSilhouette(arma::Row<size_t> assigments, arma::rowvec individualSilhouette, arma::rowvec& clustersSilhouette, bool *controlFlow);
	static void ClustersSilhouette(arma::Row<size_t> assigments, arma::rowvec individualSilhouette, arma::rowvec& clustersSilhouette, arma::rowvec& numberOfPointsPerCluster, bool *controlFlow);
};