#pragma once
#include "stdafx.h"

class Functor {
public:
	bool deriv;
	std::string function;
	Functor() {}
	Functor(std::string function, bool deriv): function(function), deriv(deriv) {}
	void operator() (double &x) {
		if (function == "Sigm") {
			if (deriv) {
				x = (1 / (1 + exp(-x))) * (1 - (1 / (1 + exp(-x))));
			}
			else {
				x = (1 / (1 + exp(-x)));
			}
		}
		if (function == "ReLu") {
			if (deriv) {
				x = (rand() % 400 + 100) / 1000;
			}
			else {
				x = fmax(x, 0);
			}
		}
	}
};