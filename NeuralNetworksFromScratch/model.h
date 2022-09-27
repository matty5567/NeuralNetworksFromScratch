#pragma once

#include "linear.h"
#include <vector>
#include "value.h"

typedef std::vector<std::vector<value*>> mat;

class Model {

public:
	Model(std::vector<Linear> layers) : layers(layers) {};


	mat forward(mat act) {

		for (auto layer : layers) {
			act = layer.forward(act);
		}

		return act;
	};

	std::vector<value*> parameters();

	void zero_grad();


private:
	std::vector<Linear> layers;

};
