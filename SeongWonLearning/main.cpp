#include "Matrix.h"
#include "GradientDescent.h"

int main() {
	size_t n, m;
	std::cin >> n >> m;
	Matrix A(n, m);
	Matrix B(n, m);
	A.StdInsert();
	B.StdInsert();
	
	std::cout << A + B << std::endl;
	std::cout << A - B << std::endl;
	std::cout << A * B << std::endl;
	std::cout << A.Power(3) << std::endl;
	
}