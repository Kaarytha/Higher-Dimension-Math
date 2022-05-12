#pragma once

#include <vector>
#include <initializer_list>
#include <iostream>
#include <string>
#include <array>

#include "TensorShape.h"

namespace NAMESPACE {
	// Tensor Declaration

	template<typename T>
	struct Tensor {
		Tensor(const TensorShape& shape, const std::initializer_list<T>& data) {
			mshape = shape;
			mdata = data;
		}

		TensorShape mshape;
		std::vector<T> mdata;

		T at(const TensorShape& location);

		void describe();

	private:
		std::string toString(int index);
		std::array<int, 100> multiples;	// probably a temporary solution for describe
	};

	// Tensor Implementation

	template<typename T>
	T Tensor<T>::at(const TensorShape& location) {
		int target = 0;

		for (int i = 0; i < location.size(); ++i) {
			int multiple = 1;
			for (auto it = mshape.begin() + i + 1; it != mshape.end(); ++it) {
				multiple *= *it;
			}
			target += (location[i] - 1) * multiple; //the rest of the array
		}

		return mdata[target];
	}

	template<typename T>
	void Tensor<T>::describe() {

		int mult = 1;
		for (int i = mshape.size() - 1; i >= 0; --i) {
			mult *= mshape[i];
			multiples[i] = mult;
		}


		std::cout << toString(0);
	};

	template<typename T>
	std::string Tensor<T>::toString(int index) {
		std::string temp = std::to_string(mdata[index]);

		if ((index + 1) % mshape.back() == 0) {
			std::string end;
			for (auto it = multiples.begin(); it != multiples.end() - 1; ++it) {
				if ((index + 1) % *it == 0) {
					end += "}";
				}
			}

			if (index + 1 == mdata.size()) {
				return temp + end;
			}


			return temp + end + ", " + toString(index + 1);
		}
		else if ((index) % mshape.back() == 0) {
			std::string beginning;
			for (int i = 0; i < mshape.size(); ++i) {
				if ((index) % multiples[i] == 0) {
					beginning += "{";
				}
			}
			return beginning + temp + ", " + toString(index + 1);
		}
		else {
			return temp + ", " + toString(index + 1);
		}
	}
}

// 2, 3, 4


//	// Tensor Declaration
//
//	template<typename T>
//	struct Tensor {
//		template<typename... Args>
//		Tensor(std::initializer_list<Args&& ...args>) {
//
//			if std::common_type_t<Args...> == float_t{
//				mshape.push_back(sizeof...(Args))
//			}
//			
//		}
//
//		std::vector<T> mdata;
//		TensorShape mshape;
//	};
//
//	// Tensor Implementation
//
//	//template<typename T>
//	//template<typename... Args>
//	//Tensor<T>::Tensor(std::initializer_list<Args&& ...args>) {
//
//	//}
//
//}
//
///* Usage
//* 
//* Tensor<float> tensor1 = {{1, 2, 3}, {4, 5, 6}} creates a 2x3 two dimensional tensor
//*	Shape is created for this tensor automatically
//* 
//* Tensor<float> tensor2 {{1, 2, 3}, {4, 5, 6}} does the same
//* 
//*/



//#include <initializer_list>
//#include <array>
//#include <iostream>
//
//template<typename T_first, typename... T_pack>
//constexpr T_first product(T_first first, T_pack... others) {
//    return first * product(others...);
//}
//
//template<typename T_last>
//constexpr T_last product(T_last last) {
//    return last;
//}
//
//template<typename T, std::size_t... Dimensions>
//class ndarray {
//public:
//    static constexpr std::size_t size() {
//        return product(Dimensions...);
//    }
//
//    ndarray(std::initializer_list<T> data) {
//        std::copy(data.begin(), data.end(), mdata.begin());
//    }
//
//    void print() {
//        for (auto& it : mdata) {
//            std::cout << it << ", ";
//        }
//        std::cout << std::endl;
//    }
//
//
//
//    std::array<T, size()> mdata;
//};








//#pragma once
//
//#include "defines.h"
//
//#include <vector>
//#include <initializer_list>
//#include <type_traits>
//
//#include "TensorShape.h"
//
//namespace NAMESPACE {
//
//	template<typename T, typename... Args>
//	T create(Args&&... args) {
//		return T(std::forward<Args>(args)...)
//	}
//
//	// Tensor Declaration
//
//	template<typename T>
//	struct Tensor {
//		template<typename... Args>
//		Tensor(std::initializer_list<Args&& ...args>) {
//
//			if std::common_type_t<Args...> == float_t{
//				mshape.push_back(sizeof...(Args))
//			}
//			
//		}
//
//		std::vector<T> mdata;
//		TensorShape mshape;
//	};
//
//	// Tensor Implementation
//
//	//template<typename T>
//	//template<typename... Args>
//	//Tensor<T>::Tensor(std::initializer_list<Args&& ...args>) {
//
//	//}
//
//}
//
///* Usage
//* 
//* Tensor<float> tensor1 = {{1, 2, 3}, {4, 5, 6}} creates a 2x3 two dimensional tensor
//*	Shape is created for this tensor automatically
//* 
//* Tensor<float> tensor2 {{1, 2, 3}, {4, 5, 6}} does the same
//* 
//*/