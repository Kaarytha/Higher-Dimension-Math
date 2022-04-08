#pragma once
#include <iostream>

template<typename T>
struct Vector {
public:
	Vector();
	virtual ~Vector();
};

struct Vector2 : Vector<Vector2> {
private:
	float mx, my;

public:
	Vector2();
	Vector2(float x, float y);

	struct Vector3 toVec3();
};



//typedef struct Vector2 {
//
//	float mx, my;
//
//public:
//	Vector2();
//	Vector2(float x, float y);
//
//	struct Vector3 toVec3();
//	
//	Vector2& operator =(const Vector2& a);
//	Vector2& operator +(const Vector2& a);
//	Vector2& operator +=(const Vector2& a);
//	Vector2& operator -(const Vector2& a);
//	Vector2& operator -=(const Vector2& a);
//	Vector2& operator *(const float& a);
//	Vector2& operator *=(const float& a);
////	Vector2& operator /(const double& a); // Why does this not take in the correct values of the current Vector2 object?
//	Vector2& operator /=(const float& a);
//	
//
//	friend std::ostream& operator <<(std::ostream& os, Vector2 a);
//} Vector2;



//Vector2 operator *(float i, const Vector2& a); // Why are things like these are necessary in order to do double * Vector2
//Vector2 operator /(float i, const Vector2& a);
//Vector2 operator /(Vector2 i, const float& a);
//
//
//
//typedef struct Vector3 {
//	float mx, my, mz;
//
//public:
//	Vector3();
//	Vector3(float x, float y, float z);
//	void ProjectOntoPlane(Vector3 normal, Vector3 point);
//
//	Vector3& operator +(const Vector2& a);
//	Vector3& operator +(const Vector3& a);
//	Vector3& operator -(const Vector2& a);
//	Vector3& operator -(const Vector3& a);
//	Vector3& operator *(const float& a);
//	// Vector3& operator /(const double& a);
//
//
////	friend std::ostream& operator <<(std::ostream& os, Vector3 a);
//} Vector3;
//
//Vector3 operator *(float i, const Vector3& a);
//Vector3 operator /(Vector3 i, const float& a);
//Vector3 operator *(const Vector3 a, float& i);
//
//std::ostream& operator <<(std::ostream& os, Vector2 a);
//std::ostream& operator <<(std::ostream& os, Vector3 a);
//
//
////float distance(Vector2 a, Vector2 b);
//float distance(Vector3 a, Vector3 b);
//
//float dotProduct(Vector2 a, Vector2 b);
//
//template<typename T>
//T normalize(T vector) {
//	return vector / distance(vector, T());
//}