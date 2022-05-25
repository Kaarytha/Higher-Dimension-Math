#pragma once

#include "defines.h"

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

	template<typename T>
	struct Tensor;

	template<typename T>
	struct StridedTensor {
		std::vector<T> mdata;
		ArrayShape mshape;
		std::vector<std::size_t> mstrides;
		int moffset;

		StridedTensor() {
			"default constructed!";
		};

		StridedTensor(const ArrayShape& shape, const std::initializer_list<T>& data);
		StridedTensor(ArrayShape&& shape, const std::initializer_list<T>& data);
		StridedTensor(Tensor<T>&& other) noexcept;
		explicit StridedTensor(const StridedTensor& other);
		StridedTensor(StridedTensor&& other) noexcept;

		template<typename E>
		StridedTensor(const E& other);

		T operator[](const ArrayShape& location);
		T operator[](const int& index) const;
		T& operator[](const int& index);

		template<typename E>
		auto& operator=(const E& other);

		ArrayShape shape() const;
		void reshape(const ArrayShape& shape) { mshape = shape; };
		auto size() const { return mdata.size(); };
		auto strides() const { return mstrides; };
		void describe();

	protected:
		std::vector<std::size_t> mmultiples;

	private:
		std::string toString(int index);
	};

	// StridedTensor Implementation
	template<typename T>
	StridedTensor<T>::StridedTensor(const ArrayShape& shape, const std::initializer_list<T>& data) : mshape(shape), mdata(data) {
		int multiple = 1;
		mstrides.resize(mshape.size());

		for (int i = mshape.size() - 1; i >= 0; --i) {
			mstrides[i] = multiple;
			multiple *= mshape[i];
		}

		mmultiples = mstrides;
		moffset = 0;

		std::cout << "shape copied!";
	};

	template<typename T>
	StridedTensor<T>::StridedTensor(ArrayShape&& shape, const std::initializer_list<T>& data) : mshape(std::move(shape)), mdata(data) {

		int multiple = 1;
		mstrides.resize(mshape.size());

		for (int i = mshape.size() - 1; i >= 0; --i) {
			mstrides[i] = multiple;
			multiple *= mshape[i];
		}

		moffset = 0;

		std::cout << "shape moved!";
	};

	template<typename T>
	StridedTensor<T>::StridedTensor(Tensor<T>&& other) noexcept : mshape(std::move(other.mshape)), mdata(std::move(other.mdata)),
	mmultiples(std::move(other.multiples())) {

		int multiple = 1;
		mstrides.resize(mshape.size());

		for (int i = mshape.size() - 1; i >= 0; --i) {
			mstrides[i] = multiple;
			multiple *= mshape[i];
		}

		moffset = 0;

		std::cout << "Tensor move converted!";
	}

	template<typename T>
	StridedTensor<T>::StridedTensor(const StridedTensor& other) {
		mdata = other.mdata;
		mshape = other.mshape;
		mstrides = other.mstrides;
		moffset = other.mstrides;

		std::cout << "StridedTensor copied!";
	}

	template<typename T>
	StridedTensor<T>::StridedTensor(StridedTensor&& other) noexcept : mshape(std::move(other.mshape)), mdata(std::move(other.mdata)),
		mstrides(std::move(other.mstrides)), moffset(std::move(other.moffset)), mmultiples(std::move(other.mmultiples)) {
		std::cout << "StridedTensor moved!";
	};

	template<typename T>
	template<typename E>
	StridedTensor<T>::StridedTensor(const E& other) {
		// Needs to assert that it is an expr
		int dif = other.size() - size();
		if (dif != 0) mdata.resize(other.size());
		mshape = other.shape();
		//mstrides = other.strides();
		
		int multiple = 1;
		mstrides.resize(mshape.size());

		for (int i = mshape.size() - 1; i >= 0; --i) {
			mstrides[i] = multiple;
			multiple *= mshape[i];
		}

		for (int i = 0; i < mdata.size(); ++i) {
			mdata[i] = other[i];
		}
		std::cout << "Strided constructed from Expression!";
	}

	template<typename T>
	template<typename E>
	auto& StridedTensor<T>::operator=(const E& other) {
		// Needs to assert that it is an expr
		int dif = other.size() - size();
		if (dif != 0) mdata.resize(other.size());
		mshape = other.shape();
		//mstrides = other.strides();

		int multiple = 1;
		mstrides.resize(mshape.size());

		for (int i = mshape.size() - 1; i >= 0; --i) {
			mstrides[i] = multiple;
			multiple *= mshape[i];
		}



		for (int i = 0; i < mdata.size(); ++i) {
			mdata[i] = other[i];
		}
		std::cout << "Expression assigned to Strided!";
		return *this;	// If return type is auto, calls constructor StridedTensor(const StridedTensor& other);
	}

	template<typename T>
	T StridedTensor<T>::operator[](const ArrayShape& location) {
		int target = moffset;

		for (int i = 0; i < location.size(); ++i) {
			target += mstrides[i] * (location[i] - 1);
		}
		return mdata[target];
	}

	template<typename T>
	T StridedTensor<T>::operator[](const int& index) const {
		ArrayShape location;
		int ind = index;
		location.resize(mshape.size(), 1);
		
		for (int i = 0; i < mshape.size(); ++i) {
			if (i = mshape.size() - 1) {
				location[i] = ind + 1;
			}
			else {
				int temp = ind / mmultiples[i];
				location[i] = temp + 1;
				ind -= temp * mmultiples[i];
			}
		}

		int target = moffset;

		for (int i = 0; i < location.size(); ++i) {
			target += mstrides[i] * (location[i] - 1);
		}
		return mdata[target];
	}

	template<typename T>
	T& StridedTensor<T>::operator[](const int& index) {
		ArrayShape location;
		int ind = index;
		location.resize(mshape.size(), 1);

		for (int i = 0; i < mshape.size(); ++i) {
			if (i = mshape.size() - 1) {
				location[i] = ind + 1;
			}
			else {
				int temp = ind / mmultiples[i];
				location[i] = temp + 1;
				ind -= temp * mmultiples[i];
			}
		}

		int target = moffset;

		for (int i = 0; i < location.size(); ++i) {
			target += mstrides[i] * (location[i] - 1);
		}
		return mdata[target];
	}



	template<typename T>
	ArrayShape StridedTensor<T>::shape() const {
		return mshape;
	}

	template<typename T>
	void StridedTensor<T>::describe() {

		mmultiples.resize(mshape.size());

		int mult = 1;
		for (int i = mshape.size() - 1; i >= 0; --i) {
			mult *= mshape[i];
			mmultiples[i] = mult;
		}

		std::cout << toString(0);
	};

	template<typename T>
	std::string StridedTensor<T>::toString(int index) {
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
}