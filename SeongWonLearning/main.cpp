#include "Matrix.h"
#include "GradientDescent.h"

 int main() {
	size_t n, m;
	std::cin >> n >> m;
	Matrix A(n, m);
	Matrix B(n, m);
	A.StdInsert();
	std::cout << A.RowEchelonForm();
	std::cout << A.Rank();
}