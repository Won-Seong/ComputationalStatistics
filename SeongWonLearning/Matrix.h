#pragma once
#include <iostream>
#include <vector>

using Vector = std::vector<double>;

class Matrix : public std::exception {
protected:
	using Space = std::vector< Vector >;//It can be thought as an empty matrix.
public://Basic matrix ops
	Matrix operator-(const Matrix&) const;//return A - B
	Matrix operator+(const Matrix&) const;//return A + B
	Matrix operator*(const Matrix&) const;//return AB(Matrix mul)
	Vector operator*(const Vector&) const;//return A * x
	Matrix operator^(const unsigned int&) const;//return A^k
	void operator+=(const Matrix&);//A = A + B
	void operator-=(const Matrix&);//A = A - B
	void operator*=(const Matrix&);//A = AB 
	void operator^=(const unsigned int&);//A = A^k
	Matrix Power(const unsigned int&) const;//return A^k
	Matrix Transpose() const;//return A'
	Matrix Inverse() const;
public://Matrix manipulation
	void Clear() { n_ = size_t(), m_ = size_t(); matrix_.clear(); };//Clear this matrix
	bool IsEmpty() const { return matrix_.empty(); }//If this's empty, return true
	void set_size(const size_t& n, const size_t& m);
	void StdInsert();
	size_t get_n() const;
	size_t get_m() const;
	Space get_matrix() const;
	Vector& operator[](const size_t& i) { return matrix_[i]; }
	Vector operator[](const size_t& i) const { return matrix_[i]; }
	void PrintMatrix() const;//Print the matrix 
	bool IsSquare() const { return n_ == m_; }
	bool IsOrthogonal() const;
	unsigned int Rank() const;
	bool IsColEqualRank() const;
	bool IsInvertible() const;
public://Constructor and Destructor
	Matrix() : n_(size_t()), m_(size_t()) {}
	Matrix(const size_t& n, const size_t& m) :n_(n), m_(m) {
		matrix_.resize(m);
		for (auto& itr : matrix_) itr.resize(n);
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
protected:
	void SetIdentity();//If the matrix is square, set it to identity.
protected:
	size_t n_, m_;//The matrix have n rows and m columns.
	Space matrix_;
public:
	friend std::ostream& operator<<(std::ostream&, const Matrix&);
};

class OrthogonalMatrix : public Matrix {
public://Const and Dest
	OrthogonalMatrix() : Matrix() {}
	OrthogonalMatrix(const size_t& n, const size_t& m) : Matrix(n, m) {};
	OrthogonalMatrix(const OrthogonalMatrix& matrix) : Matrix(matrix) {}
	OrthogonalMatrix(const Matrix& matrix) {
		if (matrix.IsOrthogonal()) *this = matrix;
		else throw std::invalid_argument("It's not orthogonal!");
	}
	OrthogonalMatrix(OrthogonalMatrix&& matrix) noexcept : Matrix(std::move(matrix)) {}
	OrthogonalMatrix& operator=(const OrthogonalMatrix& matrix) {
		n_ = matrix.n_;
		m_ = matrix.m_;
		matrix_ = matrix.matrix_;
		return *this;
	}
	OrthogonalMatrix& operator=(OrthogonalMatrix&& matrix) noexcept {
		n_ = matrix.n_;
		m_ = matrix.m_;
		matrix_ = std::move(matrix.matrix_);
		matrix.n_ = size_t();
		matrix.m_ = size_t();
		matrix.matrix_.clear();
		return *this;
	}
public:
	Matrix Inverse() const;
};

class Decomposition : public std::exception {
public:

public://Const and Dest
	Decomposition(const Matrix& matrix) : n_(matrix.get_n()), m_(matrix.get_m()) {}
protected:
	size_t n_;
	size_t m_;
};

class QR : public Decomposition {
public://Const and Dest
	QR(const Matrix& matrix) : Decomposition(matrix) {
		q_.set_size(n_, m_);
		r_.set_size(m_, m_);
		q_ = std::move(GramSchmidt(matrix));
	}
	QR(Matrix&& matrix) : Decomposition(matrix) {
		q_.set_size(n_, m_);
		r_.set_size(m_, m_);
		q_ = std::move(GramSchmidt(matrix));
		matrix.Clear();
	}
	~QR() { q_.Clear(); r_.Clear(); }
public:
	Vector Solve(const Vector&) const;//Solve a linear problem
public://Manipulate
	void PrintQR() const;
private:
	OrthogonalMatrix GramSchmidt(const Matrix& matrix);
	OrthogonalMatrix GramSchmidt(Matrix&& matrix);
private:
	OrthogonalMatrix q_;
	Matrix r_;
};

class LU : public Decomposition {
public://Const and Dest
	LU(const Matrix& matrix) : Decomposition(matrix) {
		if (n_ >= m_)
			l_.set_size(n_, m_), u_.set_size(m_, m_), l_ = matrix;
		else
			l_.set_size(n_, n_), u_.set_size(n_, m_), u_ = matrix;
		LU_Decomposition();
	}
	LU(Matrix&& matrix) : Decomposition(matrix) {
		if (n_ > m_)
			l_.set_size(n_, m_), u_.set_size(m_, m_), l_ = std::move(matrix);
		else
			l_.set_size(n_, n_), u_.set_size(n_, m_), u_ = std::move(matrix);
		LU_Decomposition();
		matrix.Clear();
	}
	~LU() { l_.Clear(); u_.Clear(); }
public://Manipulate
	double Determinant() const;
	void PrintLU() const;
private:
	void LU_Decomposition();
private:
	Matrix l_;
	Matrix u_;
};

LU LU_Decomp(const Matrix&);
Vector operator+(const Vector&, const Vector&);
Vector operator-(const Vector&, const Vector&);
double Dot(const Vector&, const Vector&);
bool IsOrthogonal(const Vector&, const Vector&);
double L2Norm(const Vector&);
double L1Norm(const Vector&);
std::ostream& operator<<(std::ostream&, const Vector&);
std::ostream& operator<<(std::ostream&, const Matrix&);
std::istream& operator>>(std::istream&, Vector&);