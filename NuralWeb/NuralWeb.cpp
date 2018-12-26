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

class ReLu
{
private:
	bool deriv;
public:
	ReLu(bool deriv) : deriv(deriv) {}
	void operator() (double &x)
	{
		if (deriv) {
			x = (rand() % 400 + 100) / 100;
		}
		else {
			x = fmax(x, 0);
		}
	}
};

class Conv {
public:
	mat core;

	Conv() {}

	Conv(int size) {
		core = randn<mat>(size, size);
	}

	mat active(mat map) {
		mat R = conv2(map, core, "same");
		R.for_each(ReLu(false));
		return R;
	}
};

int main()
{
	MNISTreader Data("train-images.idx3-ubyte", "train-labels.idx1-ubyte", 60000);
	cout << Data.Labels[0] << endl;
	system("pause");
	return 0;
}

