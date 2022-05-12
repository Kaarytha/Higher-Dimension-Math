#include "Range.h"

Range::Range() {
	mlower = 0;
	mupper = 0;
}

Range::Range(float lower, float upper) {
	mlower = lower;
	mupper = upper;
}

inline bool Range::inRange(float var) {
	if (var >= mlower || var <= mupper) return true;
	return false;
}

inline bool Range::aboveRange(float var) {
	if (var > mupper) return true;
	return false;
}

inline bool Range::belowRange(float var) {
	if (var < mlower) return true;
	return false;
}