#include "Matrix.h"
#include "GradientDescent.h"

int main() {
	size_t n, m;
	std::cin >> n >> m;
	Matrix A(n, m);
	A.StdInsert();
	A.PrintMatrix();
	A.Transpose().PrintMatrix();

	LU lu(A);
	lu.PrintLU();

	QR qr(A);
	qr.PrintQR();
}