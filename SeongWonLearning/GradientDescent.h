#pragma once
#include "Matrix.h"

class GradientDescent : public std::exception {
public :
	Vector FindWeight(const size_t& count, const double& eta) const;
public:
	GradientDescent(const Matrix& x, const Vector& y) : x_(x), y_(y), 
		n_(x.get_n()), m_(x.get_m()) {
	}
protected:
	virtual Vector Function(const Vector&) const = 0;
	virtual Vector D_Function(const Vector&) const = 0;
protected:
	size_t n_, m_;
	Matrix x_;
	Vector y_;
};

class LinearGradientDescent : public GradientDescent {
public:
	virtual Vector Function(const Vector&) const;
	virtual Vector D_Function(const Vector&) const;
public:
	LinearGradientDescent(const Matrix& x, const Vector& y) : GradientDescent(x, y) {}
private:
	
};