#pragma once
#include <vector>
#include <memory>
#include <iterator>
#include "ChainMember.h"

class Chain {
private:
	std::vector<std::unique_ptr<ChainMember>> mchain;
	static std::vector<float> mdists;

public:
	Chain();
	void AddJoint(ChainMember& joint);
	void UpdateDists();
	void UpdateDist(int index);	// This might need to be called with the pointer I want to update
	void Fabrik(Vector3 goal);
};