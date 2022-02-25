#include "Matrix.h"
#include "GradientDescent.h"

int main() {
	size_t n, m;
	std::cin >> n >> m;
	Matrix A(n, m);
	A.StdInsert();

	LU lu(A);
	lu.PrintLU();

	try
	{
		QR qr(A);
		qr.PrintQR();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	
	
}