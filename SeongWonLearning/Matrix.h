#pragma once
#include <iostream>
#include <vector>

class Matrix : public std::exception {
	using Space = std::vector< std::vector<double> >;
public://Basic matrix ops
	Matrix operator+(const Matrix&) const;//A + B
	Matrix operator-(const Matrix&) const;//A - B
	Matrix operator*(const Matrix&) const;//A * B(Matrix mul)
	Matrix operator^(const unsigned int&) const;//A^k
	void operator+=(const Matrix&);
	void operator-=(const Matrix&);
	void operator*=(const Matrix&);
	void operator^=(const unsigned int&);
	Matrix Power(const unsigned int&) const;//A^k
	Matrix Transpose() const;
	Matrix Inverse() const;
public://Manipulate
	void Clear() { n_ = double(), m_ = double(); matrix_.clear(); };
	bool IsEmpty() const { return matrix_.empty(); }
	void set_size(const size_t& n, const size_t& m) ;
	size_t get_n() const;
	size_t get_m() const;
	Space get_matrix() const;
public://Input and Output
	void PrintMatrix() const;//Print the matrix 
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
	Matrix& operator=(Matrix&& matrix) noexcept {
		n_ = matrix.n_;
		m_ = matrix.m_;
		matrix_ = std::move(matrix.matrix_);
		matrix.n_ = double();
		matrix.m_ = double();
		matrix.matrix_.clear();
	}
private://Internal utility function
	void QR_Decomposition();
private:
	size_t n_, m_;//The matrix have n rows and m columns.
	Space matrix_;
};

class OrthogonalMatrix : public Matrix {
public:
	Matrix Inverse() const { return Transpose(); }
};