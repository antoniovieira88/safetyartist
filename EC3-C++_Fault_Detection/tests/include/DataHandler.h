#include <mlpack/core.hpp>

using namespace arma;
class DataHandler {
	public:

		DataHandler();

		void loadOldMetrics();

		void saveNewMetrics();

		void setNewMetrics(rowvec clustersSilhouette, rowvec numberOfPointsPerCluster, double OverallSilhouette);

	private:
		int iteration = 0;

		mat historicalMetrics;
		colvec previousMetrics;
		colvec newMetrics;

};