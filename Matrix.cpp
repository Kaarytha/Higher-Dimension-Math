#include "Matrix.h"

Matrix::Matrix() {
	mdata = nullptr;
	mdimensions = std::make_unique<std::pair<int, int>>(0, 0);
}

Matrix::Matrix(const std::vector<std::vector<float>>& data) {
	mdata = std::make_unique<std::vector<std::vector<float>>>(data);
	mdimensions = std::make_unique<std::pair<int, int>>(mdata->size(), (*mdata)[0].size());
}

Matrix::Matrix(const Matrix& other) {
	mdata = std::make_unique<std::vector<std::vector<float>>>(*other.mdata);	// This fixes seg faults
	*mdimensions = *other.mdimensions;
}

Matrix Matrix::operator+(const Matrix& other) const {
	if (*mdimensions != *other.mdimensions) {	// How can compiler know which Dimension to pick?
		//error
	}

	Matrix temp;

	for (int i = 0; i < mdata->size(); ++i) {
		for (int j = 0; j < mdata->at(i).size(); ++i) {
			(*temp.mdata)[i][j] = (*mdata)[i][j] + (*other.mdata)[i][j];
		}
	}

	return temp;
}

Matrix& Matrix::operator+=(const Matrix& other) {
	if ((*mdata)[0].size() != other.mdata->size()) {	// Use dimensions rather than checking size
//error
	}

	for (int i = 0; i < mdata->size(); ++i) {
		for (int j = 0; j < mdata->at(i).size(); ++i) {
			(*mdata)[i][j] += other.mdata->at(i)[j];
		}
	}

	return *this;
}

Matrix Matrix::operator-(const Matrix& other) const {
	if ((*mdata)[0].size() != other.mdata->size()) {	// Use dimensions rather than checking size
		//error
	}
	
	Matrix temp;

	for (int i = 0; i < mdata->size(); ++i) {
		for (int j = 0; j < mdata->at(i).size(); ++i) {
			temp.mdata->at(i)[j] = (*mdata)[i][j] - other.mdata->at(i)[j];
		}
	}

	return temp;
}

Matrix& Matrix::operator-=(const Matrix& other) {
	if ((*mdata)[0].size() != other.mdata->size()) {	// Use dimensions rather than checking size
	//error
	}

	for (int i = 0; i < mdata->size(); ++i) {
		for (int j = 0; j < mdata->at(i).size(); ++i) {
			(*mdata)[i][j] -= other.mdata->at(i)[j];
		}
	}
	
	return *this;
}

Matrix Matrix::operator*(const Matrix& other) const {
	if ((*mdata)[0].size() != other.mdata->size()) {
		//error
	}

	Matrix temp;
	float sum;

	for (int i = 0; i < mdata->size(); ++i) {
		for (int j = 0; j < other.mdata->at(0).size(); ++j) {
			sum = 0;
			for (int k = 0; k < other.mdata->size(); ++k) {
				sum += (*mdata)[i][k] * other.mdata->at(k)[j];
			}
			temp.mdata->at(i)[j] = sum;
		}
	}

	return temp;
}

Matrix& Matrix::operator*=(const Matrix& other) {
	if ((*mdata)[0].size() != other.mdata->size()) {
		//error
	}

	float sum;

	for (int i = 0; i < mdata->size(); ++i) {
		for (int j = 0; j < other.mdata->at(0).size(); ++j) {
			sum = 0;
			for (int k = 0; k < other.mdata->size(); ++k) {
				sum += (*mdata)[i][k] * other.mdata->at(k)[j];
			}
			(*mdata)[i][j] = sum;
		}
	}

	return *this;
}

//	Returns a pair of ints in the form rows, columns
std::pair<int, int> Matrix::Dimensions() const{
	// return std::pair<int, int>(mdata->size(), (*mdata)[0].size());	// Only use if not storing dimensions
	return *mdimensions;
}

//	Returns a true if the Matrix is square and false if not
bool Matrix::isSquare() {
	if (mdata->size() != mdata->at(0).size()) {
		return false;
	}

	return true;
}

Matrix& Matrix::transpose() {
	if (!isSquare()) {
		// Error
	}

	for (int i = 0; i < mdata->size(); ++i) {
		for (int j = i + 1; j < mdata->size(); ++j) {
			std::swap(mdata->at(i)[j], mdata->at(j)[i]);
		}
	}

	return *this;
}

Matrix innerProduct(Matrix& u, Matrix& v) {
	if (u.mdata->size() != v.mdata->size()) {
		//error
	}

	Matrix temp;
	float sum;

	for (int i = 0; i < u.mdata->at(0).size(); ++i) {
		for (int j = 0; j < v.mdata->at(0).size(); ++j) {
			sum = 0;
			for (int k = 0; k < v.mdata->size(); ++k) {
				sum += u.mdata->at(k)[i] * v.mdata->at(k)[j];
			}
			temp.mdata->at(i)[j] = sum;
		}
	}

	return temp;
}

Matrix externalProduct(Matrix& u, Matrix& v) {
	if (u.mdata->at(0).size() != v.mdata->at(0).size()) {
		//error
	}

	Matrix temp;
	float sum;

	for (int i = 0; i < u.mdata->size(); ++i) {
		for (int j = 0; j < v.mdata->size(); ++j) {
			sum = 0;
			for (int k = 0; k < v.mdata->at(0).size(); ++k) {
				sum += u.mdata->at(i)[k] * v.mdata->at(j)[k];
			}
			temp.mdata->at(i)[j] = sum;
		}
	}

	return temp;
}