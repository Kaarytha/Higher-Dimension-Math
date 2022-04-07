#pragma once
#define _USE_MATH_DEFINES

#include "Math.h"
#include <cmath>
#include <vector>

class Segment2 {

public:
	struct Vector2 mendA, mendB, mdir;
	float mmag, mangle; // Angle with respect to parent
	int mparent;

private:
	float mnegAngleConstraint, mposAngleConstraint; // With respect to parent
	
	int mid;
	static int seg2Count;

public:
	Segment2();
	~Segment2();
	Segment2(Vector2 A, Vector2 B, float posConstraint = M_PI, float negConstraint = (-M_PI));
	Segment2(Vector2 parentB, float posConstraint = M_PI, float negConstraint = (-M_PI));
	// Segment2(const Segment2 &parent);
	void updateA(Vector2 target);
	void updateB(Vector2 target);
	float findAngle(Segment2 parent);
	void rectifyAngle(Segment2 parent); // Should probably be a template
	struct Vector2 getEndB();

	void debugPrint();
	void printA();
	void printB();
	void printMDir();
};

class Segment3 {
public:
	struct Vector3 mendA, mendB, mdir;
	float mmag, phi, theta; // Angle is pointless, we need unsigned phi and theta, will be needed for a rectifyAngle3()
	int mparent;

private:
	float mnegThetaConstraint, mposThetaConstraint, mphiConstraint;
	int mid;
	static int seg3Count;

public:
	Segment3();
	Segment3(Vector3 parentB, float phiConstraint = M_PI, float posThetaConstraint = M_PI, float negThetaConstraint = -M_PI);
	void updateA(Vector3 target);
	void updateB(Vector3 target);

	//Segment3(const Segment3 &parent);
	void debugPrint();
};

// I want to pass the address of previous T in vector target to T constructor
template <typename T>
void createBranch(std::vector<T>& target, int segNum) {
	target.reserve(segNum);
	target.emplace_back(T());

	for (int i = 1; i < segNum; i++) {
//		T* temp = new T(target[i - 1].mendB);	// Bad code but will be useful to understand what is happening
		target.emplace_back(T(target[i - 1].mendB));
	}
}


// Performs FABRIK towards goal

// How can I move the definition to a different file to keep the header clean?
// What happens if it is a vector of Segment3 and the goal is a Vector2?
	// This should never happen
template<typename T, typename U>
int seek(std::vector<T>& activeBranch, U goal, int iterations = 25, float accuracy = .001) {
	U target;
	U root = activeBranch[0].mendA;

	// Should be changed to for vector& i in activeBranch type thing
	for (int j = 0; j < iterations; j++) {

		target = goal;

		// Forwards (towards goal)
		for (int i = activeBranch.size() - 1; i >= 0; i--) {
			U targetDir = (target - activeBranch[i].mendA) / distance(activeBranch[i].mendA, target);
			activeBranch[i].mendB = target;
			activeBranch[i].updateA(target - activeBranch[i].mmag * targetDir);

			target = activeBranch[i].mendA;
		}

		target = root;

		// Backwards (towards root)
		for (T& i : activeBranch) {
			U targetDir = (target - i.mendB) / distance(i.mendB, target);
			i.mendA = target;
			i.updateB(target - i.mmag * targetDir);

			target = i.mendB;
		}


		// Uncomment to see all steps
		for (T& i : activeBranch) {
			i.debugPrint();
		}
		std::cout << std::endl;

		/*for (T i : activeBranch) {
			i.rectifyAngle();
		}*/
	}

	std::cout << "Remember to comment out the print statement when finished" << std::endl;
	if (distance(activeBranch[activeBranch.size() - 1].mendB, goal) <= accuracy) {
		return 1;
	}
	else return 0;
}