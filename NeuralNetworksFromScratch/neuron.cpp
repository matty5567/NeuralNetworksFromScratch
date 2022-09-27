#include "neuron.h"
#include <assert.h>

Neuron::Neuron(int input_size) {
    srand(time(NULL));

    for (int i = 0; i < input_size; i++)
    {
        float initial_weight = (float)rand() / RAND_MAX;
        value* weight = new value(initial_weight);
        weights.push_back(weight);
    }
}

value* Neuron::forward(std::vector<value*> input) {
    assert(input.size() == weights.size());

    value* activation = new value();
    for (int i = 0; i < input.size(); i++) {
        activation = new value(* activation + *input[i] * *weights[i]);
    }
    activation = new value(*activation + *bias);
    return activation;
}