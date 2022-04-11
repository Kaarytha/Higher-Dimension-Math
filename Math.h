#pragma once
#include <iostream>
#include <array>

/*	Vector class with arbitrary number of float components.
* 
*	Called as Vector<int numOfComponents> name{std::initializer_list<float> coords};
*	If coords is empty, a zero vector will be created;
* 
*/
template<int I>
struct Vector {
	std::array<float, I> mcoords;

	Vector() {
		mcoords.fill(0);
	}

	// Allows for Vector<3> vec3{3,5,7};
	Vector(std::initializer_list<float> coords) {
		for (int i = 0; i < I; ++i) {
			mcoords[i] = *(coords.begin() + i);
		}
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

	// Gets component comp value, for example, Component(1) gets the firt component
	float Component(int comp) {
		return mcoords[comp - 1];
	}

	Vector& operator =(const Vector& other) {
		mcoords = other.mcoords;
		return *this;
	}
	Vector operator +(const Vector& other) {
		Vector<I> temp;
		for (int i = 0; i < I; ++i) {
			temp.mcoords[i] = mcoords[i] + other.mcoords[i];
		}
		return temp;
	}
	Vector& operator +=(const Vector& other) {
		for (int i = 0; i < I; ++i) {
			mcoords[i] += other.mcoords[i];
		}
		return *this;
	}
	Vector operator -(const Vector& other) {
		Vector<I> temp;
		for (int i = 0; i < I; ++i) {
			temp.mcoords[i] = mcoords[i] - other.mcoords[i];
		}
		return temp;
	}
	Vector& operator -=(const Vector& other) {
		for (int i = 0; i < I; ++i) {
			mcoords[i] -= other.mcoords[i];
		}
		return *this;
	}
	Vector operator *(const float& factor) {
		Vector<I> temp;
		for (int i = 0; i < I; ++i) {
			temp.mcoords[i] = mcoords[i] * factor;
		}
		return temp;
	}
	friend Vector operator *(const float& factor, const Vector& vec) {
		Vector<I> temp;
		for (int i = 0; i < I; ++i) {
			temp.mcoords[i] = factor * vec.mcoords[i];
		}
		return temp;
	}
	Vector& operator *=(const float& factor) {
		for (auto& it : mcoords) {
			it *= factor;
		}
		return *this;
	}
	Vector operator /(const float& factor) {
		Vector<I> temp;
		for (int i = 0; i < I; ++i) {
			temp.mcoords[i] = mcoords[i] / factor;
		}
		return temp;
	}
	Vector& operator /=(const float& factor) {
		for (auto& it : mcoords) {
			it /= factor;
		}
		return *this;
	}

	friend std::ostream& operator <<(std::ostream& out, const Vector<I>& vec) {
		for (int i = 0; i < I - 1; ++i) {
			out << vec.mcoords[i] << ", ";
		}
		return out << vec.mcoords.back();
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