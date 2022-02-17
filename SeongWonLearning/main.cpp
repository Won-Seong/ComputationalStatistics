#include "Matrix.h"

int main() {
	size_t n, m;
	std::cin >> n >> m;
	Matrix A(n, m);
	double temp;
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++) {
			std::cin >> temp;
			A[i][j] = temp;
		}
	}
	
	A.PrintMatrix();
	LU lu{ std::move(A) };
	lu.PrintLU();
}