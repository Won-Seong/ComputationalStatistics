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
	for (size_t i = 0; i < n_; i++) {
		for (size_t j = 0; j < B.m_; j++) {
			temp_number = 0;
			for (size_t k = 0; k < m_; k++) temp_number += matrix_[k][i] * B.matrix_[j][k];
			temp_matrix.matrix_[j][i] = temp_number;
		}
	}
	return temp_matrix;
}

Vector Matrix::operator*(const Vector& x) const
{
	if (m_ != x.size()) throw std::invalid_argument("Size error!");
	Vector temp_vector(n_, 0);
	for (size_t i = 0; i < n_; i++)
		for (size_t j = 0; j < m_; j++)
			temp_vector[i] += matrix_[j][i] * x[j];
	return temp_vector;
}

Matrix Matrix::operator^(const unsigned int& k) const
{
	if (!IsSquare()) throw std::logic_error("This matrix is not square!");
	Matrix temp_matrix{ *this };
	for (unsigned int i = 1; i < k; i++)
		temp_matrix *= *this;
	return temp_matrix;
}

Matrix Matrix::Power(const unsigned int& k) const
{
	return operator^(k);
}

Matrix Matrix::Transpose() const
{
	Matrix temp_matrix(m_, n_);
	for (size_t i = 0; i < n_; i++)
		for (size_t j = 0; j < m_; j++)
			temp_matrix[i][j] = matrix_[j][i];
	return temp_matrix;
}

//Matrix Matrix::Inverse() const
//{
//	if (!IsSquare()) throw std::logic_error("It's not square!");
//	Matrix inverse_(get_n(), get_m());
//	inverse_.SetIdentity();
//	for (size_t i = 0; i < n_; i++)
//	{
//		
//	}
//}

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
	*this = std::move(operator*(B));
}

void Matrix::operator^=(const unsigned int& k)
{
	*this = std::move(operator^(k));
}

void Matrix::set_size(const size_t& n, const size_t& m)
{
	if (!matrix_.empty()) std::cout << "Matrix is not empty!" << std::endl;
	else {
		n_ = n, m_ = m;
		matrix_.resize(m_);
		for (auto& itr : matrix_) itr.resize(n_, double());
	}
}

void Matrix::StdInsert()
{
	for (size_t i = 0; i < n_; i++)
		for (size_t j = 0; j < m_; j++) 
			std::cin >> matrix_[j][i];
}

void Matrix::SetIdentity()
{
	if (!IsSquare()) throw std::logic_error("It's not square!");
	for (size_t i = 0; i < n_; i++)
		for (size_t j = 0; j < n_; j++)
			if (i == j) matrix_[i][j] = 1; 
			else matrix_[i][j] = 0;
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
		for (size_t i = 0; i < n_; i++)
		{
			for (size_t j = 0; j < m_; j++)
				std::cout << matrix_[j][i] << ' ';
			std::cout << '\n';
		}
		std::cout << std::endl;
	}
}

bool Matrix::IsOrthogonal() const
{
	for (size_t i = 0; i < m_; i++)
		for (size_t j = i + 1; j < m_; j++)
			if (Dot(matrix_[i], matrix_[j]) != 0) return false;
	return true;
}

unsigned int Matrix::Rank() const
{
	unsigned int rank{ 0 };
	bool flag{ false };
	Matrix temp_matrix{ *this };
	for (size_t i = 0; i < m_; i++){
		flag = false;
		for (const auto& itr : temp_matrix[i]){
			if (itr != 0) flag = true;
		}
		
		if (!flag) break;
		else rank++;

		for (size_t j = i + 1; j < m_; j++){
			double temp{temp_matrix[j][i]};
			for (size_t k = 0; k < n_; k++)
				temp_matrix[j][k] -= temp;
		}
	}
	return rank;
}

bool Matrix::IsColEqualRank() const
{
	return m_ == Rank();
}

bool Matrix::IsInvertible() const
{
	return IsSquare() && IsColEqualRank();
}

void LU::LU_Decomposition()
{
	if (n_ < m_) {

		for (size_t i = 0; i < n_; i++){
			l_[i][i] = u_[i][i];
			for (size_t k = i + 1; k < n_; k++)
				l_[i][k] = u_[i][k] , u_[k][i] /= u_[i][i];
			l_[i][i] = 1;

			for (size_t j = i + 1; j < n_; j++) {
				double temp{ u_[i][j] };
				for (size_t k = i; k < m_; k++)
					u_[k][j] -= u_[k][i] * temp;

			}

		}

	}
	else if(n_ >= m_) {
		for (size_t i = 0; i < m_; i++) {
			u_[i][i] = l_[i][i];
			for (size_t k = i + 1; k < m_; k++)
				u_[k][i] = l_[k][i];
			for (size_t k = i + 1; k < n_; k++)
				l_[i][k] /= l_[i][i];
			l_[i][i] = 1;
			for (size_t j = i + 1; j < m_; j++) {
				double temp{ l_[j][i] };
				for (size_t k = i; k < n_; k++)
					l_[j][k] -= l_[i][k] * temp;

			}
		}
	}
}

double LU::Determinant() const
{
	if (n_ != m_) throw std::logic_error("It's not square!");
	double det_l{ 1 };
	double det_u{ 1 };
	for (size_t i = 0; i < n_; i++) det_l *= l_[i][i], det_u *= u_[i][i];
	return det_l * det_u;
}

void LU::PrintLU() const
{
	std::cout << "L" << '\n';
	l_.PrintMatrix();
	std::cout << "U" << '\n';
	u_.PrintMatrix();
	std::cout << "LU" << '\n';
	l_.operator*(u_).PrintMatrix();
}

LU LU_Decomp(const Matrix& matrix)
{
	LU lu(matrix);
	return std::move(lu);
}

Vector operator+(const Vector& x, const Vector& y)
{
	if (x.size() != y.size()) throw std::invalid_argument("Different size!");
	Vector temp{ x };
	for (size_t i = 0; i < x.size(); i++)
		temp[i] += y[i];
	return std::move(temp);
}

Vector operator-(const Vector& x, const Vector& y)
{
	if (x.size() != y.size()) throw std::invalid_argument("Different size!");
	Vector temp{ x };
	for (size_t i = 0; i < x.size(); i++)
		temp[i] += y[i];
	return std::move(temp);
}

double Dot(const Vector& x, const Vector& y)
{
	if (x.size() != y.size()) throw std::invalid_argument("Different size!");
	double temp{ 0 };
	for (size_t i = 0; i < x.size(); i++)
		temp += x[i] * y[i];
	return temp;
}

bool IsOrthogonal(const Vector& x, const Vector& y)
{
	return Dot(x, y) == 0;
}

double L2Norm(const Vector& x)
{
	return std::sqrt(Dot(x , x));
}

double L1Norm(const Vector& x)
{
	double temp{ 0 };
	for (const auto& itr : x) temp += std::abs(itr);
	return temp;
}

std::ostream& operator<<(std::ostream& os, const Vector& x)
{
	for (const auto& itr : x)
		os << itr << ' ';
	return os;
}

std::istream& operator>>(std::istream& is, Vector& x)
{
	for (auto& itr : x)
		is >> itr;
	return is;
}

Matrix OrthogonalMatrix::Inverse() const
{
	if (!IsSquare()) throw std::logic_error("It's not square!");
	return Transpose();
}

Vector QR::Solve(const Vector& b) const
{
	if (b.size() != n_) throw std::invalid_argument("Different size!");
	//Rx = Q^Tb
	Vector x(m_, 0);
	Vector q_tb{ q_.Transpose() * b };

	if (n_ >= m_) {
		for (size_t i = m_ - 1; i > 0; i--) {
			double temp{ q_tb[i] };
			//Solve the equation
			for (size_t j = i + 1; j > i && j < m_; j--)
				temp -= r_[j][i] * x[j];
			x[i] = temp / r_[i][i];
		}
		double temp{ q_tb[0] };
		for (size_t j = m_ - 1; j > 0; j--)
			temp -= r_[j][0] * x[j];
		x[0] = temp / r_[0][0];
	}
	else {
		throw std::logic_error("There are infinite solutions!");
	}
	return x;
}

void QR::PrintQR() const
{
	std::cout << "Q" << '\n';
	q_.PrintMatrix();
	std::cout << "R" << '\n';
	r_.PrintMatrix();
	std::cout << "QR" << '\n';
	q_.operator*(r_).PrintMatrix();
}


OrthogonalMatrix QR::GramSchmidt(const Matrix& matrix)
{
	if (matrix.IsColEqualRank()) throw std::invalid_argument("All column ain't independent!");
	if (n_ >= m_) {
		OrthogonalMatrix temp_q(matrix.get_n(), matrix.get_m());
		for (size_t i = 0; i < temp_q.get_n(); i++)
			for (size_t j = 0; j < temp_q.get_m(); j++)
				temp_q[j][i] = matrix[j][i];
		Matrix table(m_, m_);
		for (size_t i = 0; i < m_; i++) {
			//Orthogonalize
			for (size_t j = 0; j < i; j++) {
				for (size_t k = 0; k < n_; k++)
					temp_q[i][k] -= temp_q[j][k] * table[j][i];
			}
			//Normalize(q_k = A_k / ||A_k||)
			double norm{ L2Norm(temp_q[i]) };
			for (auto& itr : temp_q[i]) itr /= norm;
			for (size_t j = i + 1; j < m_; j++)
				table[i][j] = Dot(temp_q[i], temp_q[j]);//table[i][j] == q_i dot a_j
		}
		r_ = temp_q.Transpose() * matrix;//R = Q^{T}A
		return temp_q;
	}
	else {
		OrthogonalMatrix temp_q(matrix.get_n() , matrix.get_n() );
		for (size_t i = 0; i < temp_q.get_n(); i++)
			for (size_t j = 0; j < temp_q.get_n(); j++)
				temp_q[j][i] = matrix[j][i];
		Matrix table(n_, n_);
		for (size_t i = 0; i < n_; i++) {
			//Orthogonalize
			for (size_t j = 0; j < i; j++) {
				for (size_t k = 0; k < n_; k++)
					temp_q[i][k] -= temp_q[j][k] * table[j][i];
			}

			//Normalize(q_k = A_k / ||A_k||)
			double norm{ L2Norm(temp_q[i]) };
			for (auto& itr : temp_q[i]) itr /= norm;
			for (size_t j = i + 1; j < n_; j++)
				table[i][j] = Dot(temp_q[i], temp_q[j]);//table[i][j] == q_i dot a_j
		}
		r_ = temp_q.Transpose() * matrix;//R = Q^{T}A
		return temp_q;
	}
}

OrthogonalMatrix QR::GramSchmidt(Matrix&& matrix)
{
	if (matrix.IsColEqualRank()) throw std::invalid_argument("All column ain't independent!");
	if (n_ >= m_) {
		Matrix table(m_, m_);
		for (size_t i = 0; i < m_; i++) {
			//Orthogonalize
			for (size_t j = 0; j < i; j++) {
				for (size_t k = 0; k < n_; k++)
					matrix[i][k] -= matrix[j][k] * table[j][i];
			}
			//Normalize(q_k = A_k / ||A_k||)
			double norm{ L2Norm(matrix[i]) };
			for (auto& itr : matrix[i]) itr /= norm;
			for (size_t j = i + 1; j < m_; j++)
				table[i][j] = Dot(matrix[i], matrix[j]);//table[i][j] == q_i dot a_j
		}
		r_ = matrix.Transpose() * matrix;//R = Q^{T}A
		return matrix;
	}
	else {
		Matrix table(n_, n_);
		for (size_t i = 0; i < n_; i++) {
			//Orthogonalize
			for (size_t j = 0; j < i; j++) {
				for (size_t k = 0; k < n_; k++)
					matrix[i][k] -= matrix[j][k] * table[j][i];
			}

			//Normalize(q_k = A_k / ||A_k||)
			double norm{ L2Norm(matrix[i]) };
			for (auto& itr : matrix[i]) itr /= norm;
			for (size_t j = i + 1; j < n_; j++)
				table[i][j] = Dot(matrix[i], matrix[j]);//table[i][j] == q_i dot a_j
		}
		r_ = matrix.Transpose() * matrix;//R = Q^{T}A
		return matrix;
	}
}
