// NuralWeb.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
using namespace std;
using namespace arma;

//Функтор логистической функции


int main()
{
	mat A(3, 3), B(2,2);
	A.fill(5);
	B.fill(2);
	A.for_each(Function("Sigm", true));
	B.for_each(Function("Sigm", false));
	cout << A << endl << B;
	system("pause");
	return 0;
}

