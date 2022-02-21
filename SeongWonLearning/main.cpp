#include "Matrix.h"
#include "GradientDescent.h"

int main() {
	size_t n, m;
	std::cin >> n >> m;
	Matrix A(n, m);
	Vector B(n);

	A.StdInsert();
	for (auto& itr : B)
		std::cin >> itr;
	LinearGradientDescent grad(A, B);

	A.PrintMatrix();
	for (auto& itr : B)
		std::cout << itr << ' ';
	std::cout << std::endl;

	try
	{
		grad.FindWeight(30, 0.01);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}