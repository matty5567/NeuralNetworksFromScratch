#pragma once

#include <cassert>
#include <vector>
#include "value.h"
#include "neuron.h"

typedef std::vector<std::vector<value*>> mat;


class Linear {

public:

	Linear(int inputSize, int outputSize);


	mat forward(mat inputs);

	std::vector<value*> parameters();



	// private:
	std::vector<Neuron> neurons = {};


};
