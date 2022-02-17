#pragma once
#include <iostream>
#include <vector>


class Matrix : public std::exception {
	using Vector = std::vector<double>;
	using Space = std::vector< Vector >;
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
	void Clear() { n_ = size_t(), m_ = size_t(); matrix_.clear(); };
	bool IsEmpty() const { return matrix_.empty(); }
	void set_size(const size_t& n, const size_t& m);
	size_t get_n() const;
	size_t get_m() const;
	Space get_matrix() const;
	Vector& operator[](const size_t& i) { return matrix_[i]; }
public://Input and Output
	void PrintMatrix() const;//Print the matrix 
public://Constructor and Destructor
	Matrix() : n_(size_t()), m_(size_t()) {}
	Matrix(const size_t& n, const size_t& m) :n_(n), m_(m) {
		matrix_.resize(n);
		for (auto& itr : matrix_) itr.resize(m);
	}
	Matrix(const Matrix& matrix) :n_(matrix.n_), m_(matrix.m_), matrix_(matrix.matrix_) {}
	Matrix(Matrix&& matrix) noexcept : n_(std::move(matrix.n_)), m_(std::move(matrix.m_)) {
		matrix_ = std::move(matrix.matrix_);
		matrix.n_ = size_t();
		matrix.m_ = size_t();
		matrix.matrix_.clear();
	}
	Matrix& operator=(const Matrix& matrix) {
		n_ = matrix.n_;
		m_ = matrix.m_;
		matrix_ = matrix.matrix_;
		return *this;
	}
	Matrix& operator=(Matrix&& matrix) noexcept {
		n_ = matrix.n_;
		m_ = matrix.m_;
		matrix_ = std::move(matrix.matrix_);
		matrix.n_ = size_t();
		matrix.m_ = size_t();
		matrix.matrix_.clear();
		return *this;
	}
private:
	size_t n_, m_;//The matrix have n rows and m columns.
	Space matrix_;
};

class OrthogonalMatrix : public Matrix {
public:
	Matrix Inverse() const { return Transpose(); }
};

class Decomposition : public std::exception {
public:

public://Const and Dest
	Decomposition() {}
};

class QR : public Decomposition {
public:

private:
	Matrix q_;
	Matrix r_;
};

class LU : public Decomposition {
public:
	LU(const Matrix& matrix) : n_(matrix.get_n()), m_(matrix.get_m()) {
		if (n_ > m_) 
			l_.set_size(n_, m_), u_.set_size(m_, m_), l_ = matrix;
		else 
			l_.set_size(n_, n_), u_.set_size(n_, m_), u_ = matrix;
		Decomposition();
	}
	LU(Matrix&& matrix) : n_(matrix.get_n()), m_(matrix.get_m()) {
		if (n_ > m_)
			l_.set_size(n_, m_), u_.set_size(m_, m_), l_ = std::move(matrix);
		else
			l_.set_size(n_, n_), u_.set_size(n_, m_), u_ = std::move(matrix);
		Decomposition();
		matrix.Clear();
	}
	~LU() { l_.Clear(); u_.Clear(); }
public:
	void Decomposition();
	void PrintLU() const;
private:
	size_t n_;
	size_t m_;
	Matrix l_;
	Matrix u_;
};

LU LU_Decomp(const Matrix&);
