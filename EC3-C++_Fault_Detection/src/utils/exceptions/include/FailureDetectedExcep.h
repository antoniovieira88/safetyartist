#include <string>
#include <vector>
#include "../../structs/structs.h"

using namespace std;

static string metricStr[] =
{
  "silhouetteCluster1",
  "silhouetteCluster2",
  "numPointsCluster1",
  "numPointsCluster2",
  "overallSilhouette",
  "imbalanceNumPoints"
};

struct faultDiagnosisType {
	bool failure;
	vector<failureMetricIndicatorType> failureIndicators;
};

class FailureDetectedExcep : public exception {
private:
	vector<failureMetricIndicatorType> failureIndicators;
	string errorMessage;
	string logError;

	void buildLogError();

public:
	FailureDetectedExcep(faultDiagnosisType faultDiagnosis);
	vector<failureMetricIndicatorType> getFailureIndicators();
	const char* what() const throw();
	string getLogError();
};