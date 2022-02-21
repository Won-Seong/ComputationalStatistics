#include "GradientDescent.h"

Vector LinearGradientDescent::Function(const Vector& w) const
{
	Vector temp;
	temp.resize(m_);
	for (size_t i = 0; i < n_; i++)
		for (size_t j = 0; j < m_; j++) 
			temp[j] += std::pow(w[j] * x_[i][j] - y_[i], 2);
	return temp;
}

Vector LinearGradientDescent::D_Function(const Vector& w) const
{
	Vector temp;
	temp.resize(m_);
	for (size_t i = 0; i < n_; i++) 
		for (size_t j = 0; j < m_; j++) 
			temp[j] += (w[j] * x_[i][j] - y_[i]) * 2 * x_[i][j];
	return temp;
}

Vector GradientDescent::FindWeight(const size_t& count, const double& eta) const
{
	Vector temp;
	Vector temp_two;
	Vector weights_;
	weights_.resize(m_);
	for (size_t i = 0; i < count; i++)
	{
		temp = Function(weights_);
		temp_two = D_Function(weights_);
		for (size_t j = 0; j < m_; j++)
			weights_[j] -= eta * temp_two[j];
		for (const auto& itr : weights_)
			std::cout << itr << ' ';
		std::cout << std::endl;
	}
	return weights_;
}
