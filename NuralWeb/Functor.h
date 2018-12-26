#pragma once
#include "stdafx.h"
class Function {
public:
	Functor* f;
	Function(std::string function) {
		if(function=="")
	}
};

class Functor {
public:
	bool deriv;
	virtual void operator() (double &x) {}
};

class Sigm:public Functor
{
public:
	Sigm(bool deriv){
		this->deriv = deriv;
	};
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

class ReLu :public Functor
{
public:
	ReLu(bool deriv) {
		this->deriv = deriv;
	};
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
