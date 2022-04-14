#include "Chain.h"

Chain::Chain() {

}

void Chain::addJoint(ChainMember& joint) {
	mjoints.reserve(1);
	mjoints.emplace_back(std::make_unique<ChainMember>(joint));
}

// Performs a single iteration of Fabrik towards a Vector<3> goal
void Chain::fabrik(Vector<3> goal) {
	Vector<3> root = mjoints[0]->position();
	Vector<3> target = goal;

	// Forwards pass over mchain
	for (int i = mjoints.size(); i >= 0; --i) {
		mjoints[i]->freeSeek(target);
		target = mjoints[i]->position();
	}

	// Backwards pass over mchain
	for (int i = 1; i < mjoints.size(); ++i) {
		mjoints[i]->rconstrainedSeek(*mjoints[i-1]);
		target = mjoints[i]->end();
	}
}