#include "Chain.h"

Chain::Chain() {

}

void Chain::AddJoint(ChainMember& joint) {
	mchain.reserve(1);
	mchain.emplace_back(std::make_unique<ChainMember>(joint));
}

void Chain::UpdateDists() {
	for (int i = 0; i < mchain.size(); ++i) {
		mdists[i] = mchain[i]->Length();
	}
}

void Chain::Fabrik(Vector3 goal) {
	Vector3 root = mchain[0]->Position();
	Vector3 target = goal;

	// Might deal with far end of chain here



	// Forwards pass over mchain
	for (int i = mchain.size() - 1; i >= 0; --i) {	// Make this range based after it works
		mchain[i]->FreeSeek(target);
		target = mchain[i]->Position();
	}

	// Might deal with close end of chain here


	// Backwards pass over mchain
	for (auto& it : mchain) {
		it->ConstrainedSeek(target);
		target - it->Position();
	}
}