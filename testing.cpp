#include "Square_Matrix.h"

template <typename T>
Square_Matrix<Fraction> cerinta(const Square_Matrix<T>& A, const int& n)
{

	Square_Matrix<Fraction> X = (A.transpose()).inverse();
	Square_Matrix<Fraction> S(A.order());
	S = S.zeroMatrix();
	
	for (int i = 1; i <= n; i++) {
		S += ( X * Fraction(i) ) ^ i;
	}

	return S;
}

int main()
{
	std::ifstream in("read.txt");

	int order;
	in >> order;

	Square_Matrix<int> A(order);
	in >> A;

	int n;
	std::cin >> n;

	//std::cout << cerinta<int>(A, n);
	std::cout << A.inverse();
	std::cin.get();
}