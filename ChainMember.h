#pragma once
#include <memory>
#include <vector>
#include "Vector.h"

/*  Polymorphic base class structure
*	All ChainMembers are three dimensional
*/
class ChainMember {
protected:
	Vector<3> mposition;
	Vector<3> mend;
	Vector<3> mdirection; // UV
	Vector<3> mreference;
	float mlength;

public:
	ChainMember();
	virtual ~ChainMember();
	const Vector<3>& position() const;
	const Vector<3>& end() const;
	const Vector<3>& direction() const;
	const Vector<3>& reference() const;
	const float length() const;

	void setPosition(const Vector<3>& target);
	void setEnd(const Vector<3>& target);
	void setDirection(const Vector<3>& direction);

	void update(const Vector<3>& target);
	virtual const Vector<3>& rotationAxis() const;
	virtual void freeSeek(const Vector<3>& target);
	virtual void rfreeSeek(const ChainMember& previous);
	virtual void rfreeSeek(const Vector<3>& target);
	virtual void constrainedSeek(const ChainMember& next);
	virtual void rconstrainedSeek(const ChainMember& previous);
};

class HingeBone : ChainMember {
public:
	HingeBone();

	void freeSeek(const Vector<3>& target);
	void rfreeSeek(const ChainMember& previous);
	void rfreeSeek(const Vector<3>& target);
	void constrainedSeek(const ChainMember& next);
	void rconstrainedSeek(const ChainMember& previous);
};