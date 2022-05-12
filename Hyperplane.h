#pragma once
#include "Vector.h"

template<int I>
struct Vector;

template<int I>
struct Hyperplane {
	Vector<I> mpoint;
	Vector<I> mnormal;

	Hyperplane() {
		mpoint = Vector<I>();
		mnormal = Vector<I>();
	}

	Hyperplane(Vector<I> point, Vector<I> normal) {
		mpoint = point;
		mnormal = normal;
	}
};