#include "include/enum.h"

namespace std {

	fmSafety std::stringToFmSafetyEnum(string str) {
		fmSafety value;

		switch (str) {
		case "safe":
			value = safe;
			break;
		case "unsafe":
			value = unsafe;
			break;
		default:
			throw invalid_argument();
			break;
		}

		return value;
	}

	fmDetectable std::stringToFmDetectableEnum(string str) {
		fmDetectable value;

		switch (str) {
		case "yes":
			value = yes;
			break;
		case "no":
			value = no;
			break;
		case "impactless":
			value = impactless;
			break;
		case "outside_scope":
			value = outsideScope;
			break;
		case "maybe":
			value = maybe;
			break;
		default:
			throw invalid_argument();
			break;
		}

		return value;
	}

	classMultipleFaults std::stringToClassMultipleFaultsEnum(string str) {
		classMultipleFaults value;

		switch (str) {
		case "cm0":
			value = cm0;
			break;
		case "cm1":
			value = cm1;
			break;
		case "cm2":
			value = cm2;
			break;
		case "cm3":
			value = cm3;
			break;
		case "not_applicable":
			value = notApplicable;
			break;
		default:
			throw invalid_argument();
			break;
		}

		return value;
	}
}