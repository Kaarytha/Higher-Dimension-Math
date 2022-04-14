#pragma once
#include <vector>
#include <memory>
#include <iterator>
#include "ChainMember.h"

// Stores all bones in a IK chain and a reference bone that shows initial position
class Chain {
private:
	std::vector<std::unique_ptr<ChainMember>> mjoints;

public:
	Chain();
	void addJoint(ChainMember& joint);
	void fabrik(Vector<3> goal); // Solves Fabrik for a point
};