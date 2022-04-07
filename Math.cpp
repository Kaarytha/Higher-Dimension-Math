#include "Math.h"
#include <iostream>

Vector2::Vector2() {
	mx = 0;
	my = 0;
}

Vector2::Vector2(float x, float y) {
	mx = x;
	my = y;
}

Vector3 Vector2::toVec3() {
	return Vector3(mx, my, 0);
}

Vector2& Vector2::operator =(const Vector2& a) {
	mx = a.mx;
	my = a.my;
	return *this;
}

Vector2& Vector2::operator +(const Vector2& a) {
	Vector2 temp = Vector2(mx + a.mx, my + a.my);
	return temp;
}

Vector2& Vector2::operator +=(const Vector2& a) {
	*this = *this + a;
	return *this;
}

Vector2& Vector2::operator -(const Vector2& a) {
	Vector2 temp = Vector2(mx - a.mx, my - a.my);
	return temp;
}

Vector2& Vector2::operator -=(const Vector2& a) {
	*this = *this - a;
	return *this;
}

Vector2& Vector2::operator *(const float& a) { // Does this work or have the same issue as
	Vector2 temp = Vector2(mx * a, my * a);		// commented out / operator?
	return temp;
}

Vector2& Vector2::operator *=(const float& a) {
	*this = *this * a;
	return *this;
}

//This code causes issues as the values of mx and my are not updated and instead
//use whatever was in there before

//Vector2& Vector2::operator /(const float& a) {
//	Vector2 temp = Vector2(mx / a, my / a); // 
//	return temp;
//}

Vector2& Vector2::operator /=(const float& a) {
	*this = *this / a;
	return *this;
}

Vector2 operator *(float i, const Vector2& a) {
	Vector2 temp = Vector2(a.mx * i, a.my * i);
	return temp;
}

Vector2 operator /(float i, const Vector2& a) {
	Vector2 temp = Vector2(a.mx / i, a.my / i);
	return temp;
}

Vector2 operator /(Vector2 i, const float& a) {
		Vector2 temp = Vector2(i.mx / a, i.my / a);
		return temp;
}


Vector3::Vector3() {
	mx = 0;
	my = 0;
	mz = 0;
}

Vector3::Vector3(float x, float y, float z) {
	mx = x;
	my = y;
	mz = z;
}

Vector3& Vector3::operator +(const Vector2& a) {
	Vector3 temp = Vector3(mx + a.mx, my + a.my, mz);
	return temp;
}

Vector3& Vector3::operator +(const Vector3& a) {
	Vector3 temp = Vector3(mx + a.mx, my + a.my, mz + a.mz);
	return temp;
}

Vector3& Vector3::operator -(const Vector2& a) {
	Vector3 temp = Vector3(mx - a.mx, my - a.my, mz);
	return temp;
}

Vector3& Vector3::operator -(const Vector3& a) {
	Vector3 temp = Vector3(mx - a.mx, my - a.my, mz - a.mz);
	return temp;
}

Vector3& Vector3::operator *(const float& a) {
	Vector3 temp = Vector3(mx * a, my * a, mz * a);
	return temp;
}

//Vector3& Vector3::operator /(const float& a) {
//	Vector3 temp = Vector3(mx / a, my / a, mz / a);
//	return temp;
//}

Vector3 operator *(float i, const Vector3& a) {
	Vector3 temp = Vector3(i * a.mx, i * a.my, i * a.mz);
	return temp;
}

Vector3 operator *(const Vector3 a, float& i) {
	Vector3 temp = Vector3(i * a.mx, i * a.my, i * a.mz);
	return temp;
}

Vector3 operator /(Vector3 i, const float& a) {
	Vector3 temp = Vector3(i.mx / a, i.my / a, i.mz / a);
	return temp;
}


std::ostream& operator <<(std::ostream& os, Vector2 a) {	// Should these be overloaded with Vector2& a instead?
	os << a.mx << ", " << a.my;
	return os;
}

std::ostream& operator <<(std::ostream& os, Vector3 a) {
	os << a.mx << ", " << a.my << ", " << a.mz;
	return os;
}

float distance(Vector2 a, Vector2 b) {
	return sqrt((pow((b.mx - a.mx), 2.0) + pow((b.my - a.my), 2.0))); // Would it be faster to simply do if{x<0}: x = 0 - x
}

float distance(Vector3 a, Vector3 b) {
	return sqrt((pow((b.mx - a.mx), 2.0) + pow((b.my - a.my), 2.0) + pow((b.mz - a.mz), 2.0)));
}

float dotProduct(Vector2 a, Vector2 b) {
	float product = (a.mx * b.mx + a.my * b.my);
	return product;
}