#include "model.h"

std::vector<value*> Model::parameters() {
	std::vector<value*> params;
	for (Linear layer : layers) {
		std::vector<value*> neuron_params = layer.parameters();
		params.insert(params.end(), neuron_params.begin(), neuron_params.end());
	}
	return params;
};


void Model::zero_grad() 
{
	for (auto value : this->parameters()) 
	{
		value->grad = 0.0f;
	}
}