// NuralWeb.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
using namespace std;
using namespace arma;

//Функтор логистической функции


int main()
{
	Functor* f = new Sigm(true);
	Functor* f2 = new ReLu(true);
	mat A(3, 3), B(2,2);
	A.fill(5);
	B.fill(2);
	cout << f;
	system("pause");
	return 0;
}

