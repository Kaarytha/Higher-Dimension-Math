#include "ChainMember.h"

//ChainMember::ChainMember() {
//	mposition = {};
//	mend = {};
//	mdirection = {};
//	mreference = {1, 0};
//	mlength = 0;
//}

inline const Vector<3>& ChainMember::position() const { return mposition; }
inline const Vector<3>& ChainMember::end() const { return mend; }
inline const Vector<3>& ChainMember::direction() const { return mdirection; }
inline const Vector<3>& ChainMember::reference() const { return mreference; }
inline const float ChainMember::length() const { return mlength; }

inline void ChainMember::setPosition(const Vector<3>& target) { mposition = target; }

inline void ChainMember::setEnd(const Vector<3>& target) { mend = target; }

inline void ChainMember::setDirection(const Vector<3>& direction) { mdirection = direction; }

inline void ChainMember::setReference(const Vector<3>& reference) { mreference = reference; }

inline void ChainMember::update(const Vector<3>& target) {
	mposition = target;
	mend = mposition + mdirection * mlength;
}



//void SpinBone::rconstrainedSeek(const ChainMember& previous) {
//	// Clamp spin
//	float spin = acos(dotProduct(mreference, previous.reference()));
//	if (mspinConstraints.aboveRange(spin)) {
//		mreference = { cos(mspinConstraints.mupper),sin(mspinConstraints.mupper) };
//	}
//	if (mspinConstraints.belowRange(spin)) {
//		mreference = { cos(mspinConstraints.mlower),sin(mspinConstraints.mlower) };
//	}
//}


HingeBone::HingeBone() {
	mplane.mnormal = {};
	mrotationConstraints = Range();
}

inline Vector<3> HingeBone::normal() const { return mplane.mnormal; }

void HingeBone::freeSeek(const Vector<3>& target) {
	float ratio = mlength / distance(mposition, target);
	mposition = (1.0f - ratio) * target + ratio * mposition;
	mend = target;
	// Keep track of other axes
}

//void HingeBone::rfreeSeek(const ChainMember& previous) {
//	float ratio = mlength / distance(mend, previous.end());
//	mposition = previous.end();
//	mend = (1.0f - ratio) * previous.end() + ratio * mend;
//}

void HingeBone::rfreeSeek(const Vector<3>& target) {
	float ratio = mlength / distance(mend, target);
	mposition = target;
	mend = (1.0f - ratio) * target + ratio * mend;
}

void HingeBone::constrainedSeek(const ChainMember& next) {
	float ratio = mlength / distance(mposition, next.position());
	setPosition((1.0f - ratio) * next.position() + ratio * mposition);
	setEnd(next.position());
	// Clamp to the correct axis

	
	// Clamp angle like implemented in Segments
}

void HingeBone::rconstrainedSeek(const ChainMember& previous) {

	float rotation = mdirection.angleFrom(mreference);

	//if (mrotationConstraints.aboveRange(rotation)) {
	//	float diff = mrotationConstraints.mupper - rotation;
	//	
	//	//rotate reference about axis
	//}



	/*
	Hyperplane<3> previousPlane{ mposition, mplane.mnormal };	// Might not be necessary

	Vector<3> previousDirection(mdirection);
	float ratio = mlength / distance(mend, previous.end());
	setPosition(previous.end());
	setEnd((1.0f - ratio) * previous.end() + ratio * mend);
	mdirection = (mend - previous.end()) / distance(mend, previous.end()); // This might not be necesary


	// Clamp to the correct axis
	// Doesn't work if normal to working plane
	setDirection((mend.planarProjection(mposition, mplane.mnormal) - mposition).normalised());
	setEnd(mposition + mdirection * mlength);
	setReference();
	
	// Clamp to correct angle
	// Implement with rotation matrices in absolute space, relative space results in n acos functions, n = number of chain members

	// Check bounds:
	// represent direction vectors as rotation matrix
	// Find angle between rotation matrices ***
	*/
}

// A rotation bone should be considered an extension of previous for seek and can be used for angle resolution