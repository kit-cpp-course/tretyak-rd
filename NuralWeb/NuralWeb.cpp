// NuralWeb.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
using namespace std;
using namespace arma;

int main()
{
	mat A(3, 3);
	A.fill(3.3);
	cout << A;
	system("pause");
    return 0;
}

