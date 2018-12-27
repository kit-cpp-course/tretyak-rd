#pragma once
#include "stdafx.h"
class Layer {
public:
	std::string f;
	arma::mat weights;
	Layer() {}
	virtual arma::mat activate(arma::mat& input) { arma::mat _; return _; }
	virtual arma::mat train(arma::mat& error, arma::mat output1, arma::mat output2, double speed) { arma::mat _; return _; }
};

class Perceptron :public Layer {
public:
	Perceptron(int rows, int cols, std::string function){
		weights = arma::randu<arma::mat>(rows, cols);
		f = function;
	}
	arma::mat activate(arma::mat& input) {
		arma::mat Output = input * weights;
		Output.for_each(Functor(f, false));
		return Output;
	}
	arma::mat train(arma::mat& error, arma::mat output1, arma::mat output2, double speed) {
		output2.for_each(Functor(f, true));
		arma::mat delta = error % output2;
		arma::mat error2 = delta * weights.t();
		weights += speed * output1.t() * delta;
		return error2;
	}
};