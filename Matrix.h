// A 2 dimensional tensor

#pragma once
#include <vector>
#include <memory>


struct Matrix {
	std::unique_ptr<std::vector<std::vector<float>>> mdata;
	std::unique_ptr<std::pair<int, int>> mdimensions;
	
	Matrix();
	Matrix(std::initializer_list<std::initializer_list<float>> values);
	Matrix(const std::vector<std::vector<float>>& data);
	Matrix(const Matrix& other);


	Matrix operator+(const Matrix& other) const;
	Matrix& operator+=(const Matrix& other);
	Matrix operator-(const Matrix& other) const;
	Matrix& operator-=(const Matrix& other);
	Matrix operator*(const Matrix& other) const;
	Matrix& operator*=(const Matrix& other);

	std::pair<int, int> Dimensions() const;
	bool isSquare();

	Matrix& transpose();

	friend Matrix innerProduct(Matrix& u, Matrix& v);
	friend Matrix externalProduct(Matrix& u, Matrix& v);
};