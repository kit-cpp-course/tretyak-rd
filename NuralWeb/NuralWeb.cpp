// NuralWeb.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
using namespace std;
using namespace arma;


int main()
{
	vector <int> sizes = { 3, 4, 4, 1 };
	Percs nw(2, sizes);
	mat x = "0 0 1; 0 1 1; 1 0 1; 1 1 1";
	mat y = "0; 1; 1; 0";
	nw.train(60000, 10000, 1, x, y);
	nw.solve(x);
	system("pause");
	return 0;
}

