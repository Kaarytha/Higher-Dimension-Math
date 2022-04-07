#pragma once
#include <memory>
#include <vector>
#include "Math.h"

// Should this be a template or should we store everything as joints in 3-space?
class ChainMember {
protected:
	Vector3 mposition;
	Vector3 mdirection;
	float mlength;

public:
	ChainMember();
	virtual ~ChainMember();
	Vector3 Position();
	void SetPosition(Vector3 target);
	float Length();
	virtual void FreeSeek(Vector3 target);
	virtual void ConstrainedSeek(Vector3 target);
};

class HingeBone : ChainMember {
private:
	Vector3 mrotationAxis;
public:
	HingeBone();
	void FreeSeek(Vector3 target);
	void ConstrainedSeek(Vector3 target);
};