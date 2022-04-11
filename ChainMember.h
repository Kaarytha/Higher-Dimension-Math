#pragma once
#include <memory>
#include <vector>
#include "Math.h"

class ChainMember {
protected:
	Vector<3> mposition;
	Vector<3> mdirection; // UV
	float mlength;

public:
	ChainMember();
	virtual ~ChainMember();
	Vector<3> position();
	void setPosition(Vector<3> target);
	float length();
	virtual void freeSeek(Vector<3> target);
	virtual void constrainedSeek(const Vector<3>& target);
};

class HingeBone : ChainMember {
private:
	Vector<3> mrotationAxis;	// Testing with global members first
public:
	HingeBone();
	void freeSeek(Vector<3> target);
	void constrainedSeek(Vector<3> target);
};