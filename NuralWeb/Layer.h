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
		weights = 2 * arma::randu<arma::mat>(rows, cols) - 1;
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

class Convolutional{
public:
	std::string f;
	std::vector<arma::mat> kernels;
	std::vector<arma::mat> pooling_maps;
	Convolutional(int kernel_rows, int kernel_cols, int n_kernels, std::string function) {
		kernels = std::vector<arma::mat>(n_kernels);
		for (int i = 0; i < kernels.size(); i++)
			kernels[i] = 2 * arma::randu<arma::mat>(kernel_rows, kernel_cols) - 1;
		f = function;
	}
	arma::mat Pooling(arma::mat &A) {
		if ((int)sqrt(A.size()) % 2 != 0)
			A.resize((int)sqrt(A.size()) + 1, (int)sqrt(A.size()) + 1);
		arma::mat B(((int)sqrt(A.size()) + 1) / 2, ((int)sqrt(A.size()) + 1) / 2);
		arma::mat M((int)sqrt(A.size()), (int)sqrt(A.size()));
		M.fill(0);
		for (int i = 0; i < (int)sqrt(B.size()); i++) {
			for (int j = 0; j < (int)sqrt(B.size()); j++) {
				B.at(i, j) = A.submat(2 * i, 2 * j, 2 * i + 1, 2 * j + 1).max();
				M.submat(2 * i, 2 * j, 2 * i + 1, 2 * j + 1)[A.submat(2 * i, 2 * j, 2 * i + 1, 2 * j + 1).index_max()] = 1;
			}	
		}
		B.for_each(Functor("ReLu", false));
		A = B;
		return M;
	}
	std::vector<arma::mat> activate(std::vector<arma::mat> &input) {
		std::vector<arma::mat> maps;
		for (int i = 0; i < input.size(); i++)
			for (int j = 0; j < kernels.size(); j++) {
				arma::mat temp = conv2(input[i], kernels[j], "same");
				pooling_maps.push_back(Pooling(temp));
				maps.push_back(temp);
			}
		return maps;
	}
	std::vector<arma::mat> train(std::vector<arma::mat> delta, double speed) {
		std::vector<arma::mat> deltas;
		for (int k = 0; k < kernels.size(); k++) {

			arma::mat error = pooling_maps[k];
			for (int i = 0; i < (int)sqrt(delta[k].size()); i++) {
				delta[i].for_each(Functor(f, true));
				for (int j = 0; j < (int)sqrt(delta[k].size()); j++) {
					error.submat(2 * i, 2 * j, 2 * i + 1, 2 * j + 1) *= delta[k].at(i, j);
				}
			}
			arma::mat kernel_r((int)sqrt(kernels[k].size()), (int)sqrt(kernels[k].size()));
			for (int j = 0; j < kernel_r.size(); j++)
				kernel_r[j] = kernels[k][kernels[k].size() -1 - j];
			arma::mat delta_n = arma::conv2(error, kernel_r, "same");
			deltas.push_back(delta_n);
			kernels[k] += speed * arma::conv2(kernels[k], delta_n, "same");
		}
		return deltas;
	}
};