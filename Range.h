#pragma once

typedef struct Range {
	float mlower, mupper;
	
	Range();
	Range(float upper, float lower);

	bool inRange(float var);
	bool aboveRange(float var);
	bool belowRange(float var);

} Range;