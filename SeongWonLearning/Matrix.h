#pragma once
#include <iostream>
#include <vector>

class Matrix : public std::exception {


private:
	size_t n_, m_;
	std::vector< std::vector<double> > matrix_;
};