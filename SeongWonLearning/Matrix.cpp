#include "Matrix.h"

Matrix Matrix::operator+(const Matrix& B) const
{
	if (B.n_ != n_ || B.m_ != m_) throw std::invalid_argument("Size error!");
	Matrix temp_matrix{ *this };
	for (size_t i = 0; i < n_; i++)
		for (size_t j = 0; j < m_; j++)
			temp_matrix.matrix_[i][j] += B.matrix_[i][j];
	return temp_matrix;
}

Matrix Matrix::operator-(const Matrix& B) const
{
	if (B.n_ != n_ || B.m_ != m_) throw std::invalid_argument("Size error!");
	Matrix temp_matrix{ *this };
	for (size_t i = 0; i < n_; i++)
		for (size_t j = 0; j < m_; j++)
			temp_matrix.matrix_[i][j] -= B.matrix_[i][j];
	return temp_matrix;
}

Matrix Matrix::operator*(const Matrix& B) const
{
	if (m_ != B.n_) throw std::invalid_argument("Size error!");
	Matrix temp_matrix(n_, B.m_);
	double temp_number{ double() };
	for (size_t i = 0; i < n_; i++){
		for (size_t j = 0; j < B.m_; j++) {
			temp_number = 0;
			for (size_t k = 0; k < m_; k++) temp_number += matrix_[i][k] * B.matrix_[k][j];
			temp_matrix.matrix_[i][j] = temp_number;
		}
	}
	return temp_matrix;
}

Matrix Matrix::operator^(const unsigned int& k) const
{
	if (n_ != m_) throw std::logic_error("This matrix is not square!");
	Matrix temp_matrix{ *this };
	for (unsigned int i = 0; i < k; i++)
		temp_matrix *= temp_matrix;
	return temp_matrix;
}

Matrix Matrix::Power(const unsigned int& k) const
{
	return operator^(k);
}

Matrix Matrix::Transpose() const
{
	Matrix temp_matrix(m_, n_);
	for (size_t i = 0; i < m_; i++)
		for (size_t j = 0; j < n_; j++)
			temp_matrix.matrix_[i][j] = matrix_[j][i];
	return temp_matrix;
}

Matrix Matrix::Inverse() const
{

}

void Matrix::operator+=(const Matrix& B)
{
	if (B.n_ != n_ || B.m_ != m_) throw std::invalid_argument("Size error!");
	for (size_t i = 0; i < n_; i++)
		for (size_t j = 0; j < m_; j++)
			matrix_[i][j] += B.matrix_[i][j];
}

void Matrix::operator-=(const Matrix& B)
{
	if (B.n_ != n_ || B.m_ != m_) throw std::invalid_argument("Size error!");
	for (size_t i = 0; i < n_; i++)
		for (size_t j = 0; j < m_; j++)
			matrix_[i][j] -= B.matrix_[i][j];
}

void Matrix::operator*=(const Matrix& B)
{
	*this = std::move( operator*(B) );
}

void Matrix::operator^=(const unsigned int& k)
{
	*this = std::move(operator^(k));
}

void Matrix::set_size(const size_t& n, const size_t& m) 
{
	if (!matrix_.empty()) std::cout << "Matrix is not empty!" << std::endl;
	else n_ = n, m_ = m;
}

size_t Matrix::get_n() const
{
	return n_;
}

size_t Matrix::get_m() const
{
	return m_;
}

Matrix::Space Matrix::get_matrix() const
{
	return matrix_;
}

void Matrix::PrintMatrix() const
{
	if (IsEmpty()) std::cout << "It's empty!" << std::endl;
	else {
		for (const auto& itr : matrix_) {
			for (const auto& itr_2 : itr)
				std::cout << itr_2 << ' ';
			std::cout << '\n';
		}
		std::cout << std::endl;
	}
}