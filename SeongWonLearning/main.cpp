#include "Matrix.h"
#include "GradientDescent.h"

int main() {
	size_t n, m;
	std::cin >> n >> m;
	Matrix A(n, m);
	A.StdInsert();

	LU lu(A);
	lu.PrintLU();

	QR qr(A);
	qr.PrintQR();
	
}