#include "linear.h"
#include <iostream>

Linear::Linear(int inputSize, int outputSize) {


	for (int i = 0; i < outputSize; i++) {
		Neuron neuron = Neuron(inputSize);
		neurons.push_back(neuron);
	}

};


mat Linear::forward(mat in) {


	mat out;
	out.resize(in.size());

	for (int i = 0; i < in.size(); i++) {
		for (Neuron neuron : neurons) {
			out[i].push_back(neuron.forward(in[i]));
		}
	}

	return out;
};

std::vector<value*> Linear::parameters() {
	std::vector<value*> params;
	for (Neuron neuron : neurons) {
		std::vector<value*> neuron_params = neuron.parameters();
		params.insert(params.end(), neuron_params.begin(), neuron_params.end());
	}
	return params;
};



