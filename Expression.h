#pragma once

#include <tuple>
#include <iostream>
#include <functional>
#include <type_traits>

#include "defines.h"
#include "ArrayShape.h"


namespace NAMESPACE {

	//template<typename T>
	//constexpr bool is_expr = std::is_base_of_v<Expression, T>;

	struct Expression {

	};

	template<typename T, typename... Args>
	class TensorExpr : public Expression{
		std::tuple<const Args&...> margs;
		T mfunc;

	public:

		TensorExpr(T func, const Args&... args) : mfunc(func), margs(args...) { std::cout << "Tensorexpr created!"; };

		auto operator[](const int& index) const {
			const auto func = [this, index](const Args&... args) {
				return mfunc(args[index]...);
			};
			return std::apply(func, margs);
		}

		friend std::ostream& operator<<(std::ostream& out, const TensorExpr& data) {
			for (int i = 0; i < 2; ++i) {
				out << data[i] << ", ";
			}
			return out;
		}

		auto size() const { return std::get<0>(margs).size(); };
		auto shape() const { return std::get<0>(margs).shape(); };
		auto strides() const { return std::get<0>(margs).strides(); };
	};

	// Create a specialization that only takes StridedTensors?
	template<typename Left, typename Right>
	auto operator+(const Left& left, const Right& right) {
		std::cout << "Tensoradd Expr created!";
		return TensorExpr{ [](const auto& l, const auto& r) {return l + r; }, left, right };
	}

	template<typename Left, typename Right>
	auto operator-(const Left& left, const Right& right) {
		std::cout << "Tensorsub Expr created!";
		return TensorExpr{ [](const auto& l, const auto& r) {return l - r; }, left, right };
	}

	//template<typename Left, typename Right>
	//auto operator*(const Left& left, const Right& right) {
	//	std::cout << "Tensormult Expr created!";
	//	return TensorExpr{ [](const auto& l, const auto& r) {return l * r; }, left, right };
	//}
}