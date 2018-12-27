#pragma once
#include "stdafx.h"
class Layer {
public:
	std::string f;
	arma::mat weights;
	Layer() {}
	virtual arma::mat activate(arma::mat& input) { arma::mat _; return _; }
	virtual arma::mat train(arma::mat& error, arma::mat output1, arma::mat output2) { arma::mat _; return _; }
	virtual arma::mat train_h(arma::mat& delta_n, arma::mat output1, arma::mat output2) { arma::mat _; return _; }
};

class Perceptron :public Layer {
public:
	Perceptron(int rows, int cols, std::string function){
		weights = arma::randu<arma::mat>(rows, cols);
		f = function;
	}
	arma::mat activate(arma::mat& input) {
		return input * weights;
	}
	arma::mat train(arma::mat& error, arma::mat output1, arma::mat output2) {
		output2.for_each(Functor(f, true));
		arma::mat delta = error % output2;
		arma::mat error2 = delta * weights.t();
		weights += output1.t() * delta;
		return error2;
	}
};