#include "neuron.h"
#include <assert.h>

Neuron::Neuron(int input_size) {
    

    for (int i = 0; i < input_size; i++)
    {
        float initial_weight = (((float)rand() / RAND_MAX) * 2 - 1) / 1000;
        value* weight = new value(initial_weight, "weight");
        weights.push_back(weight);
    }
}

value* Neuron::forward(std::vector<value*> input) {
    assert(input.size() == weights.size());

    value* activation = new value();
    for (int i = 0; i < input.size(); i++) {
        value* input_act = *input[i] * weights[i];
        activation = *activation + input_act;
    }
    activation = *activation + bias;
    activation = activation->leaky_relu(0.3);
    return activation;
}