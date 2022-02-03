#pragma once
#include <iostream>
#include <vector>

class Matrix : public std::exception {


public://Constructor and Destructor
	Matrix() : n_(double()), m_(double()) {}
	Matrix(const size_t& n, const size_t& m) :n_(n), m_(m) {
		matrix_.resize(n);
		for (auto& itr : matrix_) itr.resize(m);
	}
	Matrix(const Matrix& matrix) :n_(matrix.n_), m_(matrix.m_), matrix_(matrix.matrix_) {}
	Matrix(Matrix&& matrix) noexcept : n_(std::move(matrix.n_)), m_(std::move(matrix.m_)) {
		matrix_ = std::move(matrix.matrix_);
		matrix.n_ = double();
		matrix.m_ = double();
		matrix.matrix_.clear();
	}
	Matrix& operator=(const Matrix& matrix) {
		n_ = matrix.n_;
		m_ = matrix.m_;
		matrix_ = matrix.matrix_;
	}
	
private:
	size_t n_, m_;//The matrix have n rows and m columns.
	std::vector< std::vector<double> > matrix_;
};