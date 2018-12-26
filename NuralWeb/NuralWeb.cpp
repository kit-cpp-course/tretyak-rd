// NuralWeb.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
using namespace std;
using namespace arma;

//Функтор логистической функции
class Sigm
{
private:
	bool deriv;
public:
	Sigm(bool deriv) : deriv(deriv) {}
	void operator() (double &x)
	{
		if (deriv) {
			x = (1 / (1 + exp(-x))) * (1 - (1 / (1 + exp(-x))));
		}
		else {
			x = (1 / (1 + exp(-x)));
		}
	}
};

int main()
{
	double speed = 1;
	mat X("0.0 0.0 1.0; 0.0 1.0 1.0; 1.0 0.0 1.0; 1.0 1.0 1.0");
	mat Y("0.0; 1.0; 1.0; 0.0");
	mat syn0 = randn<mat>(3, 4);
	mat syn1 = randn<mat>(4, 1);
	for (int i = 0; i < 60000; i++) {
		mat l0 = X;
		mat l1 = l0 * syn0;
		l1.for_each(Sigm(false));
		mat l2 = l1 * syn1;
		l2.for_each(Sigm(false));

		mat l2_error = Y - l2;
		if (i % 10000 == 0) {
			cout << "Error: " << mean(abs(l2_error));
		}
		mat l2_d = l2;
		l2_d.for_each(Sigm(true));
		mat l2_delta = l2_error % l2_d;
		mat l1_error = l2_delta * syn1.t();
		mat l1_d = l1;
		l1_d.for_each(Sigm(true));
		mat l1_delta = l1_error % l1_d;
		syn1 += speed * l1.t() * l2_delta;
		syn0 += speed * l0.t() * l1_delta;
		if (i == 59999)
			cout << l2;
	}
	system("pause");
	return 0;
}

