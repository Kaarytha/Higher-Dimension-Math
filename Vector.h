// A 1 dimensional Tensor

#pragma once

#include <iostream>
#include <array>
#include <cmath>
#include <numbers>
#include <functional>

#include "Hyperplane.h"
#include "Matrix.h"



template<int I>
struct Hyperplane;

struct Matrix;

/*	Vector class with arbitrary number of float components.
*	This is designed to be used efficiently with a few kinds of Vectors.
*	Using with many different kinds of Vectors results in significant bloat.
*/
template<int I>
struct Vector {
	std::array<float, I> mcoords;

	Vector() {
		mcoords.fill(0);
	}

	/*	Allows for Vector<3> vec3{3,5,7};
	*	Called as Vector<int numOfComponents> name{ std::initializer_list<float> coords };
	*	If coords is empty, a zero vector will be created;
	*/
	Vector(std::initializer_list<float> coords) {
		for (int i = 0; i < I; ++i) {
			mcoords[i] = *(coords.begin() + i);
		}
	}

	explicit Vector(std::array<float, I> coords) {
		mcoords = coords;
	}

	// Copy constructor only called if vectors have same number of components.
	// Check if commented out constructor below works fine
	template<int J>
	Vector(const Vector<J>& other, char(*)[I == J ? 1 : -1] = 0) {
		mcoords = other.mcoords;
	}
	//Vector(const Vector<I>& other) {
	//	mcoords = other.mcoords;
	//}

	// Conversion constructor that throws error when Vector's have different number of components
	template<int J>
	Vector(const Vector<J>& other, char(*)[I != J ? 1 : -1] = 0) {
		std::cerr << "Error: no conversion from Vector<" << I << "> to Vector<" << J << ">" << std::endl;
	}

	Vector& operator=(const Vector& other) {
		mcoords = other.mcoords;
		return *this;
	}
	Vector operator+(const Vector& other) const {
		Vector<I> temp;
		for (int i = 0; i < I; ++i) {
			temp.mcoords[i] = mcoords[i] + other.mcoords[i];
		}
		return temp;
	}
	Vector& operator+=(const Vector& other) {
		for (int i = 0; i < I; ++i) {
			mcoords[i] += other.mcoords[i];
		}
		return *this;
	}
	Vector operator-(const Vector& other) const {
		Vector<I> temp;
		for (int i = 0; i < I; ++i) {
			temp.mcoords[i] = mcoords[i] - other.mcoords[i];
		}
		return temp;
	}
	Vector& operator-=(const Vector& other) {
		for (int i = 0; i < I; ++i) {
			mcoords[i] -= other.mcoords[i];
		}
		return *this;
	}
	Vector operator*(const float& factor) const {
		Vector<I> temp;
		for (int i = 0; i < I; ++i) {
			temp.mcoords[i] = mcoords[i] * factor;
		}
		return temp;
	}
	friend Vector operator*(const float& factor, const Vector& vec) {
		Vector<I> temp;
		for (int i = 0; i < I; ++i) {
			temp.mcoords[i] = factor * vec.mcoords[i];
		}
		return temp;
	}
	Vector& operator*=(const float& factor) {
		for (auto& it : mcoords) {
			it *= factor;
		}
		return *this;
	}
	Vector operator/(const float& factor) const {
		Vector<I> temp;
		for (int i = 0; i < I; ++i) {
			temp.mcoords[i] = mcoords[i] / factor;
		}
		return temp;
	}
	Vector& operator/=(const float& factor) {
		for (auto& it : mcoords) {
			it /= factor;
		}
		return *this;
	}
	float operator[](const int& index) const { return mcoords[index]; }

	friend std::ostream& operator<<(std::ostream& out, const Vector<I>& vec) {
		for (int i = 0; i < I - 1; ++i) {
			out << vec.mcoords[i] << ", ";
		}
		return out << vec.mcoords.back();
	}

	// Gets component comp value, for example, Component(1) gets the firt component
	float component(int comp) {
		return mcoords[comp - 1];
	}

	// Returns the magnitude of the Vector as a float
	float magnitude() const {
		float mag = 0;
		for (auto& it : mcoords) {
			mag += it * it;
		}
		return std::sqrt(mag);
	}

	// Returns dot product of two Vectors as a float
	friend float dotProduct(const Vector<I>& a, const Vector<I>& b) {
		std::function<float(int)> helper = [&](int i) {
			if (i == I - 1) {
				return a.mcoords[i] * b.mcoords[i];
			}
			return a.mcoords[i] * b.mcoords[i] + helper(++i);
		};
		return helper(0);
	}

	// Returns distance between two Vectors as a float
	friend float distance(const Vector<I>& a, const Vector<I>& b) {
		std::function<float(int)> helper = [&](int i) {
			if (i == I - 1) {
				return std::sqrt(b.mcoords[i] - a.mcoords[i]);
			}
			return std::sqrt(b.mcoords[i] - a.mcoords[i]) + helper(++i);
		};
		return std::sqrt(helper(0));
	}

	// Scales Vector to a unit vector
	void normalise() {
		float mag = this->magnitude();
		for (auto it : mcoords) {
			it = it / mag;
		}
	}

	//Should this have an overload called on a pointer that so no temporary is created?
	// Returns an equivelant Vector scaled to a unit vector
	Vector<I> normalised() const {
		float mag = this->magnitude();
		std::array<float, I> coords;
		for (int i = 0; i < I; ++i) {
			coords[i] = mcoords[i] / mag;
		}
		return Vector<I>(coords);
	}

	// Returns a representation of the Vector as a matrix
	Matrix asMatrix() const {
		Matrix temp({ {mcoords} });
		return temp;
	}

	float angleFrom(const Vector<I>& other) const {
		return 180.0 * std::acos(dotProduct(*this, other)) / std::numbers::pi;
	}

	// Check if vectors need to be coplanar
	// Returns angle between two vectors
	float angleBetween(const Vector<I>& u, const Vector<I>& v) const {
		return 180. * std::acos(dotProduct(u, v)) / std::numbers::pi;
	}

	// Returns Vector projected onto plane through origin with Vector<I> normal
	Vector<I> planarProjection(const Vector<I>& normal) {
		Vector<I> norm = normal.normalise();
		return *this - dotProduct(this, norm) * norm;
	}

	// Returns Vector projected onto plane defined by Vector<I> point and Vector<I> normal
	Vector<I> planarProjection(const Vector<I>& point, const Vector<I>& normal) {
		Vector<I> norm = normal.normalised();
		return *this - (dotProduct(this, norm) - dotProduct(norm, point)) * norm;
	}

	Vector<I> planarProjection(const Hyperplane<I>& plane) {
		Vector<I> norm = plane.mnormal->normalised();
		return *this - (dotProduct(this, norm) - dotProduct(norm, plane.mpoint)) * norm;
	}

	Vector<3> rotatedAboutAxis(const Vector<3>& axis, const float& theta) {
		float sinTheta = std::sin(theta);
		float cosTheta = std::cos(theta);
		float oneMinusCos = 1. - cosTheta;

		float xyOne = axis[0] * axis[1] * oneMinusCos;
		float xzOne = axis[0] * axis[2] * oneMinusCos;
		float yzOne = axis[1] * axis[2] * oneMinusCos;

		Matrix rotMat = { {axis[0] * axis[0] * oneMinusCos + cosTheta, xyOne + axis[2] * sinTheta, xzOne - axis[1] * sinTheta},
			{xyOne - axis[2] * sinTheta, axis[1] * axis[1] * oneMinusCos + cosTheta, yzOne + axis[0] * sinTheta},
			{xzOne + axis[1] * sinTheta, yzOne - axis[0] * sinTheta, axis[2] * axis[2] * oneMinusCos + cosTheta} };

		return rotMat * *this.asMatrix().transpose();
	}
};

// For now, do not generalize rotations. Get rotations working in three dimensions since that is what we are working in
// Rotations should be spherical space rotations not euler planar rotations, this way, they can only happen one way
// Don't use getter and setters unless necessary

// Add optional variables for magnitude and norms

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