#pragma once
#include <memory>
#include <vector>
#include "Vector.h"
#include "Range.h"


/*  Polymorphic base class structure
*	All ChainMembers are three dimensional
*/
class ChainMember {
protected:
	Vector<3> mposition;	// absolute
	Vector<3> mend;			// absolute
	Vector<3> mdirection;	// UV relative to mposition orthogonal to mreference
	Vector<3> mreference;	// absolute vector lying in working plane used with mdirection to derive rotation, maxis to derive spin
	float mlength;

public:
	virtual ~ChainMember() {};
	const Vector<3>& position() const;
	const Vector<3>& end() const;
	const Vector<3>& direction() const;
	const Vector<3>& reference() const;
	const float length() const;

	void setPosition(const Vector<3>& target);
	void setEnd(const Vector<3>& target);
	void setDirection(const Vector<3>& direction);
	void setReference(const Vector<3>& reference);

	void update(const Vector<3>& target);
	virtual void freeSeek(const Vector<3>& target) {};
	virtual void rfreeSeek(const ChainMember& previous) {};
	virtual void rfreeSeek(const Vector<3>& target) {};
	virtual void constrainedSeek(const ChainMember& next) {};
	virtual void rconstrainedSeek(const ChainMember& previous) {};
};


/*	Serves to change working plane and orientation of other joints
* 
* 
* 
* 
*/
//class SpinBone : public ChainMember {
//	float mspin;			// relative rotation along direction vector
//	Range mspinConstraints;
//public:
//	SpinBone() = default;
//	~SpinBone() = default;
//
//	void freeSeek(const Vector<3>& target) = 0;	// might be able to move free seeks to base class
//	void rfreeSeek(const ChainMember& previous) = 0;
//	void rfreeSeek(const Vector<3>& target) = 0;
//	void constrainedSeek(const ChainMember& next) = 0;
//	void rconstrainedSeek(const ChainMember& previous);
//};

/*	Rotates in 2 dimesions
* 
* 
*/
class HingeBone : public ChainMember {
	Hyperplane<3> mplane;	// Absolute working plane, mplane.mpoint is the same as mposition, how can we avoid this?
	Range mrotationConstraints;

public:
	//using ChainMember::rfreeSeek;

	HingeBone();
	~HingeBone() = default;
	Vector<3> normal() const;

	void freeSeek(const Vector<3>& target);
	//void rfreeSeek(const ChainMember& previous);
	void rfreeSeek(const Vector<3>& target);
	void constrainedSeek(const ChainMember& next);
	void rconstrainedSeek(const ChainMember& previous);
};

/*	Each hinge needs to store it's working plane in relation
* to previous.reference() and possibly previous.direction()
*/

/*	Consider a heavily constrained chain ( such as one with only one angle for each joint 
*	besides the root ) that curves to one side
*	
*	The method of freeSeek(target), rconstrainedSeek(root) would not approach the target
* 
*	Continued iterations would approach the point that creates a line tangent to the circular area
*	in the range of the chain on the side with acute angles
*	
*	What amount of freedom in the joints is necessary to converge on or near the target?
*/