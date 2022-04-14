#include "ChainMember.h"

ChainMember::ChainMember() {
	mposition = {};
	mend = {};
	mdirection = {};
	mreference = {};
	mlength = 0;
}

const Vector<3>& ChainMember::position() const { return mposition; }

const Vector<3>& ChainMember::end() const { return mend; }

const Vector<3>& ChainMember::direction() const { return mdirection; }

const Vector<3>& ChainMember::reference() const { return mreference; }

const float ChainMember::length() const { return mlength; }

void ChainMember::setPosition(const Vector<3>& target) {
	mposition = target;
}

void ChainMember::setEnd(const Vector<3>& target) {
	mend = target;
}

void ChainMember::setDirection(const Vector<3>& direction) {
	mdirection = direction;
}

void ChainMember::update(const Vector<3>& target) {
	mposition = target;
	mend = mposition + mdirection * mlength;
}



HingeBone::HingeBone() {
	mposition = {};
}

void HingeBone::freeSeek(const Vector<3>& target) {
	float ratio = mlength / distance(mposition, target);
	mposition = (1.0f - ratio) * target + ratio * mposition;
	mend = target;
	// Keep track of other axes
}

void HingeBone::rfreeSeek(const ChainMember& previous) {
	float ratio = mlength / distance(mend, previous.end());
	mposition = previous.end();
	mend = (1.0f - ratio) * previous.end() + ratio * mend;
}

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
	float ratio = mlength / distance(mend, previous.end());
	setPosition(previous.end());
	setEnd((1.0f - ratio) * previous.end() + ratio * mend);

	/*	The below is equivelant to this but optimized for reduced memory
	Vector<3> projection = mend.planarProjection(previous.rotationAxis(), previous.end());
	Vector<3> newDir = (projection - position()).normalised();
	setEnd(mposition + newDir * length());*/

	// Clamp to the correct axis
	setDirection((mend.planarProjection(previous.end(), previous.direction()) - mposition).normalised());
	setEnd(mposition + mdirection * mlength);

	// Clamp angle like implemented in Segments
}