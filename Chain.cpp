#include "Chain.h"

Chain::Chain() {

}

void Chain::AddJoint(ChainMember& joint) {
	mchain.reserve(1);
	mchain.emplace_back(std::make_unique<ChainMember>(joint));
}

void Chain::UpdateDists() {
	for (int i = 0; i < mchain.size(); ++i) {
		mdists[i] = mchain[i]->length();
	}
}

void Chain::Fabrik(Vector3 goal) {
	Vector3 root = mchain[0]->position();
	Vector3 target = goal;

	// Might deal with far end of chain here



	// Forwards pass over mchain
	for (int i = mchain.size() - 1; i >= 0; --i) {	// Make this range based after it works
		mchain[i]->freeSeek(target);
		target = mchain[i]->position();
	}

	// Might deal with close end of chain here


	// Backwards pass over mchain
	for (auto& it : mchain) {
		it->constrainedSeek(target);
		target - it->position();
	}
}