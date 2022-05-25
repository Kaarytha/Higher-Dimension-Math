#pragma once

#include <vector>
#include <initializer_list>
#include <iostream>
#include <string>
#include <array>
#include <cassert>
#include <tuple>
#include <type_traits>

#include "ArrayShape.h"
#include "Expression.h"

namespace NAMESPACE {
	// Tensor Declaration
	// Non strided array

	// Forward declaration
	template<typename T>
	struct StridedTensor;

	template<typename T>
	struct Tensor {
		std::vector<T> mdata;
		ArrayShape mshape;

		Tensor() {
			"default constructed!";
		};
		Tensor(const ArrayShape& shape, const std::initializer_list<T>& data);
		Tensor(ArrayShape&& shape, const std::initializer_list<T>& data);
		explicit Tensor(const Tensor& other);
		Tensor(Tensor&& other) noexcept;
		Tensor(const std::vector<T>& data);

		StridedTensor<T> toStrided() {
			StridedTensor<T> temp = StridedTensor<T>(std::move(*this));
			std::cout << "Strided created from Tensor!";
			return temp;
		};

		template<typename E>
		//requires(std::is_base_of_v<Expression, std::remove_cvref_t<E>>)
		Tensor(const E& other);

		template<typename E>
		auto& operator=(const E& other);

		//template<typename S>
		//S operator=(S&& other) {

		//}

		T operator[](const ArrayShape& location);
		T operator[](const int& index) const { return mdata[index]; };
		T& operator[](const int& index) { return mdata[index]; };		// Not sure if this is necessary
		


		ArrayShape shape() const;
		void reshape(const ArrayShape& shape) { mshape = shape; };
		std::size_t size() const { return mdata.size(); };
		std::vector<std::size_t> multiples() const { return mmultiples; };

		void describe();

	protected:
		std::vector<std::size_t> mmultiples;	// probably a temporary solution for describe

	private:
		std::string toString(int index);
	};

	// Tensor Implementation
	template<typename T>
	Tensor<T>::Tensor(const ArrayShape& shape, const std::initializer_list<T>& data) : mshape(shape), mdata(data) {
		std::cout << "shape copied!";

	};

	template<typename T>
	Tensor<T>::Tensor(ArrayShape&& shape, const std::initializer_list<T>& data) : mshape(std::move(shape)), mdata(data) {
		std::cout << "shape moved!";
	};

	template<typename T>
	Tensor<T>::Tensor(const Tensor& other) {
		mshape = other.mshape;
		mdata = other.mdata;
		std::cout << "copied!";
	}

	template<typename T>
	Tensor<T>::Tensor(Tensor&& other) noexcept : mshape(std::move(other.mshape)), mdata(std::move(other.mdata)), mmultiples(std::move(other.mmultiples)) {
		std::cout << "Tensor moved!";
	};

	template<typename T>
	Tensor<T>::Tensor(const std::vector<T>& data) {
		mdata = data;
	}













	template<typename T>
	template<typename E>
	//requires(std::is_base_of_v<Expression, std::remove_cvref_t<E>>)
	Tensor<T>::Tensor(const E& other) {
		int dif = other.size() - size();
		if (dif != 0) mdata.resize(other.size());
		mshape = other.shape();

		for (int i = 0; i < mdata.size(); ++i) {
			mdata[i] = other[i];
		}
		std::cout << "Tensor constructed from expr!";
	}

	template<typename T>
	template<typename E>
	auto& Tensor<T>::operator=(const E& other) {
		// Needs to assert that it is an expr
		int dif = other.size() - size();
		if (dif != 0) mdata.resize(other.size());
		mshape = other.shape();

		for (int i = 0; i < mdata.size(); ++i) {
			mdata[i] = other[i];
		}
		std::cout << "expression assigned!";
		return *this;	// If return type is auto, calls constructor Tensor(const Tensor& other);
	}

	template<typename T>
	T Tensor<T>::operator[](const ArrayShape& location) {
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
	ArrayShape Tensor<T>::shape() const {
		return mshape;
	}

	template<typename T>
	void Tensor<T>::describe() {
		mmultiples.resize(mshape.size());

		int mult = 1;
		for (int i = mshape.size() - 1; i >= 0; --i) {
			mult *= mshape[i];
			mmultiples[i] = mult;
		}

		std::cout << toString(0);
	};

	template<typename T>
	std::string Tensor<T>::toString(int index) {
		std::string temp = std::to_string(mdata[index]);

		if ((index + 1) % mshape.back() == 0) {
			std::string end;
			for (auto it = mmultiples.begin(); it != mmultiples.end() - 1; ++it) {
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
				if ((index) % mmultiples[i] == 0) {
					beginning += "{";
				}
			}
			return beginning + temp + ", " + toString(index + 1);
		}
		else {
			return temp + ", " + toString(index + 1);
		}
	}






	//	template<typename T>
	//	constexpr bool is_array_or_expression =
	//		std::is_array_v<T> || std::is_base_of_v<expr, std::remove_cvref_t<T>>;

	//	template<typename Left, typename Right>
	//	constexpr bool is_binary_op_ok =
	//		is_array_or_expression<Left> || is_array_or_expression<Right>;

	//	template<typename Left, typename Right>
	//	//requires(is_binary_op_ok<Left, Right>)
	//	auto operator+(const Left& left, const Right& right) {
	//		return expr{ [](const auto& l, const auto& r) {return l + r; }, left, right };
	//	}
	//}
}







///* Usage
//* 
//* Tensor<float> Tensor1 = {{1, 2, 3}, {4, 5, 6}} creates a 2x3 two dimensional Tensor
//*	Shape is created for this Tensor automatically
//* 
//* Tensor<float> Tensor2 {{1, 2, 3}, {4, 5, 6}} does the same
//* 
//*/



/* Works, compiler does some optimizations so Tensor<int> temp = first + second calls a constructor instead of assignment operator
#include <vector>
#include <type_traits>
#include <iostream>
#include <tuple>
#include <initializer_list>
#include <cassert>



template<typename T>
class Vector{
	std::vector<T> mdata;

	public:
	Vector() = default;
	Vector(const std::vector<T>& other): mdata(other){};
	Vector(const std::initializer_list<T>& data){
		for(auto it : data){
			mdata = data;
		}
	}

	template<typename E>
	auto operator=(const E& other){

		for(int i = -2; i < (other.size() - size()); ++i) mdata.emplace_back(0);
		for(int i = 0; i < mdata.size(); ++i){
			mdata[i] = other[i];
		}
		return *this;
	}
	T operator[](const int& index) const {
		return mdata[index];
	}
	T& operator[](const int& index) {return mdata[index];};

	friend std::ostream& operator<<(std::ostream& out, const Vector<T>& vec){
		for(int i = 0; i < vec.mdata.size(); ++i){
			out << vec[i] << ", ";
		}
		return out;
	}

	std::size_t size() const {return mdata.size();};
};

template<typename T, typename... Args>
class Expr{
	std::tuple<const Args&...> margs;
	T mfunc;

	public:

	Expr(T func, const Args&... args): mfunc(func), margs(args...) {};

	auto operator[](const int& index) const {
		const auto func = [this, index](const Args&... args){
			return mfunc(args[index]...);
		};
		return std::apply(func, margs);
	}

	friend std::ostream& operator<<(std::ostream& out, const Expr& data){
		for(int i = 0; i < 2; ++i){
			out << data[i] << ", ";
		}
		return out;
	}

	auto size() const {
		return std::get<0>(margs).size();
	}
};

template<typename Left, typename Right>
auto operator+(const Left& left, const Right& right){
	return Expr{ [](const auto& l, const auto& r){return l + r;}, left, right};
}

int main(){
	Vector<int> first{1, 2, 3, 4};
	Vector<int> second{1,1,1,1};
	Vector<int> third;
	third = first + second;

	std::cout << "\n\n\n\n";
	std::cout << first.size();

	std::cout << third;
}*/

/* Create simple robot that looks at person
* 1. Uses IK system that users Tensors
* 2. Uses opencv testing to find person
* 3. calculates change in orientation and looks 
*		for straight lines to get correct orientation
*/



/*
* std::array<int, mshape.size()> h;
* h.fill(1);
* 
* 
* 
* 
* 
*/