#pragma once

#include "defines.h"

#include <vector>
#include <initializer_list>

namespace NAMESPACE {
	
	typedef std::vector<std::size_t> TensorShape;

	//struct TensorShape {
	//	std::vector<std::size_t> mdims;
	//	TensorShape() = default;
	//	TensorShape(const std::initializer_list<int>& dims);
	//	std::size_t operator[](const int& index) const;
	//};

	//// TensorShape implementation

	//TensorShape::TensorShape(const std::initializer_list<int>& dims) {
	//	for (auto& it : dims) {
	//		mdims.push_back(it);
	//	}
	//}

	//std::size_t TensorShape::operator[](const int& index) const {
	//	return mdims[index];
	//}

}