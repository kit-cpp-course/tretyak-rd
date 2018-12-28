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
				std::cout << mean(abs(mean(error, 1))) <<std::endl;
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
	void save(std::string path) {
		for (int i = 0; i < Layers.size(); i++) {
			std::stringstream ss;
			ss << path << "\Layer" << i;
			Layers[i]->weights.save(ss.str());
		}
	}
	void load(std::string path) {
		for (int i = 0; i < Layers.size(); i++) {
			std::stringstream ss;
			ss << path << "\Layer" << i;
			Layers[i]->weights.load(ss.str());
		}
	}
};

class Conv {
public:
	std::vector<Convolutional*> Convolutionals;
	std::vector<Layer*> Layers;
	Conv(int n_layers, std::vector<int> kernels_sizes) {
		int size = 1;
		for (int i = 0; i < kernels_sizes.size(); i++)
			size *= kernels_sizes[i];

		Layers = std::vector<Layer*>(2);
		Layers[0] = new Perceptron(size, size, "Sigm");
		Layers[1] = new Perceptron(size, 10, "Sigm");

		Convolutionals = std::vector<Convolutional*>(n_layers);
		for (int i = 0; i < Convolutionals.size(); i++)
			Convolutionals[i] = new Convolutional(3, 3, kernels_sizes[i], "ReLu");
	}
	arma::mat solve(arma::mat& input) {
		std::vector<std::vector<arma::mat>> outputs;
		std::vector<arma::mat> in(1);
		in[0] = input;
		outputs.push_back(Convolutionals[0]->activate(in));
		for (int j = 1; j < Convolutionals.size(); j++) {
			outputs.push_back(Convolutionals[j]->activate(outputs[j - 1]));
		}
		arma::mat maps(1, outputs[Convolutionals.size() - 1].size());
		for (int i = 0; i < outputs[Convolutionals.size() - 1].size(); i++)
			maps.at(0, i) = outputs[Convolutionals.size() - 1][i][0];
		outputs.push_back(std::vector<arma::mat>());
		outputs.push_back(std::vector<arma::mat>());
		outputs[Convolutionals.size()].push_back(Layers[0]->activate(maps));
		outputs[Convolutionals.size() + 1].push_back(Layers[1]->activate(outputs[Convolutionals.size()][0]));
		return outputs[outputs.size() - 1][0];
	}

	void train(int ages, int error_step, double speed, arma::mat& input, arma::mat& etalon) {
		for (int i = 0; i < ages; i++) {
			std::vector<std::vector<arma::mat>> outputs;
			std::vector<arma::mat> in(1);
			in[0] = input;
			outputs.push_back(Convolutionals[0]->activate(in));
			for (int j = 1; j < Convolutionals.size(); j++) {
				outputs.push_back(Convolutionals[j]->activate(outputs[j - 1]));
			}
			arma::mat maps(1, outputs[Convolutionals.size() - 1].size());
			for (int j = 0; j < outputs[Convolutionals.size() - 1].size(); j++)
				maps.at(0, j) = outputs[Convolutionals.size() - 1][j][0];
			outputs.push_back(std::vector<arma::mat>());
			outputs.push_back(std::vector<arma::mat>());
			outputs[Convolutionals.size()].push_back(Layers[0]->activate(maps));
			outputs[Convolutionals.size() + 1].push_back(Layers[1]->activate(outputs[Convolutionals.size()][0]));
			arma::mat error = etalon - outputs[outputs.size() - 1][0];
			if (i%error_step == 0)
				std::cout << mean(abs(mean(error, 1))) << std::endl;

			error = Layers[1]->train(error, outputs[outputs.size() - 2][0], outputs[outputs.size() - 1][0], speed);
			error = Layers[0]->train(error, maps, outputs[outputs.size() - 2][0], speed);
			std::vector<arma::mat> deltas;
			for (int j = 0; j < error.size(); j++) {
				arma::mat temp(1,1);
				temp.at(0, 0) = error[j];
				deltas.push_back(temp);
			}
			for (int j = Convolutionals.size() - 1; j > -1; j--) {
				deltas = Convolutionals[j]->train(deltas, speed);
			}
		}
	}

	void save(std::string path) {
	}
	void load(std::string path) {
	}
};