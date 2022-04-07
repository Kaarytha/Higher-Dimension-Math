#include "ChainMember.h"

ChainMember::ChainMember() {
	mposition = Vector3();
}

Vector3 ChainMember::Position() { return mposition; }

void ChainMember::SetPosition(Vector3 target) {
	mposition = target;
}

float ChainMember::Length() { return mlength; }



void HingeBone::FreeSeek(Vector3 target) {
	float ratio = mlength / distance(mposition, target); // start using dists instead of inherent lengths
	mposition = (1.0f - ratio) * target + ratio * mposition;
}

// I don't think the Bone should know about other bones, so how does it use Chain.mdists?
void HingeBone::ConstrainedSeek(Vector3 target) {
	float ratio = mlength / distance(mposition, target); // start using dists instead of inherent lengths
	mposition = (1.0f - ratio) * target + ratio * mposition;
	// Clamp to the correct axis
	// Clamp angle like implemented in Segments
}

//bool fabrikSeek(Vector3 target, int iter, double accuracy) {
//	std::vector<double> dists;
//	std::shared_ptr<Joint> root = mjoints[0];
//
//	dists.reserve(mjoints.size() - 1);
//	for (auto it = std::begin(mjoints); it != std::end(mjoints) - 1; ++it) {
//		dists.emplace_back(distance(it, it + 1));
//	}
//
//	for (int i = 0; i < iter; ++i) {
//		// Forwards
//		mjoints.back()->Update(target);
//
//		for (auto it = std::rend(mjoints) - 1; it != std::rbegin(mjoints); --it) {
//			double r = distance(it, it + 1);
//			double lambda = dists[it] / r;
//			Joint& iter = **it;
//			iter.Update((1 - lambda) * **(it + 1) + lambda * **it);
//		}
//	}
//}