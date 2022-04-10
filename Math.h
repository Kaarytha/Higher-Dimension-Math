#pragma once
#include <iostream>
#include <array>
#include <cstdarg>


// Vector<3> vec3( {3,5,7} );
template<int I>
struct Vector {
	std::array<float, I-1> mcoords;


	Vector(std::initializer_list<float> coords) {
		for (int i = 0; i < I - 1; ++i) {
			mcoords[i] = coords[i];
		}
	}
	
	// Need a conversion constructor so we can do things like Vector<5> + Vector<3>
	// Or check to make sure vector being added has fewer or equal dimensions and iterate over other.mcoords

	Vector(const Vector& other) {
		mcoords = other.mcoords;
	}
	
	float Component(int comp) {
		return mcoords[comp-1];
	}

	Vector& operator +(const Vector& other) {
		Vector<I> temp;
		for (int i = 0; i < I; ++i) {
			temp.mcoords[i] = mcoords[i] + other.mcoords[i]
		}

		return temp;
	}
	Vector& operator +=(const Vector& other) {
		for (int i = 0; i < I; ++i) {
			mcoords[i] += other.mcoords[i]
		}

		return temp;
	}
	Vector& operator -(const Vector& other) {
		Vector<I> temp;
		for (int i = 0; i < I; ++i) {
			temp.mcoords[i] = mcoords[i] - other.mcoords[i]
		}

		return temp;
	}
	Vector& operator -=(const Vector& other) {
		for (int i = 0; i < I; ++i) {
			mcoords[i] -= other.mcoords[i]
		}

		return temp;
	}
	Vector& operator *(const float& factor) {
		Vector<I> temp;
		for (int i = 0; i < I; ++i) {
			temp.mcoords[i] = mcoords[i] * factor
		}

		return temp;
	}
	Vector& operator *=(const float& factor) {
		for (auto& it : mcoords) {
			it *= factor;
		}
	}
	Vector& operator /(const float& factor) {
		Vector<I> temp;
		for (int i = 0; i < I; ++i) {
			temp.mcoords[i] = mcoords[i] / factor
		}

		return temp;
	}
	Vector& operator /=(const float& factor) {
		for (auto& it : mcoords) {
			it /= factor;
		}
	}

	friend ostream& operator <<(ostream& out, const Vector& vec) {
		out << mcoords;
		return out;
	}
};




//typedef struct Vector2 {
//
//	float mx, my;
//
//public:
//	Vector2();
//	Vector2(float x, float y);
//
////	struct Vector3 toVec3();
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