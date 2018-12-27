#pragma once
#include "stdafx.h"
class Percs {
public:
	std::vector<Layer*> Layers;
	Percs(int n_layers, std::vector<int> sizes) {
		Layers = std::vector<Layer*>(sizes.size()/2);
		for (int i = 0; i < sizes.size()/2; i++) {
			Layers[i] = new Perceptron(sizes[2 * i], sizes[2 * i + 1], "Sigm");
		}
	}
	void train(int ages, int error_step, double speed, arma::mat& input, arma::mat& etalon) {
		for (int i = 0; i < ages; i++) {
			std::vector<arma::mat> outputs(Layers.size()+1);
			outputs[0] = input;
			for (int j = 1; j < outputs.size(); j++) {
				outputs[j] = Layers[j-1]->activate(outputs[j - 1]);
			}
			arma::mat error = etalon - outputs[outputs.size() - 1];
			if (i%error_step ==0)
				std::cout << abs(mean(error)) <<std::endl;
			for (int j = Layers.size() - 1; j > -1; j--) {
				error = Layers[j]->train(error, outputs[j], outputs[j+1], speed);
			}
		}
	}
	void solve(arma::mat& input) {
		std::vector<arma::mat> outputs(Layers.size());
		outputs[0] = Layers[0]->activate(input);
		for (int j = 1; j < outputs.size(); j++) {
			outputs[j] = Layers[j]->activate(outputs[j - 1]);
		}
		std::cout << outputs[outputs.size() - 1];
	}
};