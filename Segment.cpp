//#define _USE_MATH_DEFINES
//
//#include "Vector.h"
//#include "Segment.h"
//#include <cmath>
//#include <iostream>
//#include <vector>
//
//
//int Segment3::seg3Count = 0;
//
//int Segment2::seg2Count = 0;
//
//
//Segment2::Segment2() {
//	mendA = Vector2(0.f, 0.f);
//	mendB = Vector2(0.f, 1.f);
//	mmag = distance(mendA, mendB);
//	mdir = (mendB - mendA) / mmag;
//	mnegAngleConstraint = (-M_PI);
//	mposAngleConstraint = M_PI;
//	mid = seg2Count;
//	seg2Count++;
//	mparent = mid - 1;
//	mangle = 0;
//}
//
//Segment2::~Segment2() {
//	// For a more complicated id system probably using a set
//	// Currently, there is no way to use id 4 if there has been 6 segments created and the 5th was destroyed
//	// The goal is to remove ids upon destruction so the lowest free id is used on segment creation
//}
//
//Segment2::Segment2(Vector2 A, Vector2 B, float posConstraint, float negConstraint) {
//	mendA = A;
//	mendB = B;
//	mmag = distance(mendA, mendB);
//	mdir = (mendB - mendA) / mmag;
//	mnegAngleConstraint = negConstraint;
//	mposAngleConstraint = posConstraint;
//	mid = seg2Count;
//	seg2Count++;
//	mparent = mid - 1;
//}
//
//// Creates segment at pointB of parent but does not attach them
//Segment2::Segment2(Vector2 parentB, float posConstraint, float negConstraint) {
//	mendA = parentB;
//	mendB = mendA + Vector2(0.f, 1.f);
//	mmag = distance(mendA, mendB);
//	mdir = (mendB - mendA) / mmag;
//	mnegAngleConstraint = negConstraint;
//	mposAngleConstraint = posConstraint;
//	mid = seg2Count;
//	seg2Count++;
//	mparent = mid - 1;
//}
//
////Segment2::Segment2(const Segment2 &parent) {		// This implementation creates a temporary segment which floats segcounts
////	mendA = parent.mendB;
////	mendB = mendA + Vector2(0.f, 1.f);
////	mmag = distance(mendA, mendB);
////	mdir = (mendB - mendA) / mmag;
////	mnegAngleConstraint = -M_PI;
////	mposAngleConstraint = M_PI;
////	mid = seg2Count;
////	seg2Count++;
////	mparent = mid - 1;
////}
//
//// Updates mendA and recalculates associated values
//void Segment2::updateA(Vector2 target) {
//	mendA.mx = target.mx;
//	mendA.my = target.my;
//	mmag = distance(mendA, mendB);
//	mdir = (mendB - mendA) / mmag;
//	// Might need to call findAngle(parent)
//}
//
//// Updates mendB and recalculates associated values
//void Segment2::updateB(Vector2 target) {
//	mendB.mx = target.mx;
//	mendB.my = target.my;
//	mmag = distance(mendA, mendB);
//	mdir = (mendB - mendA) / mmag;
//	// Needs to call findAngle(parent)
//}
//
//// Calculates mAngle
//float Segment2::findAngle(Segment2 parent) {
//	return acos(dotProduct(parent.mendB - parent.mendA, mendB - mendA) / (parent.mmag * mmag));
//}
//
//// Handles angles outside of constraints
//void Segment2::rectifyAngle(Segment2 parent) {
//	if (mangle < mnegAngleConstraint) {
//		float clampAngle = atan(parent.mdir.my / parent.mdir.mx) + mnegAngleConstraint;
//		updateB(mendA + mmag * Vector2(cos(clampAngle), sin(clampAngle)));
//		mangle = this->findAngle(parent);
//	}
//	else if (mangle > mposAngleConstraint) {
//		float clampAngle = atan(parent.mdir.my / parent.mdir.mx) + mposAngleConstraint;
//		updateB(mendA + mmag * Vector2(cos(clampAngle), sin(clampAngle)));
//		mangle = this->findAngle(parent);
//	}
//}
//
//Vector2 Segment2::getEndB() {
//	return mendB;
//}
//
//// Prints mendA, and mendB, and mdir of a segment
//void Segment2::debugPrint() {
//	std::cout << "Segment " << mid << ":" << std::endl;
//	std::cout << "    Point A: " << mendA << std::endl;
//	std::cout << "    Point B: " << mendB << std::endl;
//	std::cout << "    Magnitude: " << mmag << std::endl;
//	std::cout << "    Direction: " << mdir << std::endl;
//}
//
//// Prints mpointA of a segment
//void Segment2::printA() {
//	std::cout << "Segment ID: " << mid << ",    point A: " << mendA << std::endl;
//}
//
//// Prints mpointB of a segment
//void Segment2::printB() {
//	std::cout << "Segment ID: " << mid << ",    point B: " << mendB << std::endl;
//}
//
//// Prints mDir of a segment
//void Segment2::printMDir() {
//	std::cout << "Segment ID: " << mid << ",    Direction: " << mdir << std::endl;
//}
//
//
//Segment3::Segment3() {
//	mendA = Vector3(0.f, 0.f, 0.f);
//	mendB = Vector3(1.f, 0.f, 0.f);
//	mmag = distance(mendA, mendB);
//	mdir = (mendB - mendA) / mmag;
//	mphiConstraint = M_PI;
//	mnegThetaConstraint = -M_PI;
//	mposThetaConstraint = M_PI;
//	mid = seg3Count;
//	seg3Count++;
//	mparent = mid - 1;
//}
//
//// I want to be able to pass the address of a Segment3 instead of parentB
//
//Segment3::Segment3(Vector3 parentB, float phiConstraint, float posThetaConstraint, float negThetaConstraint) {
//	mendA = parentB;
//	mendB = mendA + Vector3(1.f, 1.f, 0.f);
//	mmag = distance(mendA, mendB);
//	mdir = (mendB - mendA) / mmag;
//	mphiConstraint = phiConstraint;
//	mnegThetaConstraint = negThetaConstraint;
//	mposThetaConstraint = posThetaConstraint;
//	mid = seg3Count;
//	seg3Count++;
//	mparent = mid - 1;
//}
//
////Segment3::Segment3(const Segment3 &parent) {		// This implementation creates a temporary segment which floats segcount
////	mendA = parent.mendB;
////	mendB = mendA + Vector3(1.f, 1.f, 0.f);
////	mmag = distance(mendA, mendB);
////	mdir = (mendB - mendA) / mmag;
////	mphiConstraint = M_PI_2;
////	mnegThetaConstraint = -M_PI;
////	mposThetaConstraint = M_PI;
////	mid = seg3Count;
////	seg3Count++;
////	mparent = mid - 1;
////}
//
//void Segment3::updateA(Vector3 target) {
//	mendA.mx = target.mx;
//	mendA.my = target.my;
//	mendA.mz = target.mz;
//	mmag = distance(mendA, mendB);
//	mdir = (mendB - mendA) / mmag;
//	// Might need to call findAngle(parent)
//}
//
//void Segment3::updateB(Vector3 target) {
//	mendB.mx = target.mx;
//	mendB.my = target.my;
//	mendB.mz = target.mz;
//	mmag = distance(mendA, mendB);
//	mdir = (mendB - mendA) / mmag;
//	// Might need to call findAngle(parent)
//}
//
//void Segment3::debugPrint() {
//	std::cout << "Segment " << mid << ":" << std::endl;
//	std::cout << "    Point A: " << mendA << std::endl;
//	std::cout << "    Point B: " << mendB << std::endl;
//	std::cout << "    Magnitude: " << mmag << std::endl;
//	std::cout << "    Direction: " << mdir << std::endl;
//}
//
//// Performs FABRIK towards goal
//
//// What happens if it is a vector of Segment3 and the goal is a Vector2?
//// Should this behavior simply not be allowed, the responsibility of the coder?